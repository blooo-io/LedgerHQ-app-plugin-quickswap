#include "quickswap_plugin.h"

void set_sent_amount(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Send", msg->titleLength);
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }
    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   context->decimals_sent,
                   context->ticker_sent,
                   msg->msg,
                   msg->msgLength);
}

void set_sent_amount_max(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Send Max", msg->titleLength);
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }
    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   context->decimals_sent,
                   context->ticker_sent,
                   msg->msg,
                   msg->msgLength);
}

void set_sent_amount_eth(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Send", msg->titleLength);
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }

    amountToString(msg->pluginSharedRO->txContent->value.value,
                   msg->pluginSharedRO->txContent->value.length,
                   context->decimals_sent,
                   context->ticker_sent,
                   msg->msg,
                   msg->msgLength);
}

void set_sent_amount_eth_max(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Send Max", msg->titleLength);
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }

    amountToString(msg->pluginSharedRO->txContent->value.value,
                   msg->pluginSharedRO->txContent->value.length,
                   context->decimals_sent,
                   context->ticker_sent,
                   msg->msg,
                   msg->msgLength);
}

void set_received_amount_min(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Receive Min", msg->titleLength);

    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_received)) {
        strlcpy(context->ticker_received, msg->network_ticker, sizeof(context->ticker_received));
    }

    amountToString(context->amount_received,
                   sizeof(context->amount_received),
                   context->decimals_received,
                   context->ticker_received,
                   msg->msg,
                   msg->msgLength);
}

void set_received_amount(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Receive", msg->titleLength);

    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_received)) {
        strlcpy(context->ticker_received, msg->network_ticker, sizeof(context->ticker_received));
    }

    amountToString(context->amount_received,
                   sizeof(context->amount_received),
                   context->decimals_received,
                   context->ticker_received,
                   msg->msg,
                   msg->msgLength);
}

void set_amount_a_min(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Send Min", msg->titleLength);
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }
    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   context->decimals_sent,
                   context->ticker_sent,
                   msg->msg,
                   msg->msgLength);
}

void set_amount_a_min_remove(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Receive Min", msg->titleLength);
    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        strlcpy(context->ticker_sent, msg->network_ticker, sizeof(context->ticker_sent));
    }
    amountToString(context->amount_sent,
                   sizeof(context->amount_sent),
                   context->decimals_sent,
                   context->ticker_sent,
                   msg->msg,
                   msg->msgLength);
}

void set_amount_b_min(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Send Min", msg->titleLength);

    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_received)) {
        strlcpy(context->ticker_received, msg->network_ticker, sizeof(context->ticker_received));
    }

    amountToString(context->amount_received,
                   sizeof(context->amount_received),
                   context->decimals_received,
                   context->ticker_received,
                   msg->msg,
                   msg->msgLength);
}

void set_amount_b_min_remove(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Receive Min", msg->titleLength);

    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_received)) {
        strlcpy(context->ticker_received, msg->network_ticker, sizeof(context->ticker_received));
    }

    amountToString(context->amount_received,
                   sizeof(context->amount_received),
                   context->decimals_received,
                   context->ticker_received,
                   msg->msg,
                   msg->msgLength);
}

// Set UI for the "Send" screen.
static void set_send_ui(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    switch (context->selectorIndex) {
        case SWAP_EXACT_TOKENS_FOR_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_ETH:
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            set_sent_amount(msg, context);
            break;
        case SWAP_EXACT_ETH_FOR_TOKENS:
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            set_sent_amount_eth(msg, context);
            break;
        case SWAP_ETH_FOR_EXACT_TOKENS:
            set_sent_amount_eth_max(msg, context);
            break;
        case SWAP_TOKENS_FOR_EXACT_TOKENS:
        case SWAP_TOKENS_FOR_EXACT_ETH:
            set_sent_amount_max(msg, context);
            break;

        case ADD_LIQUIDITY:
        case ADD_LIQUIDITY_ETH:
            set_amount_a_min(msg, context);
            break;

        case REMOVE_LIQUIDITY:
        case REMOVE_LIQUIDITY_ETH:
        case REMOVE_LIQUIDITY_WITH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_WITH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            set_amount_a_min_remove(msg, context);
            break;

        default:
            PRINTF("Unhandled selector Index: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}

// Set UI for "Receive" screen.
static void set_receive_ui(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    switch (context->selectorIndex) {
        case SWAP_EXACT_TOKENS_FOR_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_ETH:
        case SWAP_EXACT_ETH_FOR_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            set_received_amount_min(msg, context);
            break;
        case SWAP_ETH_FOR_EXACT_TOKENS:
        case SWAP_TOKENS_FOR_EXACT_TOKENS:
        case SWAP_TOKENS_FOR_EXACT_ETH:
            set_received_amount(msg, context);
            break;

        case ADD_LIQUIDITY:
        case ADD_LIQUIDITY_ETH:
            set_amount_b_min(msg, context);
            break;

        case REMOVE_LIQUIDITY:
        case REMOVE_LIQUIDITY_ETH:
        case REMOVE_LIQUIDITY_WITH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_WITH_PERMIT:
        case REMOVE_LIQUIDITY_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
        case REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SUPPORTING_FEE_ON_TRANSFER_TOKENS:
            set_amount_b_min_remove(msg, context);
            break;

        default:
            PRINTF("Unhandled selector Index: %d\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}

// Set UI for "Beneficiary" screen.
static void set_beneficiary_ui(ethQueryContractUI_t *msg, quickswap_parameters_t *context) {
    strlcpy(msg->title, "Beneficiary", msg->titleLength);

    msg->msg[0] = '0';
    msg->msg[1] = 'x';

    getEthAddressStringFromBinary((uint8_t *) context->beneficiary,
                                  (char *) msg->msg + 2,
                                  msg->pluginSharedRW->sha3,
                                  0);
}

// Set UI for "Warning" screen.
static void set_warning_ui(ethQueryContractUI_t *msg,
                           const quickswap_parameters_t *context __attribute__((unused))) {
    strlcpy(msg->title, "WARNING", msg->titleLength);
    strlcpy(msg->msg, "Unknown token", msg->msgLength);
}

// Helper function that returns the enum corresponding to the screen that should be displayed.
static screens_t get_screen(const ethQueryContractUI_t *msg,
                            const quickswap_parameters_t *context) {
    uint8_t index = msg->screenIndex;

    bool token_sent_found = context->tokens_found & TOKEN_SENT_FOUND;
    bool token_received_found = context->tokens_found & TOKEN_RECEIVED_FOUND;

    bool both_tokens_found = token_received_found && token_sent_found;
    bool both_tokens_not_found = !token_received_found && !token_sent_found;

    switch (index) {
        case 0:
            if (both_tokens_found) {
                return SEND_SCREEN;
            } else if (both_tokens_not_found) {
                return WARN_SCREEN;
            } else if (token_sent_found) {
                return SEND_SCREEN;
            } else if (token_received_found) {
                return WARN_SCREEN;
            }
            break;
        case 1:
            if (both_tokens_found) {
                return RECEIVE_SCREEN;
            } else if (both_tokens_not_found) {
                return SEND_SCREEN;
            } else if (token_sent_found) {
                return WARN_SCREEN;
            } else if (token_received_found) {
                return SEND_SCREEN;
            }
            break;
        case 2:
            if (both_tokens_found) {
                return BENEFICIARY_SCREEN;
            } else if (both_tokens_not_found) {
                return WARN_SCREEN;
            } else {
                return RECEIVE_SCREEN;
            }
        case 3:
            if (both_tokens_found) {
                return ERROR;
            } else if (both_tokens_not_found) {
                return RECEIVE_SCREEN;
            } else {
                return BENEFICIARY_SCREEN;
            }
        case 4:
            if (both_tokens_not_found) {
                return BENEFICIARY_SCREEN;
            } else {
                return ERROR;
            }
        default:
            return ERROR;
    }
    return ERROR;
}

void handle_query_contract_ui(void *parameters) {
    ethQueryContractUI_t *msg = (ethQueryContractUI_t *) parameters;
    quickswap_parameters_t *context = (quickswap_parameters_t *) msg->pluginContext;
    memset(msg->title, 0, msg->titleLength);
    memset(msg->msg, 0, msg->msgLength);
    msg->result = ETH_PLUGIN_RESULT_OK;

    screens_t screen = get_screen(msg, context);
    switch (screen) {
        case SEND_SCREEN:
            set_send_ui(msg, context);
            break;
        case RECEIVE_SCREEN:
            set_receive_ui(msg, context);
            break;
        case BENEFICIARY_SCREEN:
            set_beneficiary_ui(msg, context);
            break;
        case WARN_SCREEN:
            set_warning_ui(msg, context);
            break;
        default:
            PRINTF("Received an invalid screenIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
}
