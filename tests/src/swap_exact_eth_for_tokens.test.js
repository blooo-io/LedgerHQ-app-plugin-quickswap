import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapExactETHForTokens"; // <= Name of the test
const testDirSuffix = "swap_exact_eth_for_tokens"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;
// From: https://polygonscan.com/tx/0x7e261dfec5fb59dff3614c614eae7ba75e253c235bd87bc7822871b14ad06923
const inputData = "0x7ff36ab5000000000000000000000000000000000000000000000000000000001c7ec7ea00000000000000000000000000000000000000000000000000000000000000800000000000000000000000001dc122db61d53a8e088d63af743f4d4c713e8a2000000000000000000000000000000000000000000000000000000000c3c084a900000000000000000000000000000000000000000000000000000000000000020000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf12700000000000000000000000002791bca1f2de4661ed88a30c99a7a9449aa84174";
const value = "200";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 9, // <= Define the number of steps for this test case and this device
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
