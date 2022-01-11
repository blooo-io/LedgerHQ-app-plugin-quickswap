import { processTest } from "../../test.fixture";

const contractName = "Paraswap V4";
// From : https://etherscan.io/tx/0x74cf3c6bcdcdd2db5998e7b2836456d40c238fcb6d4d0db0776e2f3a16c49b88
const rawTxHex =
  "0xf9014c8205b885028fa6ae008303375e941bd435f3c054b6e901b7b108a0ab7617c808677b80b8e4f9355f72000000000000000000000000000000000000000000000003dacc12f3fe33b468000000000000000000000000000000000000000000000000063c63848f37478e000000000000000000000000000000000000000000000000000000000000008000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000002000000000000000000000000de30da39c46104798bb5aa3fe8b9e0e1f348163f000000000000000000000000eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee26a0e340f76fa1762f684a11b578b17e19be63ad3fd70f4e30cb0e4878c5da0abff9a0158cb6914abc788bc545908679d21e2ddf50f43887259ba74537c87b62d599d0";
const testLabel = "Buy On Uniswap"; // <= Name of the test
const testDirSuffix = "buy_on_uniswap_v4"; // <= directory to compare device snapshots to
const testNetwork = "eth"; 
const signedPlugin = true; // <== set to true if the plugin is already signed and available
const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 8, // <= Define the number of steps for this test case and this device
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
