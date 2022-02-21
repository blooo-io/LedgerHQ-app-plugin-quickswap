#include "quickswap_plugin.h"

// Function: swapExactTokensForTokens(uint256 amountIn, uint256 amountOutMin, address[] path,
// address to, uint256 deadline)
// MethodID: 0x38ed1739
static const uint8_t SWAP_EXACT_TOKENS_FOR_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x38,
                                                                             0xed,
                                                                             0x17,
                                                                             0x39};

// Function: swapExactTokensForETH(uint256 amountIn, uint256 amountOutMin, address[] path, address
// to, uint256 deadline)
// MethodID: 0x18cbafe5
static const uint8_t SWAP_EXACT_TOKENS_FOR_ETH_SELECTOR[SELECTOR_SIZE] = {0x18, 0xcb, 0xaf, 0xe5};

// Function: swapExactETHForTokens(uint256 amountOutMin, address[] path, address to, uint256
// deadline)
// MethodID : 0x7ff36ab5
static const uint8_t SWAP_EXACT_ETH_FOR_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x7f, 0xf3, 0x6a, 0xb5};

// Function: swapTokensForExactTokens(uint256 amountOut, uint256 amountInMax, address[] path,
// address to, uint256 deadline)
// MethodID : 0x8803dbee
static const uint8_t SWAP_TOKENS_FOR_EXACT_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x88,
                                                                             0x03,
                                                                             0xdb,
                                                                             0xee};

// Function: swapExactTokensForTokensSupportingFeeOnTransferTokens(uint256 amountIn, uint256
// amountOutMin, address[] path, address to, uint256 deadline)
// MethodID: 0x5c11d795
static const uint8_t
    SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x5c,
                                                                                              0x11,
                                                                                              0xd7,
                                                                                              0x95};

// Function: swapETHForExactTokens(uint256 amountOut, address[] path, address to, uint256 deadline)
// MethodID: 0xfb3bdb41
static const uint8_t SWAP_ETH_FOR_EXACT_TOKENS_SELECTOR[SELECTOR_SIZE] = {0xfb, 0x3b, 0xdb, 0x41};

// Function: swapExactTokensForETHSupportingFeeOnTransferTokens(uint256 amountIn, uint256
// amountOutMin, address[] path, address to, uint256 deadline)
// MethodID: 0x791ac947
static const uint8_t
    SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR[SELECTOR_SIZE] = {0x79,
                                                                                           0x1a,
                                                                                           0xc9,
                                                                                           0x47};

// Function: swapTokensForExactETH(uint256 amountOut, uint256 amountInMax, address[] path, address
// to, uint256 deadline)
// MethodID: 0x4a25d94a
static const uint8_t SWAP_TOKENS_FOR_EXACT_ETH_SELECTOR[SELECTOR_SIZE] = {0x4a, 0x25, 0xd9, 0x4a};

// Function: swapExactETHForTokensSupportingFeeOnTransferTokens(uint256 amountOutMin, address[]
// path, address to, uint256 deadline)
// MethodID: 0xb6f9de95
static const uint8_t
    SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR[SELECTOR_SIZE] = {0xb6,
                                                                                           0xf9,
                                                                                           0xde,
                                                                                           0x95};

// Function: addLiquidity(address tokenA, address tokenB, uint256 amountADesired, uint256
// amountBDesired, uint256 amountAMin, uint256 amountBMin, address to, uint256 deadline)
// MethodID: 0xe8e33700
static const uint8_t ADD_LIQUIDITY_SELECTOR[SELECTOR_SIZE] = {0xe8, 0xe3, 0x37, 0x00};

// Function: addLiquidityETH(address token, uint256 amountTokenDesired, uint256 amountTokenMin,
// uint256 amountETHMin, address to, uint256 deadline)
// MethodID: 0xf305d719
static const uint8_t ADD_LIQUIDITY_ETH_SELECTOR[SELECTOR_SIZE] = {0xf3, 0x05, 0xd7, 0x19};

// Function: removeLiquidity(address tokenA, address tokenB, uint256 liquidity, uint256 amountAMin,
// uint256 amountBMin, address to, uint256 deadline)
// MethodID: 0xbaa2abde
static const uint8_t REMOVE_LIQUIDITY_SELECTOR[SELECTOR_SIZE] = {0xba, 0xa2, 0xab, 0xde};

// Function: removeLiquidityETH(address token, uint256 liquidity, uint256 amountTokenMin, uint256
// amountETHMin, address to, uint256 deadline)
// MethodID: 0x02751cec
static const uint8_t REMOVE_LIQUIDITY_ETH_SELECTOR[SELECTOR_SIZE] = {0x02, 0x75, 0x1c, 0xec};

// Function: removeLiquidityWithPermit(address tokenA, address tokenB, uint256 liquidity, uint256
// amountAMin, uint256 amountBMin, address to, uint256 deadline, bool approveMax, uint8 v, bytes32
// r, bytes32 s)
// MethodID: 0x2195995c
static const uint8_t REMOVE_LIQUIDITY_WITH_PERMIT_SELECTOR[SELECTOR_SIZE] = {0x21,
                                                                             0x95,
                                                                             0x99,
                                                                             0x5c};

// Function: removeLiquidityETHWithPermit(address token, uint256 liquidity, uint256 amountTokenMin,
// uint256 amountETHMin, address to, uint256 deadline, bool approveMax, uint8 v, bytes32 r, bytes32
// s)
// MethodID: 0xded9382a
static const uint8_t REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SELECTOR[SELECTOR_SIZE] = {0xde,
                                                                                 0xd9,
                                                                                 0x38,
                                                                                 0x2a};

// Function: removeLiquidityETHSupportingFeeOnTransferTokens(address token, uint256 liquidity,
// uint256 amountTokenMin, uint256 amountETHMin, address to, uint256 deadline)
// MethodID: 0xaf2979eb
static const uint8_t REMOVE_LIQUIDITY_ETH_SUPPORTING_FEE_ON_TRANSFER_SELECTOR[SELECTOR_SIZE] = {
    0xaf,
    0x29,
    0x79,
    0xeb};

// Function: removeLiquidityETHWithPermitSupportingFeeOnTransferTokens(address token, uint256
// liquidity, uint256 amountTokenMin, uint256 amountETHMin, address to, uint256 deadline, bool
// approveMax, uint8 v, bytes32 r, bytes32 s)
// MethodID: 0x5b0d5984
static const uint8_t
    REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR[SELECTOR_SIZE] =
        {0x5b, 0x0d, 0x59, 0x84};

// Array of all the different quickswap selectors.
const uint8_t *const QUICKSWAP_SELECTORS[NUM_QUICKSWAP_SELECTORS] = {
    SWAP_EXACT_TOKENS_FOR_TOKENS_SELECTOR,
    SWAP_EXACT_TOKENS_FOR_ETH_SELECTOR,
    SWAP_EXACT_ETH_FOR_TOKENS_SELECTOR,
    SWAP_TOKENS_FOR_EXACT_TOKENS_SELECTOR,
    SWAP_EXACT_TOKENS_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    SWAP_ETH_FOR_EXACT_TOKENS_SELECTOR,
    SWAP_EXACT_TOKENS_FOR_ETH_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    SWAP_TOKENS_FOR_EXACT_ETH_SELECTOR,
    SWAP_EXACT_ETH_FOR_TOKENS_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR,
    ADD_LIQUIDITY_SELECTOR,
    ADD_LIQUIDITY_ETH_SELECTOR,
    REMOVE_LIQUIDITY_SELECTOR,
    REMOVE_LIQUIDITY_ETH_SELECTOR,
    REMOVE_LIQUIDITY_WITH_PERMIT_SELECTOR,
    REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SELECTOR,
    REMOVE_LIQUIDITY_ETH_SUPPORTING_FEE_ON_TRANSFER_SELECTOR,
    REMOVE_LIQUIDITY_ETH_WITH_PERMIT_SUPPORTING_FEE_ON_TRANSFER_TOKENS_SELECTOR};

// QuickSwap uses `0xeeeee` as a dummy address to represent ETH.
const uint8_t QUICKSWAP_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                       0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                       0x00, 0x00, 0x00, 0x00, 0x10, 0x10};

// Used to indicate that the beneficiary should be the sender.
const uint8_t NULL_ETH_ADDRESS[ADDRESS_LENGTH] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                                  0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
