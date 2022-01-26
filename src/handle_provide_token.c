#include "quickswap_plugin.h"

void handle_provide_token(void *parameters) {
    ethPluginProvideInfo_t *msg = (ethPluginProvideInfo_t *) parameters;
    quickswap_parameters_t *context = (quickswap_parameters_t *) msg->pluginContext;
    PRINTF("QUICKSWAP plugin provide token: 0x%p, 0x%p\n", msg->item1->token, msg->item2->token);

    if (ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
        context->decimals_sent = WEI_TO_ETHER;
        context->tokens_found |= TOKEN_SENT_FOUND;
    } else if (msg->item1->token.address != NULL) {
        context->decimals_sent = msg->item1->token.decimals;
        strlcpy(context->ticker_sent, (char *) msg->item1->token.ticker, sizeof(context->ticker_sent));
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
    } else if (msg->item2->token.address != NULL) {
        context->decimals_received = msg->item2->token.decimals;
        strlcpy(context->ticker_received,
                (char *) msg->item2->token.ticker,
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