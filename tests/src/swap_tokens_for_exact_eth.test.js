import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapTokensForExactEth"; // <= Name of the test
const testDirSuffix = "swap_tokens_for_exact_eth"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x55541772baa4664f2698b43e49f0795e8272476ee1ea4584675d2c7d469ce51b

const inputData = "0x4a25d94a0000000000000000000000000000000000000000000000a29f48211d0f90000000000000000000000000000000000000000000000000004eec3e2abaddf8000000000000000000000000000000000000000000000000000000000000000000a000000000000000000000000084e45c018e1ab000ebe00c12bb58a9caabb6dc440000000000000000000000000000000000000000000000000000000061f425180000000000000000000000000000000000000000000000000000000000000002000000000000000000000000bbba073c31bf03b8acf7c28ef0738decf36956830000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf1270";
// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 13, // <= Define the number of steps for this test case and this device
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
