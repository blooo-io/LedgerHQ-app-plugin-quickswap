import { processTest } from "../../test.fixture";

const contractName = "Paraswap V5";
// From : https://etherscan.io/tx/0x6d92259fc715278a3f44aa88a0147d147e313c5e202fc71580362142bb134aca
const rawTxHex =
  "0x02f9013b0182305e84773594008528b730555d830257bb94def171fe48cf0115b1d80b88dc8eab59176fee578809c55848d4657c8fb8c4935fb84b00000000000000000000000000000000000000000000000009c55848d4657c8f000000000000000000000000000000000000000000000000000000daa12dbdc000000000000000000000000000000000000000000000000000000000000000600000000000000000000000000000000000000000000000000000000000000002000000000000000000000000eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee0000000000000000000000002b591e99afe9f32eaa6214f7b7629768c40eeb39c001a0adc705de9be63a2d4a70ecefe9b65e93b7d22526715df723c2f3bc7fc72d7702a06f91aba422975a0947bc0434578d220c9e13743bfe1fb716784be5e3613c7907";
const testLabel = "Buy On Uniswap"; // <= Name of the test
const testDirSuffix = "buy_on_uniswap"; // <= directory to compare device snapshots to
const testNetwork = "eth"; 

const signedPlugin = true;

const devices = [
  {
    name: "nanos",
    label: "Nano S",
    steps: 9, // <= Define the number of steps for this test case and this device
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
