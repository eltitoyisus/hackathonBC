// SPDX-License-Identifier: MIT
pragma solidity ^0.8.0;

// Interfaz ERC-20
interface IERC20 {
    function totalSupply() external view returns (uint256);
    function balanceOf(address account) external view returns (uint256);
    function transfer(address recipient, uint256 amount) external returns (bool);
    function allowance(address owner, address spender) external view returns (uint256);
    function approve(address spender, uint256 amount) external returns (bool);
    function transferFrom(address sender, address recipient, uint256 amount) external returns (bool);
    event Transfer(address indexed from, address indexed to, uint256 value);
    event Approval(address indexed owner, address indexed spender, uint256 value);
}

contract FT is IERC20 {
    string public name = "FT Token";  // Nombre del token
    string public symbol = "FT";      // Símbolo del token
    uint8 public decimals = 18;       // Decimales del token
    uint256 private _totalSupply;     // Suministro total

    mapping(address => uint256) private _balances;     // Mapeo de balances
    mapping(address => mapping(address => uint256)) private _allowances;  // Mapeo de aprobaciones

    // Constructor para asignar suministro inicial a la cuenta creadora
    constructor(uint256 initialSupply) {
        _totalSupply = initialSupply * 10 ** uint256(decimals);
        _balances[msg.sender] = _totalSupply;
    }

    // Función para obtener el suministro total
    function totalSupply() external view override returns (uint256) {
        return _totalSupply;
    }

    // Función para obtener el saldo de una cuenta
    function balanceOf(address account) external view override returns (uint256) {
        return _balances[account];
    }

    // Función para transferir tokens
    function transfer(address recipient, uint256 amount) external override returns (bool) {
        require(recipient != address(0), "ERC20: transfer to the zero address");
        require(_balances[msg.sender] >= amount, "ERC20: transfer amount exceeds balance");

        _balances[msg.sender] -= amount;
        _balances[recipient] += amount;

        emit Transfer(msg.sender, recipient, amount);
        return true;
    }

    // Función para aprobar a un tercero a gastar tokens en nombre del dueño
    function approve(address spender, uint256 amount) external override returns (bool) {
        _allowances[msg.sender][spender] = amount;
        emit Approval(msg.sender, spender, amount);
        return true;
    }

    // Función para obtener la cantidad de tokens que un tercero puede gastar en nombre de otro
    function allowance(address owner, address spender) external view override returns (uint256) {
        return _allowances[owner][spender];
    }

    // Función para transferir tokens en nombre de otro
    function transferFrom(address sender, address recipient, uint256 amount) external override returns (bool) {
        require(sender != address(0), "ERC20: transfer from the zero address");
        require(recipient != address(0), "ERC20: transfer to the zero address");
        require(_balances[sender] >= amount, "ERC20: transfer amount exceeds balance");
        require(_allowances[sender][msg.sender] >= amount, "ERC20: transfer amount exceeds allowance");

        _balances[sender] -= amount;
        _balances[recipient] += amount;
        _allowances[sender][msg.sender] -= amount;

        emit Transfer(sender, recipient, amount);
        return true;
    }
}
