#include "paraswap_plugin.h"

// Called once to init.
void handle_init_contract(void *parameters) {
    ethPluginInitContract_t *msg = (ethPluginInitContract_t *) parameters;

    if (msg->interfaceVersion != ETH_PLUGIN_INTERFACE_VERSION_LATEST) {
        PRINTF("Wrong interface version: expected %d got %d\n",
               ETH_PLUGIN_INTERFACE_VERSION_LATEST,
               msg->interfaceVersion);
        msg->result = ETH_PLUGIN_RESULT_UNAVAILABLE;
        return;
    }

    if (msg->pluginContextLength < sizeof(paraswap_parameters_t)) {
        PRINTF("Paraswap context size too big: expected %d got %d\n",
               sizeof(paraswap_parameters_t),
               msg->pluginContextLength);
        msg->result = ETH_PLUGIN_RESULT_ERROR;
        return;
    }

    paraswap_parameters_t *context = (paraswap_parameters_t *) msg->pluginContext;
    memset(context, 0, sizeof(*context));
    context->valid = 1;

    for (uint8_t i = 0; i < NUM_PARASWAP_SELECTORS; i++) {
        if (memcmp((uint8_t *) PIC(PARASWAP_SELECTORS[i]), msg->selector, SELECTOR_SIZE) == 0) {
            context->selectorIndex = i;
            break;
        }
    }

    // Set `next_param` to be the first field we expect to parse.
    switch (context->selectorIndex) {
        case BUY_ON_UNI_FORK:
        case SWAP_ON_UNI_FORK:
        case BUY_ON_UNI:
        case SWAP_ON_UNI:
        case SWAP_ON_UNI_V4:
        case SWAP_ON_UNI_FORK_V4:
        case BUY_ON_UNI_V4:
        case BUY_ON_UNI_FORK_V4:
            if (context->selectorIndex == SWAP_ON_UNI_FORK ||
                context->selectorIndex == BUY_ON_UNI_FORK ||
                context->selectorIndex == SWAP_ON_UNI_FORK_V4 ||
                context->selectorIndex == BUY_ON_UNI_FORK_V4) {
                context->skip =
                    2;  // Skip the first two parameters (factory and initCode) for uni forks.
            }
            context->next_param = AMOUNT_SENT;
            break;
        case SWAP_ON_ZERO_V4:
        case SWAP_ON_ZERO_V2:
            context->next_param = TOKEN_SENT;
            break;
        case MEGA_SWAP:
        case BUY:
        case MULTI_SWAP:
        case SIMPLE_BUY:
        case SIMPLE_SWAP:
        case SIMPLE_SWAP_V4:
        case MULTI_SWAP_V4:
        case MEGA_SWAP_V4:
            context->next_param = TOKEN_SENT;
            if (context->selectorIndex != SIMPLE_SWAP_V4)
                context->skip = 1;  // Skipping 0x20 (offset of structure)
            break;
        default:
            PRINTF("Missing selectorIndex\n");
            msg->result = ETH_PLUGIN_RESULT_ERROR;
            return;
    }
    msg->result = ETH_PLUGIN_RESULT_OK;
}
