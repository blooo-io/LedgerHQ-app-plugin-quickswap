import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapETHForExactTokens"; // <= Name of the test
const testDirSuffix = "swap_eth_for_exact_tokens"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;
const value = "35.325471452788314635";

// From: https://polygonscan.com/tx/0xe44661112fc3617c7220568faf1e2706b104df97def86908bc83bc29aef10a30
const inputData = "0xfb3bdb410000000000000000000000000000000000000000000000000000000004a0d850000000000000000000000000000000000000000000000000000000000000008000000000000000000000000028e5090405232336ebc1eda14511af7c315c560800000000000000000000000000000000000000000000000000000000c3c30a5500000000000000000000000000000000000000000000000000000000000000020000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf12700000000000000000000000002791bca1f2de4661ed88a30c99a7a9449aa84174"

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 11, // <= Define the number of steps for this test case and this device
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
