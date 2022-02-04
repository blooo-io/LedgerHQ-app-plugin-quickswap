import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapExactTokensForTokens"; // <= Name of the test
const testDirSuffix = "swap_exact_tokens_for_tokens"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x7559b9652faefbf468e5f0022cbc09ae72797bf9aeed9cf9dc3431d45d06cd50
const inputData = "0x38ed1739000000000000000000000000000000000000000000000008021c3376b756800000000000000000000000000000000000000000000000000011a8c4755677a40000000000000000000000000000000000000000000000000000000000000000a0000000000000000000000000c6d5ad3c4002a1b48d87b83939698660516ae1420000000000000000000000000000000000000000000000000000000061dfef0e00000000000000000000000000000000000000000000000000000000000000020000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf1270000000000000000000000000831753dd7087cac61ab5644b308642cc1c33dc13"
// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 13, // <= Define the number of steps for this test case and this device
    },
    {
      name: "nanox",
      label: "Nano X",
      steps: 7, // <= Define the number of steps for this test case and this device
    },
];

devices.forEach((device) =>
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork)
);
