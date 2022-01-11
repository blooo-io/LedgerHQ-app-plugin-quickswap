import { processTest } from "../../test.fixture";

const contractName = "Paraswap V5";
// From : https://etherscan.io/tx/0xe7b7b2683b300ba8a096e5ebab88eae13d0e1860ea6e44a439f1a6c454a1c970
const rawTxHex =
  "0x02f901720105845cfbb60085208d534c808302d8f794def171fe48cf0115b1d80b88dc8eab59176fee5780b90104f56610340000000000000000000000009deb29c9a4c7a88a3c0257393b7f3335338d9a9d69d637e77615df9f235f642acebbdad8963ef35c5523142078c9b8f9d0ceba7e0000000000000000000000000000000000000000000000000000000014d2f28e00000000000000000000000000000000000000000000000001581dcf2479497a00000000000000000000000000000000000000000000000000000000000000a00000000000000000000000000000000000000000000000000000000000000002000000000000000000000000dac17f958d2ee523a2206206994597c13d831ec7000000000000000000000000eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeec001a0d6680c8da8c738b49ae62b6fbf562c78bd095284996d509dd765fc07562c7fe6a01d3bd78d9af02c86d126a2a03e78a2c99cfc6f4fc7e631abc099f2bf7b5b1024";
const testLabel = "Swap On Uniswap Fork"; // <= Name of the test
const testDirSuffix = "swap_on_uniswap_fork"; // <= directory to compare device snapshots to
const testNetwork = "eth"; 
const signedPlugin = true;

const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 7, // <= Define the number of steps for this test case and this device
  },
  // {
  //   name: "nanox",
  //   label: "Nano X",
  //   steps: 5, // <= Define the number of steps for this test case and this device
  // },
];

devices.forEach((device) =>
  processTest(device, contractName, testLabel, testDirSuffix, rawTxHex, signedPlugin,"",testNetwork)
);
