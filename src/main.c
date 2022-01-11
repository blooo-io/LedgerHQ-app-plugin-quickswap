/*******************************************************************************
 *   Ethereum 2 Deposit Application
 *   (c) 2020 Ledger
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 ********************************************************************************/

#include <stdbool.h>
#include <stdint.h>

#include "os.h"
#include "cx.h"

#include "glyphs.h"

#include "paraswap_plugin.h"

// ---------- Paraswap V5 -------------
// Function: swapOnUniswap(uint256 amountIn, uint256 amountOutMin, address[] path) ***
// Selector: 0x54840d1a
static const uint8_t PARASWAP_SWAP_ON_UNISWAP_SELECTOR[SELECTOR_SIZE] = {0x54, 0x84, 0x0d, 0x1a};

// Function: swapOnUniswapFork(address factory, bytes32 initCode, uint256 amountIn, uint256
// amountOutMin, address[] path)
// Selector : 0xf5661034
static const uint8_t PARASWAP_SWAP_ON_UNISWAP_FORK_SELECTOR[SELECTOR_SIZE] = {0xf5,
                                                                              0x66,
                                                                              0x10,
                                                                              0x34};

// Function: buyOnUniswap(uint256 amountInMax, uint256 amountOut, address[] path)
// Selector: 0x935fb84b
static const uint8_t PARASWAP_BUY_ON_UNISWAP_SELECTOR[SELECTOR_SIZE] = {0x93, 0x5f, 0xb8, 0x4b};

// Function: buyOnUniswapFork(address factory, bytes32 initCode, uint256 amountInMax, uint256
// amountOut, address[] path) ***
// Selector: 0xc03786b0
static const uint8_t PARASWAP_BUY_ON_UNISWAP_FORK_SELECTOR[SELECTOR_SIZE] = {0xc0,
                                                                             0x37,
                                                                             0x86,
                                                                             0xb0};

// Function : simpleSwap((address fromToken,address toToken,uint256 fromAmount,uint256 toAmount,
// uint256 expectedAmount,address[] callees,bytes exchangeData,uint256[] startIndexes,
// uint256[] values,address beneficiary,address partner,uint256 feePercent,bytes permit,
// uint256 deadline,bytes16 uuid))
// Selector : 0x54e3f31b
static const uint8_t PARASWAP_SIMPLE_SWAP_SELECTOR[SELECTOR_SIZE] = {0x54, 0xe3, 0xf3, 0x1b};

// Function: multiSwap ((address fromToken, uint256 fromAmount, uint256 toAmount, uint256
// expectedAmount, address payable beneficiary, Utils.Path[] path, address payable partner, uint256
// feePercent, bytes permit, uint256 deadline, bytes16 uuid)) )
// Selector: 0xa94e78ef
static const uint8_t PARASWAP_MULTI_SWAP_SELECTOR[SELECTOR_SIZE] = {0xa9, 0x4e, 0x78, 0xef};

// Function: megaSwap (( address fromToken, uint256 fromAmount, uint256 toAmount, uint256
// expectedAmount, address payable beneficiary, Utils.MegaSwapPath[] path, address payable partner,
// uint256 feePercent, bytes permit, uint256 deadline, bytes16 uuid)) external returns (
// uint256 )
// Selector: 0x46c67b6d
static const uint8_t PARASWAP_MEGA_SWAP_SELECTOR[SELECTOR_SIZE] = {0x46, 0xc6, 0x7b, 0x6d};

// Function: simpleBuy(( address fromToken, address toToken, uint256 fromAmount, uint256
// toAmount, uint256 expectedAmount, address[] callees, bytes exchangeData, uint256[]
// startIndexes, uint256[] values, address payable beneficiary, address payable partner, uint256
// feePercent, bytes permit, uint256 deadline, bytes16 uuid,) ) external payable,
// Selector: 0x2298207a
static const uint8_t PARASWAP_SIMPLE_BUY_SELECTOR[SELECTOR_SIZE] = {0x22, 0x98, 0x20, 0x7a};

// Function swapOnZeroXv4 ( address fromToken, address toToken, uint256 fromAmount, uint256
// amountOutMin, address exchange, bytes payload )
// Selector 0x64466805
static const uint8_t PARASWAP_SWAP_ON_ZERO_V4_SELECTOR[SELECTOR_SIZE] = {0x64, 0x46, 0x68, 0x05};

// Function: swapOnZeroXv2(address fromToken, address toToken, uint256 fromAmount, uint256
// amountOutMin, address exchange, bytes payload)
// Selector: 0x81033120
static const uint8_t PARASWAP_SWAP_ON_ZERO_V2_SELECTOR[SELECTOR_SIZE] = {0x81, 0x03, 0x31, 0x20};
// ---------- End Paraswap V5 -------------

// ---------- Paraswap V4 -------------
// Function : simpleSwap(address fromToken, address toToken, uint256 fromAmount, uint256 toAmount,
// uint256 expectedAmount, address[] callees, bytes exchangeData, uint256[] startIndexes,
// uint256[] values, address beneficiary, string referrer, bool useReduxToken)
// Selector : 0xcfc0afeb
static const uint8_t PARASWAP_SIMPLE_SWAP_V4_SELECTOR[SELECTOR_SIZE] = {0xcf, 0xc0, 0xaf, 0xeb};

// Function: swapOnUniswap(uint256 amountIn, uint256 amountOutMin, address[] path, uint8 referrer)
// Selector: 0x58b9d179
static const uint8_t PARASWAP_SWAP_ON_UNISWAP_V4_SELECTOR[SELECTOR_SIZE] = {0x58, 0xb9, 0xd1, 0x79};

// Function: swapOnUniswapFork(address factory, bytes32 initCode, uint256 amountIn, uint256
// amountOutMin, address[] path, uint8 referrer)
// Selector: 0x0863b7ac
static const uint8_t PARASWAP_SWAP_ON_UNISWAP_FORK_V4_SELECTOR[SELECTOR_SIZE] = {0x08,
                                                                                 0x63,
                                                                                 0xb7,
                                                                                 0xac};

// Function: multiSwap ((address fromToken, uint256 fromAmount, uint256 toAmount, uint256
// expectedAmount, address beneficiary, string referrer, bool useReduxToken,  Utils.Path[] path)))
// Selector: 0x8f00eccb
static const uint8_t PARASWAP_MULTI_SWAP_V4_SELECTOR[SELECTOR_SIZE] = {0x8f, 0x00, 0xec, 0xcb};

// Function: megaSwap ((address fromToken, uint256 fromAmount, uint256 toAmount, uint256
// expectedAmount, address beneficiary, string referrer, bool useReduxToken,  Utils.Path[] path)))
// Selector: 0xec1d21dd
static const uint8_t PARASWAP_MEGA_SWAP_V4_SELECTOR[SELECTOR_SIZE] = {0xec, 0x1d, 0x21, 0xdd};

// Function : buy(address fromToken, address toToken, uint256 fromAmount, uint256 toAmount,
//            address beneficiary, string referrer, bool useReduxToken, Utils.BuyRoute[] route)
// Selector: 0xf95a49eb
static const uint8_t PARASWAP_BUY_SELECTOR[SELECTOR_SIZE] = {0xf9, 0x5a, 0x49, 0xeb};

// Function: buyOnUniswap(uint256 amountInMax, uint256 amountOut, address[] path, uint8 referrer)
// Selector: 0xf9355f72
static const uint8_t PARASWAP_BUY_ON_UNISWAP_V4_SELECTOR[SELECTOR_SIZE] = {0xf9, 0x35, 0x5f, 0x72};

// Function: buyOnUniswapFork(address factory, bytes32 initCode, uint256 amountInMax, uint256
// amountOut, address[] path, uint8 referrer)
// Selector: 0x33635226
static const uint8_t PARASWAP_BUY_ON_UNISWAP_FORK_V4_SELECTOR[SELECTOR_SIZE] = {0x33,
                                                                                0x63,
                                                                                0x52,
                                                                                0x26};

// ---------- End Paraswap V4 -------------

// Array of all the different paraswap selectors.
const uint8_t *const PARASWAP_SELECTORS[NUM_PARASWAP_SELECTORS] = {
    PARASWAP_SWAP_ON_UNISWAP_SELECTOR,
    PARASWAP_BUY_ON_UNISWAP_SELECTOR,
    PARASWAP_SWAP_ON_UNISWAP_FORK_SELECTOR,
    PARASWAP_BUY_ON_UNISWAP_FORK_SELECTOR,
    PARASWAP_SIMPLE_SWAP_SELECTOR,
    PARASWAP_SIMPLE_BUY_SELECTOR,
    PARASWAP_MULTI_SWAP_SELECTOR,
    PARASWAP_BUY_SELECTOR,
    PARASWAP_MEGA_SWAP_SELECTOR,
    PARASWAP_SWAP_ON_ZERO_V4_SELECTOR,
    PARASWAP_SWAP_ON_ZERO_V2_SELECTOR,
    PARASWAP_SIMPLE_SWAP_V4_SELECTOR,
    PARASWAP_SWAP_ON_UNISWAP_V4_SELECTOR,
    PARASWAP_SWAP_ON_UNISWAP_FORK_V4_SELECTOR,
    PARASWAP_MULTI_SWAP_V4_SELECTOR,
    PARASWAP_MEGA_SWAP_V4_SELECTOR,
    PARASWAP_BUY_ON_UNISWAP_V4_SELECTOR,
    PARASWAP_BUY_ON_UNISWAP_FORK_V4_SELECTOR};

// Paraswap uses `0xeeeee` as a dummy address to represent ETH.
const uint8_t PARASWAP_ETH_ADDRESS[ADDRESS_LENGTH] = {0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
                                                      0xee, 0xee, 0xee, 0xee, 0xee, 0xee, 0xee,
                                                      0xee, 0xee, 0xee, 0xee, 0xee, 0xee};

// Used to indicate that the beneficiary should be the sender.
const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void paraswap_plugin_call(int message, void *parameters) {
    switch (message) {
        case ETH_PLUGIN_INIT_CONTRACT:
            handle_init_contract(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_PARAMETER:
            handle_provide_parameter(parameters);
            break;
        case ETH_PLUGIN_FINALIZE:
            handle_finalize(parameters);
            break;
        case ETH_PLUGIN_PROVIDE_TOKEN:
            handle_provide_token(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_ID:
            handle_query_contract_id(parameters);
            break;
        case ETH_PLUGIN_QUERY_CONTRACT_UI:
            handle_query_contract_ui(parameters);
            break;
        default:
            PRINTF("Unhandled message %d\n", message);
            break;
    }
}

void call_app_ethereum() {
    unsigned int libcall_params[3];
    libcall_params[0] = (unsigned int) "Ethereum";
    libcall_params[1] = 0x100;
    libcall_params[2] = RUN_APPLICATION;
    os_lib_call((unsigned int *) &libcall_params);
}

__attribute__((section(".boot"))) int main(int arg0) {
    // exit critical section
    __asm volatile("cpsie i");

    // ensure exception will work as planned
    os_boot();

    // Try catch block. Please read the docs for more information on how to use those!
    BEGIN_TRY {
        TRY {
            // Low-level black magic.
            check_api_level(CX_COMPAT_APILEVEL);
            // Check if we are called from the dashboard.
            if (!arg0) {
                // called from dashboard, launch Ethereum app
                call_app_ethereum();
                return 0;
            } else {
                // Not called from dashboard: called from the ethereum app!
                const unsigned int *args = (unsigned int *) arg0;

                // If `ETH_PLUGIN_CHECK_PRESENCE` is set, this means the caller is just trying to
                // know whether this app exists or not. We can skip `paraswap_plugin_call`.
                if (args[0] != ETH_PLUGIN_CHECK_PRESENCE) {
                    paraswap_plugin_call(args[0], (void *) args[1]);
                }
                os_lib_end();
            }
        }
        FINALLY {
        }
    }
    END_TRY;

    return 0;
}
