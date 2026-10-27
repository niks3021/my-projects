#include <iostream>

class AuditRule;

class BankAccount {
private:
    int accountNo;
    double balance;
    static int successfulTransactions;

public:
    void setAccountDetails(int accNo, double initialBalance);
    bool deposit(double amount);
    bool withdraw(double amount);
    bool transferTo(BankAccount &receiver, double amount);
    void displayAccount();

    static void displayTransactionCount();

    friend void auditAccount(BankAccount acc, AuditRule rule);
};

class AuditRule {
private:
    double minimumRequiredBalance;

public:
    void setRule(double minBal) {
        minimumRequiredBalance = minBal;
    }

    friend void auditAccount(BankAccount acc, AuditRule rule);
};

int BankAccount::successfulTransactions = 0;

void BankAccount::setAccountDetails(int accNo, double initialBalance) {
    accountNo = accNo;
    balance = initialBalance;
}

bool BankAccount::deposit(double amount) {
    if (amount <= 0) {
        std::cout << "Deposit failed: Amount must be positive.\n";
        return false;
    }
    balance += amount;
    successfulTransactions++;
    std::cout << "Successfully deposited Rs. " << amount << " into Account " << accountNo << "\n";
    return true;
}

bool BankAccount::withdraw(double amount) {
    if (amount <= 0) {
        std::cout << "Withdrawal failed: Amount must be positive.\n";
        return false;
    }
    if (amount > balance) {
        std::cout << "Withdrawal failed: Insufficient balance in Account " << accountNo << "\n";
        return false;
    }
    balance -= amount;
    successfulTransactions++;
    std::cout << "Successfully withdrew Rs. " << amount << " from Account " << accountNo << "\n";
    return true;
}

bool BankAccount::transferTo(BankAccount &receiver, double amount) {
    if (amount <= 0) {
        std::cout << "Transfer failed: Amount must be positive.\n";
        return false;
    }
    if (amount > balance) {
        std::cout << "Transfer failed: Insufficient balance in Account " << accountNo << "\n";
        return false;
    }
    balance -= amount;
    receiver.balance += amount;
    successfulTransactions++;
    std::cout << "Successfully transferred Rs. " << amount << " from Account " << accountNo << " to Account " << receiver.accountNo << "\n";
    return true;
}

void BankAccount::displayAccount() {
    std::cout << "Account No: " << accountNo << " | Balance: Rs. " << balance << "\n";
}

void BankAccount::displayTransactionCount() {
    std::cout << "Total Successful Transactions: " << successfulTransactions << "\n";
}

void auditAccount(BankAccount acc, AuditRule rule) {
    std::cout << "Auditing Account " << acc.accountNo << ": ";
    if (acc.balance >= rule.minimumRequiredBalance) {
        std::cout << "PASSED (Balance Rs. " << acc.balance << " >= Required Rs. " << rule.minimumRequiredBalance << ")\n";
    } else {
        std::cout << "FAILED (Balance Rs. " << acc.balance << " < Required Rs. " << rule.minimumRequiredBalance << ")\n";
    }
}

int main() {
    BankAccount acc1, acc2;
    AuditRule rule;

    acc1.setAccountDetails(101, 5000.0);
    acc2.setAccountDetails(102, 1000.0);
    rule.setRule(2000.0);

    std::cout << " Initial Account States \n";
    acc1.displayAccount();
    acc2.displayAccount();
    std::cout << "\n Demonstrating Operations \n";

    acc1.deposit(1500.0);

    acc2.withdraw(3000.0);

    acc2.withdraw(200.0);

    acc1.transferTo(acc2, 2000.0);

    std::cout << "\nStatic Transaction Count\n";
    BankAccount::displayTransactionCount();

    std::cout << "\nAudit Results\n";
    auditAccount(acc1, rule);
    auditAccount(acc2, rule);

    std::cout << "\nFinal Account States\n";
    acc1.displayAccount();
    acc2.displayAccount();

    return 0;
}