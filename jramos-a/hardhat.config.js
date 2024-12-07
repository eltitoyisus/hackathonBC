require('@nomiclabs/hardhat-waffle');
require('@nomiclabs/hardhat-ethers');

// Replace these with your own values
const { mnemonic, infuraProjectId } = require('./secrets.json');

module.exports = {
  solidity: "0.8.0", // Match the version of your contract
  networks: {
    hardhat: {
      chainId: 31337 // Hardhat local network ID
    },
    arbitrumSepolia: {
      url: `https://sepolia.arbitrum.io/rpc`,
      accounts: { mnemonic: mnemonic }
    }
  }
};