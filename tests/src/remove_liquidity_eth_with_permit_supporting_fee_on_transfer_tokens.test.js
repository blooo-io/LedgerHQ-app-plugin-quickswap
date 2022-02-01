import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "removeLiquidityETHWithPermitSupportingFeeOnTransferTokens"; // <= Name of the test
const testDirSuffix = "remove_liquidity_eth_with_permit_supporting_fee_on_transfer_tokens"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0x8a7812c99c758919b73854d004afe1f3ef85e644b879059810e79fd3581d3f3c

const inputData = "0x5b0d59840000000000000000000000002791bca1f2de4661ed88a30c99a7a9449aa8417400000000000000000000000000000000000000000000000000007d76e757c84a000000000000000000000000000000000000000000000000000000001562b3e400000000000000000000000000000000000000000000000c48c4194d3e0f6e34000000000000000000000000821dd9b7e8b882ccaf50e23bc6b3e224212718a70000000000000000000000000000000000000000000000000000000061f7f7320000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001c325ee28ffba040f6c062504e9f77819d0aebe20c2a06a8567ea80041f9697943670d67d3ba8cec231e015122062905aa6b1751106d373fb89647b95e05c1ca67";

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
