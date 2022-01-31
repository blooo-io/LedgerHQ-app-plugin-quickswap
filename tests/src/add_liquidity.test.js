import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "addLiquidity"; // <= Name of the test
const testDirSuffix = "add_liquidity"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x7fa92d865c689c31896422854f10cf8eba29f99a06cbb9b0815a14f5fe33f998

const inputData = "0xe8e337000000000000000000000000000d500b1d8e8ef31e21c99d1db9a6444d3adf1270000000000000000000000000580a84c73811e1839f75d86d75d88cca0c241ff400000000000000000000000000000000000000000000000011f5894729623df10000000000000000000000000000000000000000000000001bc1a3c8854f00b800000000000000000000000000000000000000000000000011de8c6e7c6078820000000000000000000000000000000000000000000000001b9e1c907a66ed83000000000000000000000000a262c24a656f74d5309dbc1588e9f7b7093f27950000000000000000000000000000000000000000000000000000000061f7ad09";

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
