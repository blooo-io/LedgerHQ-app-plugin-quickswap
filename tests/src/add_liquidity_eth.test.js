import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "addLiquidityETH"; // <= Name of the test
const testDirSuffix = "add_liquidity_eth"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x11773a55c31115ac6d10722b9874b141236823ed24d9d376c5134bbec80541bc

const inputData = "0xf305d7190000000000000000000000007ceb23fd6bc0add59e62ac25578270cff1b9f6190000000000000000000000000000000000000000000000000004ecbdbb8517190000000000000000000000000000000000000000000000000004e66ffbdcbea90000000000000000000000000000000000000000000000001eeddb89f78b2ea3000000000000000000000000f48fb2676746809d59a4753767d0cf391d0726200000000000000000000000000000000000000000000000000000000061f7e415";
const value = "2.239878167063678235";

// Create serializedTx and remove the "0x" prefix
const serializedTx = populateTransaction(contractAddr, inputData, chainID, value);

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
