#include "paraswap_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    paraswap_parameters_t *context = (paraswap_parameters_t *) msg->pluginContext;
    if (context->valid) {
        msg->numScreens = 2;
        if ((context->selectorIndex == SIMPLE_SWAP || context->selectorIndex == SIMPLE_BUY ||
             context->selectorIndex == SIMPLE_SWAP_V4) &&
            (strncmp(context->beneficiary,
                     (const unsigned char *) NULL_ETH_ADDRESS,
                     ADDRESS_LENGTH) != 0)) {
            // An addiitonal screen is required to display the `beneficiary` field.
            msg->numScreens += 1;
        }
        if (!ADDRESS_IS_NETWORK_TOKEN(context->contract_address_sent)) {
            // Address is not network token (0xeee...) so we will need to look up the token in the
            // CAL.
            msg->tokenLookup1 = context->contract_address_sent;
            PRINTF("Setting address sent to: %.*H\n",
                   ADDRESS_LENGTH,
                   context->contract_address_sent);

            // The user is not swapping ETH, so make sure there's no ETH being sent in this tx.
            if (!allzeroes(msg->pluginSharedRO->txContent->value.value,
                           msg->pluginSharedRO->txContent->value.length)) {
                PRINTF("ETH attached to tx when token being swapped is %.*H\n",
                       sizeof(context->contract_address_sent),
                       context->contract_address_sent);
                msg->result = ETH_PLUGIN_RESULT_ERROR;
            }
        } else {
            msg->tokenLookup1 = NULL;
        }
        if (!ADDRESS_IS_NETWORK_TOKEN(context->contract_address_received)) {
            // Address is not network token (0xeee...) so we will need to look up the token in the
            // CAL.
            PRINTF("Setting address receiving to: %.*H\n",
                   ADDRESS_LENGTH,
                   context->contract_address_received);
            msg->tokenLookup2 = context->contract_address_received;
        } else {
            msg->tokenLookup2 = NULL;
        }

        msg->uiType = ETH_UI_TYPE_GENERIC;
        msg->result = ETH_PLUGIN_RESULT_OK;
    } else {
        PRINTF("Context not valid\n");
        msg->result = ETH_PLUGIN_RESULT_FALLBACK;
    }
}