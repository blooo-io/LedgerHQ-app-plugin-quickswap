#include "quickswap_plugin.h"

void handle_provide_token(void *parameters) {
    ethPluginProvideToken_t *msg = (ethPluginProvideToken_t *) parameters;
    quickswap_parameters_t *context = (quickswap_parameters_t *) msg->pluginContext;
    PRINTF("QUICKSWAP plugin provide token: 0x%p, 0x%p\n", msg->token1, msg->token2);

    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        context->decimals_sent = WEI_TO_ETHER;
        context->tokens_found |= TOKEN_SENT_FOUND;
    } else if (msg->token1 != NULL) {
        context->decimals_sent = msg->token1->decimals;
        strlcpy(context->ticker_sent, (char *) msg->token1->ticker, sizeof(context->ticker_sent));
        context->tokens_found |= TOKEN_SENT_FOUND;
    } else {
        // CAL did not find the token and token is not ETH.
        context->decimals_sent = DEFAULT_DECIMAL;
        strlcpy(context->ticker_sent, "???", sizeof(context->ticker_sent));
        // We will need an additional screen to display a warning message.
    }

    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_received)) {
        context->decimals_received = WEI_TO_ETHER;
        context->tokens_found |= TOKEN_RECEIVED_FOUND;
    } else if (msg->token2 != NULL) {
        context->decimals_received = msg->token2->decimals;
        strlcpy(context->ticker_received,
                (char *) msg->token2->ticker,
                sizeof(context->ticker_received));
        context->tokens_found |= TOKEN_RECEIVED_FOUND;
    } else {
        // CAL did not find the token and token is not ETH.
        context->decimals_received = DEFAULT_DECIMAL;
        strlcpy(context->ticker_received, "???", sizeof(context->ticker_received));
        // We will need an additional screen to display a warning message.
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}