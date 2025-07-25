# Bank-Management-System
# SHIMZA SAJID
# 💼 Simple Bank Management System in C

A simple console-based **Bank Management System** developed in C language.  
Built as a mini project to demonstrate file handling, user authentication with hidden password input, and transaction logging.

## 🛠 Features

- Create new user accounts
- Secure login with **hidden password (using asterisks)**
- Check balance
- Deposit money
- Withdraw money
- Transfer money to another account
- View transaction history (timestamped)
- Persistent storage using `.dat` and `.txt` files

## 🔐 Login Security

- Password input is hidden with `*` characters using `getch()` from `<conio.h>`.

## 📂 File Structure

- Each account is saved in a separate `.dat` file: `12345.dat`
- Transaction history is logged in a `.txt` file: `12345_history.txt`
<img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/34c8d49a-c9c3-4cb4-a1eb-3cd1cfc73b06" />
<img width="1366" height="768" alt="image" src="https://github.com/user-attachments/assets/37d1e7f6-cfbb-4798-8eae-2bdd55cd6f12" />


## 🖥️ How to Run

### 🧰 Requirements:
- C compiler like `GCC`
- Windows Command Prompt (or compatible terminal for conio.h support)

