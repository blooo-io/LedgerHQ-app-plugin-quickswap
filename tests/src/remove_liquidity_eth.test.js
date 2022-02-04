import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "removeLiquidityETH"; // <= Name of the test
const testDirSuffix = "remove_liquidity_eth"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x610210746baf5f5c82a1500b908ffd50e5eee1788e7a4a8113753261c82ba6c0

const inputData = "0x02751cec000000000000000000000000d3b71117e6c1558c1553305b44988cd944e9730000000000000000000000000000000000000000000000000305d3509223c7ffff00000000000000000000000000000000000000000000001be42001fd092c69cc000000000000000000000000000000000000000000000000609ca963273f1ecc000000000000000000000000830ad44d0d89dec491c0fc326c9a5ceffba314220000000000000000000000000000000000000000000000000000000061f7517b";

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
      steps: 8, // <= Define the number of steps for this test case and this device
    },
];

devices.forEach((device) =>
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork)
);
