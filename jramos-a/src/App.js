import React, { useEffect } from 'react';
import './App.css';

function App() {
  useEffect(() => {
    // Initialize staking platform variables
    let balance = 100;
    let staked = 0;
    let rewards = 0;

    // Create and append the main structure
    const body = document.body;

    // Header
    const header = document.createElement('header');
    const h1 = document.createElement('h1');
    h1.textContent = '42 Staking Platform';
    header.appendChild(h1);
    body.appendChild(header);

    // Main content
    const main = document.createElement('main');
    const stakingSection = document.createElement('section');
    stakingSection.classList.add('staking-section');

    // Balance display
    const balanceDiv = document.createElement('div');
    balanceDiv.classList.add('balance');
    const balanceText = document.createElement('p');
    balanceText.innerHTML = `Wallet Balance: <span id="balance">${balance}</span> Tokens`;
    balanceDiv.appendChild(balanceText);

    // Stake form
    const stakeForm = document.createElement('form');
    stakeForm.id = 'stake-form';
    const stakeInput = document.createElement('input');
    stakeInput.type = 'number';
    stakeInput.id = 'stake-amount';
    stakeInput.placeholder = 'Amount to Stake';
    stakeInput.min = '1';
    const stakeButton = document.createElement('button');
    stakeButton.type = 'submit';
    stakeButton.textContent = 'Stake';
    stakeForm.append(stakeInput, stakeButton);

    // Unstake form
    const unstakeForm = document.createElement('form');
    unstakeForm.id = 'unstake-form';
    const unstakeInput = document.createElement('input');
    unstakeInput.type = 'number';
    unstakeInput.id = 'unstake-amount';
    unstakeInput.placeholder = 'Amount to Unstake';
    unstakeInput.min = '1';
    const unstakeButton = document.createElement('button');
    unstakeButton.type = 'submit';
    unstakeButton.textContent = 'Unstake';
    unstakeForm.append(unstakeInput, unstakeButton);

    // Rewards display
    const rewardsDiv = document.createElement('div');
    rewardsDiv.classList.add('rewards');
    const stakedText = document.createElement('p');
    stakedText.innerHTML = `Staked Amount: <span id="staked">${staked}</span> Tokens`;
    const rewardsText = document.createElement('p');
    rewardsText.innerHTML = `Rewards: <span id="rewards">${rewards}</span> Tokens`;
    rewardsDiv.append(stakedText, rewardsText);

    // Append elements to the section
    stakingSection.append(balanceDiv, stakeForm, unstakeForm, rewardsDiv);
    main.appendChild(stakingSection);
    body.appendChild(main);

    // Footer
    const footer = document.createElement('footer');
    footer.innerHTML = `<p>Made with ❤️ and the 42 spirit</p>`;
    body.appendChild(footer);

    // Update the UI dynamically
    const updateUI = () => {
      document.getElementById('balance').textContent = balance;
      document.getElementById('staked').textContent = staked;
      document.getElementById('rewards').textContent = rewards.toFixed(2);
    };

    // Stake and Unstake functionality
    stakeForm.addEventListener('submit', (e) => {
      e.preventDefault();
      const amount = parseFloat(stakeInput.value);
      if (amount > 0 && amount <= balance) {
        balance -= amount;
        staked += amount;
        rewards += amount * 0.05; // 5% reward
        updateUI();
      }
      stakeInput.value = '';
    });

    unstakeForm.addEventListener('submit', (e) => {
      e.preventDefault();
      const amount = parseFloat(unstakeInput.value);
      if (amount > 0 && amount <= staked) {
        balance += amount;
        staked -= amount;
        updateUI();
      }
      unstakeInput.value = '';
    });

    // Initial UI update
    updateUI();
  }, []);

  return null;
}

export default App;