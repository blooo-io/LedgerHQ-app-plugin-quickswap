import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapExactTokensForTokensSupportingFeeOnTransferTokens"; // <= Name of the test
const testDirSuffix = "swap_exact_tokens_for_tokens_supporting_fee_on_transfer_tokens"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x4d8c633ef143f708ebcb1b967c0d39d6e575aeb65bc89f39cae29e5e6135676a
const inputData = "0x5c11d79500000000000000000000000000000000000000000000000f43a37de158ea800000000000000000000000000000000000000000000000000000000000055cca5b00000000000000000000000000000000000000000000000000000000000000a00000000000000000000000001c51846968f9c3e72b1c736e856d98c45573b8bd0000000000000000000000000000000000000000000000000000000061f2a50a00000000000000000000000000000000000000000000000000000000000000020000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf12700000000000000000000000002791bca1f2de4661ed88a30c99a7a9449aa84174";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 11, // <= Define the number of steps for this test case and this device
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

