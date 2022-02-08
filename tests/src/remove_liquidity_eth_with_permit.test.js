import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "removeLiquidityETHWithPermit"; // <= Name of the test
const testDirSuffix = "remove_liquidity_eth_with_permit"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x4805fdb5d1517e59851f11be6b682231d44b2e49bf7950880a41b4b6ba89a18f

const inputData = "0xded9382a000000000000000000000000bbba073c31bf03b8acf7c28ef0738decf369568300000000000000000000000000000000000000000000000274a622d3840d6075000000000000000000000000000000000000000000000001987b7a4f6ef8ba7d000000000000000000000000000000000000000000000003e4f128aa03c594bc000000000000000000000000c1821e3cc4862005b9e397388d0a971b9ffe17350000000000000000000000000000000000000000000000000000000061f813150000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001c8dbb5ff8bb19ac1246e06d5d7d5afa589adcd60492e21714f22f315fc7f48ff20f269606c9f23dcfc08f8d264be66a2ff17efdd77d611d2da2d3a66e1b3dbc09";

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
