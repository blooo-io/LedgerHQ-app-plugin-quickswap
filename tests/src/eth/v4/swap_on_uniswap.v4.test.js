import { processTest } from "../../test.fixture";

const contractName = "Paraswap V4";
// From : https://etherscan.io/tx/0x6b6aeef79fc7e295109fd6dd6f614753e30996a8ac1d5c15269c440c4c768df5
const rawTxHex =
  "0xf9014a30850bdfd63e0083029fb2941bd435f3c054b6e901b7b108a0ab7617c808677b80b8e458b9d179000000000000000000000000000000000000000000000007dc477bc1cfa4000000000000000000000000000000000000000000000000000003ee127868deef220000000000000000000000000000000000000000000000000000000000000080000000000000000000000000000000000000000000000000000000000000000100000000000000000000000000000000000000000000000000000000000000020000000000000000000000000b38210ea11411557c13457d4da7dc6ea731b88a000000000000000000000000eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee26a022380972064ddd3aef0178dec7f1a2542df6ad8c5d95ccd6e29d6f0e0a3f938ca04343dcc66bf041170803672fd96d6d7b2030c0bb3ecd3069e247475f30edc9ec";
const testLabel = "Swap On Uniswap"; // <= Name of the test
const testDirSuffix = "swap_on_uniswap_v4"; // <= directory to compare device snapshots to
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
