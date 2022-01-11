#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

#define PARAMETER_LENGTH 32
#define SELECTOR_SIZE    4

#define RUN_APPLICATION 1

#define NUM_PARASWAP_SELECTORS 18
#define SELECTOR_SIZE          4

#define PLUGIN_NAME "Paraswap"

#define TOKEN_SENT_FOUND     1
#define TOKEN_RECEIVED_FOUND 1 << 1

// Paraswap uses `0xeeeee` as a dummy address to represent ETH.
extern const uint8_t PARASWAP_ETH_ADDRESS[ADDRESS_LENGTH];

// Adress 0x00000... used to indicate that the beneficiary is the sender.
extern const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH];

// Returns 1 if corresponding address is the Paraswap address for the chain token (ETH, BNB, MATIC,
// etc.. are 0xeeeee...).
#define ADDRESS_IS_NETWORK_TOKEN(_addr) (!memcmp(_addr, PARASWAP_ETH_ADDRESS, ADDRESS_LENGTH))

typedef enum {
    SWAP_ON_UNI,
    BUY_ON_UNI,
    SWAP_ON_UNI_FORK,
    BUY_ON_UNI_FORK,
    SIMPLE_SWAP,
    SIMPLE_BUY,
    MULTI_SWAP,
    BUY,
    MEGA_SWAP,
    SWAP_ON_ZERO_V4,
    SWAP_ON_ZERO_V2,
    SIMPLE_SWAP_V4,
    SWAP_ON_UNI_V4,
    SWAP_ON_UNI_FORK_V4,
    MULTI_SWAP_V4,
    MEGA_SWAP_V4,
    BUY_ON_UNI_V4,
    BUY_ON_UNI_FORK_V4
} paraswapSelector_t;

extern const uint8_t *const PARASWAP_SELECTORS[NUM_PARASWAP_SELECTORS];

typedef enum {
    SEND_SCREEN,
    RECEIVE_SCREEN,
    WARN_SCREEN,
    BENEFICIARY_SCREEN,
    ERROR,
} screens_t;

// Would've loved to make this an enum but we don't have enough room because enums are `int` and not
// `uint8_t`.
#define AMOUNT_SENT     0  // Amount sent by the user to the contract.
#define AMOUNT_RECEIVED 1  // Amount sent by the contract to the user.
#define TOKEN_SENT      2  // Address of the token the user is sending.
#define TOKEN_RECEIVED  3  // Address of the token sent to the user.
#define PATH \
    4  // Path of the different asseths that will get swapped during the trade. First and last
       // tokens are the ones we care about.
#define BENEFICIARY           5  // Address to which the contract will send the tokens.
#define OFFSET                6
#define PATHS_OFFSET          7
#define PATHS_LEN             8
#define MEGA_PATHS_OFFSET     9
#define MEGA_PATHS_LEN        10
#define FIRST_MEGAPATH_OFFSET 11
#define FIRST_MEGAPATH        12
#define NONE                  13  // Placeholder variant to be set when parsing is done but data is still being sent.

// Number of decimals used when the token wasn't found in the CAL.
#define DEFAULT_DECIMAL WEI_TO_ETHER

// Ticker used when the token wasn't found in the CAL.
#define DEFAULT_TICKER ""

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct paraswap_parameters_t {
    uint8_t amount_sent[INT256_LENGTH];
    uint8_t amount_received[INT256_LENGTH];
    char beneficiary[ADDRESS_LENGTH];
    uint8_t contract_address_sent[ADDRESS_LENGTH];
    uint8_t contract_address_received[ADDRESS_LENGTH];
    char ticker_sent[MAX_TICKER_LEN];
    char ticker_received[MAX_TICKER_LEN];

    // 32 * 2 + 20 * 3 + 12 * 2 == 64 + 60 + 24 == 144
    // 32 * 5 == 160 bytes so there are 160 - 144 == 16 bytes left.

    uint16_t offset;
    uint16_t checkpoint;
    uint8_t next_param;
    uint8_t tokens_found;
    uint8_t valid;
    uint8_t decimals_sent;
    uint8_t decimals_received;
    uint8_t selectorIndex;
    uint8_t array_len;
    uint8_t skip;
    // 4 * 1 + 2 * 2 + 7 * 1 == 8 + 7 == 15 bytes. There are 16 - 15 == 1 byte left.
} paraswap_parameters_t;

void handle_init_contract(void *parameters);
void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);