#include "paraswap_plugin.h"

// Copies the whole parameter (32 bytes long) from `src` to `dst`.
// Useful for numbers, data...
static void copy_parameter(uint8_t *dst, size_t dst_len, uint8_t *src) {
    // Take the minimum between dst_len and parameter_length to make sure we don't overwrite memory.
    size_t len = MIN(dst_len, PARAMETER_LENGTH);
    memcpy(dst, src, len);
}

// Copy amount sent parameter to amount_sent
static void handle_amount_sent(const ethPluginProvideParameter_t *msg,
                               paraswap_parameters_t *context) {
    copy_parameter(context->amount_sent, sizeof(context->amount_sent), msg->parameter);
}

// Copy amount sent parameter to amount_received
static void handle_amount_received(const ethPluginProvideParameter_t *msg,
                                   paraswap_parameters_t *context) {
    copy_parameter(context->amount_received, sizeof(context->amount_received), msg->parameter);
}

static void handle_beneficiary(const ethPluginProvideParameter_t *msg,
                               paraswap_parameters_t *context) {
    memset(context->beneficiary, 0, sizeof(context->beneficiary));
    memcpy(context->beneficiary,
           &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH],
           sizeof(context->beneficiary));
    PRINTF("BENEFICIARY: %.*H\n", ADDRESS_LENGTH, context->beneficiary);
}

static void handle_array_len(const ethPluginProvideParameter_t *msg,
                             paraswap_parameters_t *context) {
    context->array_len = msg->parameter[PARAMETER_LENGTH - 1];
    PRINTF("LIST LEN: %d\n", context->array_len);
}

static void handle_token_sent(const ethPluginProvideParameter_t *msg,
                              paraswap_parameters_t *context) {
    memset(context->contract_address_sent, 0, sizeof(context->contract_address_sent));
    memcpy(context->contract_address_sent,
           &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH],
           sizeof(context->contract_address_sent));
    PRINTF("TOKEN SENT: %.*H\n", ADDRESS_LENGTH, context->contract_address_sent);
}

static void handle_token_received(const ethPluginProvideParameter_t *msg,
                                  paraswap_parameters_t *context) {
    memset(context->contract_address_received, 0, sizeof(context->contract_address_received));
    memcpy(context->contract_address_received,
           &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH],
           sizeof(context->contract_address_received));
    PRINTF("TOKEN RECEIVED: %.*H\n", ADDRESS_LENGTH, context->contract_address_received);
}

static void handle_uniswap_and_forks(ethPluginProvideParameter_t *msg,
                                     paraswap_parameters_t *context) {
    switch (context->next_param) {
        case AMOUNT_SENT:  // amountIn
            handle_amount_sent(msg, context);
            context->next_param = AMOUNT_RECEIVED;
            context->checkpoint = msg->parameterOffset;
            if (context->selectorIndex == BUY_ON_UNI_FORK ||
                context->selectorIndex == SWAP_ON_UNI_FORK ||
                context->selectorIndex == SWAP_ON_UNI_FORK_V4 ||
                context->selectorIndex == BUY_ON_UNI_FORK_V4) {
                // Substract two chunks because we've skipped the first two parameters.
                // No underflow possible because we've skipped the first two chunks, so
                // msg->parameterOffset >= 2 * PARAMETER_LENGTH.
                context->checkpoint -= 2 * PARAMETER_LENGTH;
            }
            break;
        case AMOUNT_RECEIVED:  // amountOut
            handle_amount_received(msg, context);
            context->next_param = PATHS_OFFSET;
            break;
        case PATHS_OFFSET:
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - sizeof(context->offset));
            context->next_param = PATH;
            break;
        case PATH:  // len(path)
            handle_array_len(msg, context);
            context->next_param = TOKEN_SENT;
            break;
        case TOKEN_SENT:  // path[0]
            handle_token_sent(msg, context);
            // -2 because we won't be skipping the first one and the last one.
            context->skip = context->array_len - 2;
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:  // path[len(path) - 1]
            handle_token_received(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Unsupported param\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_simple_calls(ethPluginProvideParameter_t *msg, paraswap_parameters_t *context) {
    switch (context->next_param) {
        case TOKEN_SENT:  // fromToken
            handle_token_sent(msg, context);
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:  // toToken
            handle_token_received(msg, context);
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:  // fromAmount
            handle_amount_sent(msg, context);
            context->next_param = AMOUNT_RECEIVED;
            break;
        case AMOUNT_RECEIVED:  // toAmount
            handle_amount_received(msg, context);
            context->next_param = BENEFICIARY;
            context->skip = 4;  // callees, exchangeData, startIndexes, values.
            if (context->selectorIndex == SIMPLE_SWAP || context->selectorIndex == SIMPLE_SWAP_V4) {
                context->skip++;  // skip field expectedAmount for simple swap.
            }
            break;
        case BENEFICIARY:
            handle_beneficiary(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_multiswap(ethPluginProvideParameter_t *msg, paraswap_parameters_t *context) {
    switch (context->next_param) {
        case TOKEN_SENT:  // fromToken
            context->checkpoint = msg->parameterOffset;
            handle_token_sent(msg, context);
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:  // fromAmount
            handle_amount_sent(msg, context);
            context->next_param = AMOUNT_RECEIVED;
            break;
        case AMOUNT_RECEIVED:  // toAmount
            handle_amount_received(msg, context);
            context->next_param = BENEFICIARY;
            context->skip = 1;  // Skip expectedAmount
            break;
        case BENEFICIARY:  // beneficiary
            handle_beneficiary(msg, context);
            context->next_param = PATHS_OFFSET;
            if (context->selectorIndex == MULTI_SWAP_V4) {
                context->skip = 2;  // Skip referrer and useReduxtoken
            }
            break;
        case PATHS_OFFSET:
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = PATHS_LEN;
            break;
        case PATHS_LEN:
            // We want to access path[-1] so take the length and decrease by one
            context->skip = msg->parameter[PARAMETER_LENGTH - 1] - 1;
            context->next_param = OFFSET;
            context->checkpoint = msg->parameterOffset +
                                  PARAMETER_LENGTH;  // Offset checkpoint starts after the length
            break;
        case OFFSET:
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:
            handle_token_received(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_buy(ethPluginProvideParameter_t *msg, paraswap_parameters_t *context) {
    switch (context->next_param) {
        case TOKEN_SENT:  // fromToken
            handle_token_sent(msg, context);
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:  // toToken
            handle_token_received(msg, context);
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:  // fromAmount
            handle_amount_sent(msg, context);
            context->next_param = AMOUNT_RECEIVED;
            break;
        case AMOUNT_RECEIVED:  // toAmount
            handle_amount_received(msg, context);
            context->next_param = BENEFICIARY;
            break;
        case BENEFICIARY:  // beneficiary
            handle_beneficiary(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_swap_on_zero(ethPluginProvideParameter_t *msg, paraswap_parameters_t *context) {
    switch (context->next_param) {
        case TOKEN_SENT:  // fromToken
            handle_token_sent(msg, context);
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:  // toToken
            handle_token_received(msg, context);
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:  // fromAmount
            handle_amount_sent(msg, context);
            context->next_param = AMOUNT_RECEIVED;
            break;
        case AMOUNT_RECEIVED:  // toAmount
            handle_amount_received(msg, context);
            context->next_param = NONE;
            break;
        case BENEFICIARY:  // beneficiary
            handle_beneficiary(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

static void handle_megaswap(ethPluginProvideParameter_t *msg, paraswap_parameters_t *context) {
    switch (context->next_param) {
        case TOKEN_SENT:  // fromToken
            context->checkpoint = msg->parameterOffset;
            handle_token_sent(msg, context);
            context->next_param = AMOUNT_SENT;
            break;
        case AMOUNT_SENT:
            handle_amount_sent(msg, context);
            context->next_param = AMOUNT_RECEIVED;
            break;
        case AMOUNT_RECEIVED:
            handle_amount_received(msg, context);
            context->next_param = BENEFICIARY;
            context->skip = 1;  // Skip expectedAmount.
            break;
        case BENEFICIARY:
            handle_beneficiary(msg, context);
            context->next_param = MEGA_PATHS_OFFSET;
            if (context->selectorIndex == MEGA_SWAP_V4) {
                context->skip = 2;  // Skip referrer and useReduxToken.
            }
            break;
        case MEGA_PATHS_OFFSET:
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = MEGA_PATHS_LEN;
            break;
        case MEGA_PATHS_LEN:
            context->next_param = FIRST_MEGAPATH_OFFSET;
            break;
        case FIRST_MEGAPATH_OFFSET:
            context->checkpoint = msg->parameterOffset;
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = FIRST_MEGAPATH;
            break;
        case FIRST_MEGAPATH:
            context->checkpoint = msg->parameterOffset;
            context->next_param = PATHS_OFFSET;
            break;
        case PATHS_OFFSET:
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = PATHS_LEN;
            break;
        case PATHS_LEN:
            context->skip = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->skip--;  // Decrease by one because we wish to acces path[-1].
            context->next_param = PATH;
            break;
        case PATH:
            context->checkpoint = msg->parameterOffset;
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = TOKEN_RECEIVED;
            break;
        case TOKEN_RECEIVED:
            handle_token_received(msg, context);
            context->next_param = NONE;
            break;
        case NONE:
            break;
        default:
            PRINTF("Param not supported\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            break;
    }
}

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    paraswap_parameters_t *context = (paraswap_parameters_t *) msg->pluginContext;

    msg->result = ETH_PLUGIN_RESULT_OK;

    if (context->skip) {
        // Skip this step, and don't forget to decrease skipping counter.
        context->skip--;
    } else {
        if ((context->offset) && msg->parameterOffset != context->checkpoint + context->offset) {
            PRINTF("offset: %d, checkpoint: %d, parameterOffset: %d\n",
                   context->offset,
                   context->checkpoint,
                   msg->parameterOffset);
            return;
        }
        context->offset = 0;  // Reset offset
        switch (context->selectorIndex) {
            case BUY_ON_UNI_FORK:
            case SWAP_ON_UNI_FORK:
            case BUY_ON_UNI:
            case SWAP_ON_UNI:
            case SWAP_ON_UNI_V4:
            case SWAP_ON_UNI_FORK_V4:
            case BUY_ON_UNI_V4:
            case BUY_ON_UNI_FORK_V4:
                handle_uniswap_and_forks(msg, context);
                break;

            case SIMPLE_BUY:
            case SIMPLE_SWAP:
            case SIMPLE_SWAP_V4:
                handle_simple_calls(msg, context);
                break;

            case MULTI_SWAP:
            case MULTI_SWAP_V4:
                handle_multiswap(msg, context);
                break;

            case BUY:
                handle_buy(msg, context);
                break;

            case MEGA_SWAP:
            case MEGA_SWAP_V4:
                handle_megaswap(msg, context);
                break;

            case SWAP_ON_ZERO_V2:
            case SWAP_ON_ZERO_V4:
                handle_swap_on_zero(msg, context);
                break;

            default:
                PRINTF("Selector Index %d not supported\n", context->selectorIndex);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                break;
        }
    }
}