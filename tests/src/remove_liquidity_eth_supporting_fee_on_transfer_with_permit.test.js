import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "removeLiquidityETHSupportingFeeOnTransferTokens"; // <= Name of the test
const testDirSuffix = "remove_liquidity_eth_supporting_fee_on_transfer_with_permit"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x3092e9ece50fa0365b767fbc74c5763c1fc4882516b668a4e347750978c8bf1b

const inputData = "0xaf2979eb000000000000000000000000b932d203f83b8417be0f61d9dafad09cc24a471500000000000000000000000000000000000000000000000bf74d6cdc827250fe00000000000000000000000000000000000000000000000228a0f3f658d0374600000000000000000000000000000000000000000000004bf086ed404e03a968000000000000000000000000d2bc3f00f8b5dd1159708ada58b42a2b3adb1eea0000000000000000000000000000000000000000000000000000000061e77a45";

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
