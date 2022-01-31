import { processTest, populateTransaction } from "./test.fixture";

const contractName = "QuickSwap";

const testLabel = "removeLiquidityWithPermit"; // <= Name of the test
const testDirSuffix = "remove_liquidity_with_permit"; // <= directory to compare device snapshots to
const testNetwork = "polygon";
const signedPlugin = false;

const contractAddr = "0xa5e0829caced8ffdd4de3c43696c57f7d7a678ff";
const chainID = 137;

// From : https://polygonscan.com/tx/0xa407b137b246a8782d00656cab8baa4fd2679928e62d9ebdcb81dc5ebc6c06c4

const inputData = "0x2195995c0000000000000000000000002791bca1f2de4661ed88a30c99a7a9449aa841740000000000000000000000007ceb23fd6bc0add59e62ac25578270cff1b9f619000000000000000000000000000000000000000000000000000003a8d13b287900000000000000000000000000000000000000000000000000000000127b1a8700000000000000000000000000000000000000000000000001a13baa01e1ab3b00000000000000000000000055dc2cde9388102c7c3dd58884cfa67540f7465c0000000000000000000000000000000000000000000000000000000061f80fa80000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001b4c5577243e360a7595f2da8999d3d861432a113f92391c5c05f0aa1716224d62639368cb89f80cc315d130212d8c1c86c67e06b1d90517cda01700dc056ec3ad";

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
