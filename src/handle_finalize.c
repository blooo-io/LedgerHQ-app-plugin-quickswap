#include "quickswap_plugin.h"

void handle_finalize(void *parameters) {
    ethPluginFinalize_t *msg = (ethPluginFinalize_t *) parameters;
    quickswap_parameters_t *context = (quickswap_parameters_t *) msg->pluginContext;

    if (context->valid && context->next_param == NONE) {
        msg->numScreens = 2;
        if (memcmp(context->beneficiary, NULL_ETH_ADDRESS, ADDRESS_LENGTH) != 0) {
            // An additional screen is required to display the `beneficiary` field.
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