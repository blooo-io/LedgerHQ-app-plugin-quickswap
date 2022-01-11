import { processTest } from "../../test.fixture";

const contractName = "Paraswap V4";
// From : https://etherscan.io/tx/0xb543fb02efb0890bdff0228c1a41de068d18c4709e254c7d1c3825c28778a996
const rawTxHex =
  "0xf9018d82010f8509c76524008302e7a9941bd435f3c054b6e901b7b108a0ab7617c808677b80b90124336352260000000000000000000000009deb29c9a4c7a88a3c0257393b7f3335338d9a9d69d637e77615df9f235f642acebbdad8963ef35c5523142078c9b8f9d0ceba7e00000000000000000000000000000000000000000000000000000000223efc940000000000000000000000000000000000000000000000000283436748eb996b00000000000000000000000000000000000000000000000000000000000000c000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002000000000000000000000000dac17f958d2ee523a2206206994597c13d831ec7000000000000000000000000eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee26a006d701b9ed2db5d1dc508a021005adb414ae0d4e1bd8150b7e83a2fa5b1d420da023bedbfb8bd274e21337a6af6d177f24b7ef2a22e2af9955fcabcd7623c5d1f9";
const testLabel = "Buy On Uniswap Fork"; // <= Name of the test
const testDirSuffix = "buy_on_uniswap_fork_v4"; // <= directory to compare device snapshots to
const testNetwork = "eth"; 
const signedPlugin = true; // <== set to true if the plugin is already signed and available
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
