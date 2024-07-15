#include <iostream>
#include <unordered_map>
#include <string>

class Account {
protected:
    std::string accountNumber;
    double balance;

public:
    Account(const std::string& accNum, double initialBalance)
        : accountNumber(accNum), balance(initialBalance) {}

    virtual void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
            std::cout << "Deposited: " << amount << "\n";
        } else {
            std::cout << "Invalid deposit amount\n";
        }
    }

    virtual void withdraw(double amount) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            std::cout << "Withdrew: " << amount << "\n";
        } else {
            std::cout << "Invalid withdrawal amount or insufficient funds\n";
        }
    }

    void checkBalance() const {
        std::cout << "Account Number: " << accountNumber << ", Balance: " << balance << "\n";
    }

    std::string getAccountNumber() const {
        return accountNumber;
    }
};

class SavingsAccount : public Account {
public:
    SavingsAccount(const std::string& accNum, double initialBalance)
        : Account(accNum, initialBalance) {}

    void deposit(double amount) override {
        const double interestRate = 0.02;
        double interest = amount * interestRate;
        balance += (amount + interest);
        std::cout << "Deposited: " << amount << " with interest: " << interest << "\n";
    }
};

class CheckingAccount : public Account {
public:
    CheckingAccount(const std::string& accNum, double initialBalance)
        : Account(accNum, initialBalance) {}

    void withdraw(double amount) override {
        const double transactionFee = 1.00;
        if (amount + transactionFee <= balance) {
            balance -= (amount + transactionFee);
            std::cout << "Withdrew: " << amount << " with transaction fee: " << transactionFee << "\n";
        } else {
            std::cout << "Invalid withdrawal amount or insufficient funds\n";
        }
    }
};

class Bank {
private:
    std::unordered_map<std::string, Account*> accounts;

public:
    ~Bank() {
        for (auto& pair : accounts) {
            delete pair.second;
        }
    }

    void openSavingsAccount(const std::string& accNum, double initialBalance) {
        accounts[accNum] = new SavingsAccount(accNum, initialBalance);
        std::cout << "Opened savings account with number: " << accNum << "\n";
    }

    void openCheckingAccount(const std::string& accNum, double initialBalance) {
        accounts[accNum] = new CheckingAccount(accNum, initialBalance);
        std::cout << "Opened checking account with number: " << accNum << "\n";
    }

    Account* getAccount(const std::string& accNum) {
        if (accounts.find(accNum) != accounts.end()) {
            return accounts[accNum];
        } else {
            std::cout << "Account not found\n";
            return nullptr;
        }
    }

    void listAccounts() {
        for (const auto& pair : accounts) {
            std::cout << "Account Number: " << pair.first << "\n";
        }
    }
};

void showMenu() {
    std::cout << "\nBanking System Menu:\n";
    std::cout << "1. Open Savings Account\n";
    std::cout << "2. Open Checking Account\n";
    std::cout << "3. Deposit\n";
    std::cout << "4. Withdraw\n";
    std::cout << "5. Check Balance\n";
    std::cout << "6. List Accounts\n";
    std::cout << "7. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Bank bank;
    int choice;
    std::string accountNumber;
    double amount;

    while (true) {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter initial balance: ";
                std::cin >> amount;
                bank.openSavingsAccount(accountNumber, amount);
                break;
            case 2:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter initial balance: ";
                std::cin >> amount;
                bank.openCheckingAccount(accountNumber, amount);
                break;
            case 3:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter deposit amount: ";
                std::cin >> amount;
                if (Account* acc = bank.getAccount(accountNumber)) {
                    acc->deposit(amount);
                }
                break;
            case 4:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                std::cout << "Enter withdrawal amount: ";
                std::cin >> amount;
                if (Account* acc = bank.getAccount(accountNumber)) {
                    acc->withdraw(amount);
                }
                break;
            case 5:
                std::cout << "Enter account number: ";
                std::cin >> accountNumber;
                if (Account* acc = bank.getAccount(accountNumber)) {
                    acc->checkBalance();
                }
                break;
            case 6:
                bank.listAccounts();
                break;
            case 7:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
