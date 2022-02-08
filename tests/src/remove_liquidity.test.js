import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "removeLiquidity"; // <= Name of the test
const testDirSuffix = "remove_liquidity"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x610210746baf5f5c82a1500b908ffd50e5eee1788e7a4a8113753261c82ba6c0

const inputData = "0xbaa2abde0000000000000000000000002791bca1f2de4661ed88a30c99a7a9449aa84174000000000000000000000000385eeac5cb85a38a9a07a70c73e0a3271cfb54a700000000000000000000000000000000000000000000000000041541a5b4b9cb0000000000000000000000000000000000000000000000000000001112fb37d80000000000000000000000000000000000000000000007dd020b9b0f3b2b8e69000000000000000000000000071d217637b6322a7faac6895a9eb00e529d34240000000000000000000000000000000000000000000000000000000061f7568f";

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
        steps: 8, // <= Define the number of steps for this test case and this device
    },
];

devices.forEach((device) =>
    processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork)
);
