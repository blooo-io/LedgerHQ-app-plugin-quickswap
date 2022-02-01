import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapExactTokensForETH"; // <= Name of the test
const testDirSuffix = "swap_exact_tokens_for_eth"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0xf28b2c838a390f56af25405c99bb2e856dab3ea797f8d97c1633b2b5bd9bcdef
const inputData = "0x18cbafe500000000000000000000000000000000000000000000000000000000061326c600000000000000000000000000000000000000000000000249274b959ab0cd8400000000000000000000000000000000000000000000000000000000000000a0000000000000000000000000ca19a1effa79c2db290b115901f2742b80aee06c00000000000000000000000000000000000000000000000000000000c3bfc5d40000000000000000000000000000000000000000000000000000000000000002000000000000000000000000c2132d05d31c914a87c6611c10748aeb04b58e8f0000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf1270"
// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

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
