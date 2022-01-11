#include "paraswap_plugin.h"

void handle_query_contract_id(void *parameters) {
    ethQueryContractID_t *msg = (ethQueryContractID_t *) parameters;
    const paraswap_parameters_t *context = (paraswap_parameters_t *) msg->pluginContext;

    strlcpy(msg->name, PLUGIN_NAME, msg->nameLength);

    switch (context->selectorIndex) {
        case MEGA_SWAP:
        case MULTI_SWAP:
        case SIMPLE_SWAP:
        case SIMPLE_SWAP_V4:
        case SWAP_ON_UNI_FORK:
        case SWAP_ON_UNI:
        case SWAP_ON_ZERO_V4:
        case SWAP_ON_ZERO_V2:
        case SWAP_ON_UNI_V4:
        case SWAP_ON_UNI_FORK_V4:
        case MULTI_SWAP_V4:
        case MEGA_SWAP_V4:
            strlcpy(msg->version, "Swap", msg->versionLength);
            break;
        case SIMPLE_BUY:
        case BUY_ON_UNI_FORK:
        case BUY_ON_UNI:
        case BUY:
        case BUY_ON_UNI_V4:
        case BUY_ON_UNI_FORK_V4:
            strlcpy(msg->version, "Buy", msg->versionLength);
            break;
        default:
            PRINTF("Selector Index :%d not supported\n", context->selectorIndex);
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }

    msg->result = ETH_PLUGIN_RESULT_OK;
}
