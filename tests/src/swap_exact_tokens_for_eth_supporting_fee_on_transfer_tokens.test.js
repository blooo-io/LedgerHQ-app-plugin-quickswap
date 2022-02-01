import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "swapExactTokensForEthSupportingFeeOnTransferTokens"; // <= Name of the test
const testDirSuffix = "swap_exact_tokens_for_eth_supporting_fee_on_transfer_tokens"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x7c5e599642e85f2c142d0832b9188be3bab6b17d9673d2f36bbec793d599d76b
const inputData = "0x791ac94700000000000000000000000000000000000000000000012a27d53bc0487000000000000000000000000000000000000000000000000000012b1d26e47816ee0e00000000000000000000000000000000000000000000000000000000000000a0000000000000000000000000d21212e80af069e2845aec7bc7ca5ef29002d03400000000000000000000000000000000000000000000000000000000c3e844ff0000000000000000000000000000000000000000000000000000000000000002000000000000000000000000edbe70ef62b74730215728ed6b3f1f8705e3c58b0000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf1270";
//00000000000000000000000000000000000000000000000f43a37de158ea800000000000000000000000000000000000000000000000000000000000055cca5b00000000000000000000000000000000000000000000000000000000000000a00000000000000000000000001c51846968f9c3e72b1c736e856d98c45573b8bd0000000000000000000000000000000000000000000000000000000061f2a50a00000000000000000000000000000000000000000000000000000000000000020000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf12700000000000000000000000002791bca1f2de4661ed88a30c99a7a9449aa84174
// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

const devices = [
    {
        name: "nanos",
        label: "Nano S",
        steps: 12, // <= Define the number of steps for this test case and this device
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

