#include "quickswap_plugin.h"

// Copies the whole parameter (32 bytes long) from `src` to `dst`.
// Useful for numbers, data...
static void copy_parameter(uint8_t *dst, size_t dst_len, uint8_t *src) {
    // Take the minimum between dst_len and parameter_length to make sure we don't overwrite memory.
    size_t len = MIN(dst_len, PARAMETER_LENGTH);
    memcpy(dst, src, len);
}

// Copy amount sent parameter to amount_sent
static void handle_amount_sent(const ethPluginProvideParameter_t *msg,
                               quickswap_parameters_t *context) {
    copy_parameter(context->amount_sent, sizeof(context->amount_sent), msg->parameter);
}

// Copy amount sent parameter to amount_received
static void handle_amount_received(const ethPluginProvideParameter_t *msg,
                                   quickswap_parameters_t *context) {
    copy_parameter(context->amount_received, sizeof(context->amount_received), msg->parameter);
}

static void handle_beneficiary(const ethPluginProvideParameter_t *msg,
                               quickswap_parameters_t *context) {
    memset(context->beneficiary, 0, sizeof(context->beneficiary));
    memcpy(context->beneficiary,
           &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH],
           sizeof(context->beneficiary));
    PRINTF("BENEFICIARY: %.*H\n", ADDRESS_LENGTH, context->beneficiary);
}

static void handle_array_len(const ethPluginProvideParameter_t *msg,
                             quickswap_parameters_t *context) {
    context->array_len = msg->parameter[PARAMETER_LENGTH - 1];
    PRINTF("LIST LEN: %d\n", context->array_len);
}

static void handle_token_sent(const ethPluginProvideParameter_t *msg,
                              quickswap_parameters_t *context) {
    memset(context->contract_address_sent, 0, sizeof(context->contract_address_sent));
    memcpy(context->contract_address_sent,
           &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH],
           sizeof(context->contract_address_sent));
    PRINTF("TOKEN SENT: %.*H\n", ADDRESS_LENGTH, context->contract_address_sent);
}

static void handle_token_received(const ethPluginProvideParameter_t *msg,
                                  quickswap_parameters_t *context) {
    memset(context->contract_address_received, 0, sizeof(context->contract_address_received));
    memcpy(context->contract_address_received,
           &msg->parameter[PARAMETER_LENGTH - ADDRESS_LENGTH],
           sizeof(context->contract_address_received));
    PRINTF("TOKEN RECEIVED: %.*H\n", ADDRESS_LENGTH, context->contract_address_received);
}

static void handle_swap_exact_tokens_for_tokens(ethPluginProvideParameter_t *msg,
                                                quickswap_parameters_t *context) {
    switch (context->next_param) {
        case AMOUNT_SENT:  // amountIn
            handle_amount_sent(msg, context);
            context->next_param = AMOUNT_RECEIVED;
            context->checkpoint = msg->parameterOffset;
            break;
        case AMOUNT_RECEIVED:  // amountOut
            handle_amount_received(msg, context);
            context->next_param = PATHS_OFFSET;
            break;
        case PATHS_OFFSET:
            context->offset = U2BE(msg->parameter, PARAMETER_LENGTH - 2);
            context->next_param = PATH;
            break;
        case PATH:  // len(path)
            handle_array_len(msg, context);
            context->next_param = TOKEN_SENT;
            break;
        case TOKEN_SENT:  // path[0]
            handle_token_sent(msg, context);
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

void handle_provide_parameter(void *parameters) {
    ethPluginProvideParameter_t *msg = (ethPluginProvideParameter_t *) parameters;
    quickswap_parameters_t *context = (quickswap_parameters_t *) msg->pluginContext;

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
            case SWAP_EXACT_TOKENS_FOR_TOKENS:
                handle_swap_exact_tokens_for_tokens(msg, context);
                break;
            default:
                PRINTF("Selector Index %d not supported\n", context->selectorIndex);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
                break;
        }
    }
}