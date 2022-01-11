import { processTest } from "../../test.fixture";

const contractName = "Paraswap V4";
// From : https://etherscan.io/tx/0x30f033eae4ef9f426b934b7b494de6ca839cd45f6fc3390690ff894fa6519ec4
const rawTxHex =
  "0xf901ad8202ce850c570bd20083035127941bd435f3c054b6e901b7b108a0ab7617c808677b80b901440863b7ac000000000000000000000000c0aee478e3658e2610c5f7a4a2e1777ce9e4f2ace18a34eb0e04b04f7a0ac29a6e80748dca96319b42c54d679cb821dca90c63030000000000000000000000000000000000000000000000000b08c97b24f59c87000000000000000000000000000000000000000000000000000000004848291500000000000000000000000000000000000000000000000000000000000000c000000000000000000000000000000000000000000000000000000000000000010000000000000000000000000000000000000000000000000000000000000003000000000000000000000000dbdb4d16eda451d0503b854cf79d55697f90c8df000000000000000000000000c02aaa39b223fe8d0a0e5c4f27ead9083c756cc2000000000000000000000000a0b86991c6218b36c1d19d4a2e9eb0ce3606eb4826a0649856a7c253e327433f667c4816f3eb616f57c74bd95fe2f7c70b5b51d4e1e1a023227729bf28bfaa85706e738447f3c953ea6f07a6869f616d0a898ff4ca99db";
const testLabel = "Swap On Uniswap Fork"; // <= Name of the test
const testDirSuffix = "swap_on_uniswap_fork_v4"; // <= directory to compare device snapshots to
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
