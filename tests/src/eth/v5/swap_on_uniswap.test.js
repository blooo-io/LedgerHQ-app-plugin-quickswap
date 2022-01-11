import { processTest } from "../../test.fixture";

const contractName = "Paraswap V5";
// From : https://etherscan.io/tx/0x4ae6d1fe1d298a6f84eb710cf5fb3107f5646ed3dbbe04a89d869de4e2a6888a
const rawTxHex =
  "0x02f90131010c84625900808532cc8a99008302a53494def171fe48cf0115b1d80b88dc8eab59176fee5780b8c454840d1a00000000000000000000000000000000000000000000027a14a0ff5e40a67d0b0000000000000000000000000000000000000000000000000c16dfffe3c8c66400000000000000000000000000000000000000000000000000000000000000600000000000000000000000000000000000000000000000000000000000000002000000000000000000000000d9016a907dc0ecfa3ca425ab20b6b785b42f2373000000000000000000000000eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeec001a09b996bf896d123a326b3851742e45d9bb60215bd304d1fb38e062a9b8a930c1ea02541f8a2ecd909d6000518b72f27b22aeb94594e0602e933f45859cbc4da8b67";
const testLabel = "Swap On Uniswap"; // <= Name of the test
const testDirSuffix = "swap_on_uniswap"; // <= directory to compare device snapshots to
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
