import { processTest } from "../../test.fixture";

const contractName = "Paraswap V5";
// From : https://etherscan.io/tx/0x5a0912bcaa6252b5a1349dc1f53279983c1b1e290d3c1457cd6d8689fd6e6cfe
const rawTxHex =
  "0x02f9017c01823044849502f900851d31d51fd683028b2494def171fe48cf0115b1d80b88dc8eab59176fee578814ebb29b0ccbda64b90104c03786b0000000000000000000000000c0aee478e3658e2610c5f7a4a2e1777ce9e4f2ace18a34eb0e04b04f7a0ac29a6e80748dca96319b42c54d679cb821dca90c630300000000000000000000000000000000000000000000000014ebb29b0ccbda640000000000000000000000000000000000000000000000424574f1f86b49000000000000000000000000000000000000000000000000000000000000000000a00000000000000000000000000000000000000000000000000000000000000002000000000000000000000000eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee0000000000000000000000004104b135dbc9609fc1a9490e61369036497660c8c001a0b57599150493405ea7216b9f63648788dc86eff43d3b77cce71d5f76bf41ae02a06dfed183b80740e42dc768dc6eb57ed0d3a8bfc8690703f0135c8afa711e342d";
const testLabel = "Buy On Uniswap Fork"; // <= Name of the test
const testDirSuffix = "buy_on_uniswap_fork"; // <= directory to compare device snapshots to
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
