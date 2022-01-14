import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapExactTokensForTokensSupportingFeeOnTransferTokens"; // <= Name of the test
const testDirSuffix = "swap_exact_tokens_for_tokens_supporting_fee_on_transfer_tokens"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x3b3f958390dc504411eafc62c2cdab2d649d33b4ba51dca9967ef2fe8a0ef81f
const inputData = "0x5c11d7950000000000000000000000000000000000000000000000744bcff5c00f08000000000000000000000000000000000000000000000000000011881ceff1eaadeb00000000000000000000000000000000000000000000000000000000000000a0000000000000000000000000c2dc06aeb55922ffff6e0fb9a42ffc9b1e1dec150000000000000000000000000000000000000000000000000000000061e1423c0000000000000000000000000000000000000000000000000000000000000002000000000000000000000000831753dd7087cac61ab5644b308642cc1c33dc130000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf1270"

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 10, // <= Define the number of steps for this test case and this device
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

