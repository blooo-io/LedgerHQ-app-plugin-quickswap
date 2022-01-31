#pragma once

#include "eth_internals.h"
#include "eth_plugin_interface.h"
#include <string.h>

#define PARAMETER_LENGTH        32
#define SELECTOR_SIZE           4
#define RUN_APPLICATION         1
#define NUM_QUICKSWAP_SELECTORS 12
#define PLUGIN_NAME             "QuickSwap"

#define TOKEN_SENT_FOUND     1
#define TOKEN_RECEIVED_FOUND 1 << 1

// QuickSwap uses `0xeeeee` as a dummy address to represent ETH.
extern const uint8_t QUICKSWAP_ETH_ADDRESS[ADDRESS_LENGTH];

// Adress 0x00000... used to indicate that the beneficiary is the sender.
extern const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH];

// Returns 1 if corresponding address is the QuickSwap address for the chain token (ETH, BNB, MATIC,
// etc.. are 0xeeeee...).
#define ADDRESS_IS_NETWORK_TOKEN(_addr) (!memcmp(_addr, QUICKSWAP_ETH_ADDRESS, ADDRESS_LENGTH))

typedef enum {
    SWAP_EXACT_TOKENS_FOR_TOKENS,
    SWAP_EXACT_TOKENS_FOR_ETH,
    SWAP_EXACT_ETH_FOR_TOKENS,
    SWAP_TOKENS_FOR_EXACT_TOKENS,
    SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS,
    SWAP_ETH_FOR_EXACT_TOKENS,
    SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS,
    SWAP_TOKENS_FOR_EXACT_ETH,
    SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS,
    ADD_LIQUIDITY,
    ADD_LIQUIDITY_ETH,
    REMOVE_LIQUIDITY
} quickswapSelector_t;

extern const uint8_t *const QUICKSWAP_SELECTORS[NUM_QUICKSWAP_SELECTORS];

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
#define PATH            4
// Path of the different asseths that will get swapped during the trade. First and last
// tokens are the ones we care about.
#define BENEFICIARY                 5  // Address to which the contract will send the tokens.
#define OFFSET                      6
#define PATHS_OFFSET                7
#define PATHS_LEN                   8
#define TOKEN_RECEIVED_PATHS_OFFSET 9
#define TOKEN_RECEIVED_PATH         10
#define NONE                        11
// Number of decimals used when the token wasn't found in the CAL.
#define DEFAULT_DECIMAL WEI_TO_ETHER

// Ticker used when the token wasn't found in the CAL.
#define DEFAULT_TICKER ""

// Shared global memory with Ethereum app. Must be at most 5 * 32 bytes.
typedef struct quickswap_parameters_t {
    uint8_t amount_sent[INT256_LENGTH];                 // 32 bytes
    uint8_t amount_received[INT256_LENGTH];             // 32 bytes
    uint8_t contract_address_sent[ADDRESS_LENGTH];      // 20 bytes
    uint8_t contract_address_received[ADDRESS_LENGTH];  // 20 bytes
    char beneficiary[ADDRESS_LENGTH];                   // 20 bytes
    char ticker_sent[MAX_TICKER_LEN];                   // 12 bytes
    char ticker_received[MAX_TICKER_LEN];               // 12 bytes

    // sub total : 148 bytes

    uint16_t offset;            // 2 bytes
    uint16_t checkpoint;        // 2 bytes
    uint8_t next_param;         // 1 byte
    uint8_t tokens_found;       // 1 byte
    uint8_t valid;              // 1 byte
    uint8_t decimals_sent;      // 1 byte
    uint8_t decimals_received;  // 1 byte
    uint8_t selectorIndex;      // 1 byte
    uint8_t array_len;          // 1 byte
    uint8_t skip;               // 1 byte

    // sub total : 12 bytes
    // total : 148b + 12b = 160 bytes : no bytes left

} quickswap_parameters_t;

void handle_init_contract(void *parameters);
void handle_provide_parameter(void *parameters);
void handle_query_contract_ui(void *parameters);
void handle_finalize(void *parameters);
void handle_provide_token(void *parameters);
void handle_query_contract_id(void *parameters);