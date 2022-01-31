import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapExactETHForTokensSupportingFeeOnTransferTokens"; // <= Name of the test
const testDirSuffix = "swap_exact_eth_for_tokens_supporting_fee_on_transfer_tokens"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;


// From : https://polygonscan.com/tx/0xf3dddb613151fd340717fbb5d5199700c18ea52f240626448fcf15a51f4ca80c
const inputData = "0xb6f9de95000000000000000000000000000000000000000000000000000000001d7a138b00000000000000000000000000000000000000000000000000000000000000800000000000000000000000003b347eae85f49a67b645e06c31b1700bda223fd800000000000000000000000000000000000000000000000000000000c3eec2da00000000000000000000000000000000000000000000000000000000000000020000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf12700000000000000000000000002791bca1f2de4661ed88a30c99a7a9449aa84174";
const value = "321";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 6, // <= Define the number of steps for this test case and this device
    },
    // {
    //   name: "nanox",
    //   label: "Nano X",
    //   steps: 5, // <= Define the number of steps for this test case and this device
    // },
];

devices.forEach((device) =>
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork)
);

