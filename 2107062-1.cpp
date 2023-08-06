#include <iostream>
#include <vector>
#include <string>
//2107062
using namespace std;

class Bank;
class Account
{
    friend class Bank;

protected:
    string name;
    string accountNumber;
    double balance;

public:
    Account(string nam, string accNumber, double initialBalance)
        : name(nam), accountNumber(accNumber), balance(initialBalance) {}

    virtual void deposit(double amount)
    {
        balance += amount;
    }

    virtual bool withdraw(double amount)
    {
        if (amount <= balance)
        {
            balance -= amount;
            return true;
        }
        return false;
    }

    virtual void display()
    {
        cout << " Name: " << name;
        cout << ", Number: " << accountNumber << ", Balance: " << balance << endl;
    }
    friend class Bank;
};

class RegularAccount : public Account
{
public:
    RegularAccount(string nam, string accNumber, double initialBalance)
        : Account(nam, accNumber, initialBalance) {}

    void display() override
    {
        cout << "Regular Account - ";
        Account::display();
    }
};

class SavingsAccount : public Account
{
public:
    SavingsAccount(string nam, string accNumber, double initialBalance)
        : Account(nam, accNumber, initialBalance) {}

    void display() override
    {
        cout << "Savings Account - ";
        Account::display();
    }

    bool withdraw(double amount) override
    {
        if (balance - amount >= 1000)
        {
            balance -= amount;
            return true;
        }
        return false;
    }
};

class Bank
{
private:
    vector<Account *> accounts;

public:
    /*~Bank(){
        for (Account *acc : accounts){
            cout << acc->name << "'s has been deleted with id of " << acc->accountNumber << endl;
            delete acc;
        }
    }*/
    void addAccount(Account *account)
    {
        accounts.push_back(account);
    }
    friend void displayAccounts(Bank bank);
    void deposit(string &accNumber, double amount)
    {
        for (Account *acc : accounts)
        {
            if (acc->accountNumber == accNumber)
            {
                acc->deposit(amount);
                cout << amount << " taka was added to your account\n";
                return;
            }
        }
        cout << "Account not found." << endl;
    }
    bool withdraw(string accNumber, double amount)
    {
        for (Account *acc : accounts)
        {
            if (acc->accountNumber == accNumber)
            {
                return acc->withdraw(amount);
            }
        }
        cout << "Account not found." << endl;
        return false;
    }
};

void displayAccounts(Bank bank)
{
    for (int i = 0; i < bank.accounts.size(); ++i)
    {
        bank.accounts[i]->display();
    }
}

int main()
{
    //   freopen("output.txt", "w", stdout);
    Bank bank;
    /* RegularAccount *acc1 = new RegularAccount("Arif", "1001", 5000);
     SavingsAccount *acc2 = new SavingsAccount("Rohan", "2002", 7000);
     SavingsAccount *acc3 = new SavingsAccount("Rian", "2003", 7000);

     bank.addAccount(acc1);
     bank.addAccount(acc2);
     bank.addAccount(acc3);*/

    int choice;
    string accountNumber;
    double amount;
    string id, nam;
    do
    {
        cout << "Bank Management System" << endl;
        cout << "1. Display Accounts\n2. Deposit\n3. Withdraw\n4. Add \n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            displayAccounts(bank);
            break;

        case 2:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Amount to Deposit: ";
            cin >> amount;
            bank.deposit(accountNumber, amount);
            break;

        case 3:
            cout << "Enter Account Number: ";
            cin >> accountNumber;
            cout << "Enter Amount to Withdraw: ";
            cin >> amount;
            if (bank.withdraw(accountNumber, amount))
            {
                cout << "Withdrawal successful." << endl;
            }
            else
            {
                cout << "Insufficient balance or account not found." << endl;
            }
            break;
        case 4:
            int q;
            cout << "Account Type: (0. Savings 1. Regular)";
            cin >> q;
            cout << "Name: ";
            cin >> nam;
            cout << "ID : ";
            cin >> id;
            if (q)
                bank.addAccount(new RegularAccount(nam, id, 0.0));
            else
                bank.addAccount(new SavingsAccount(nam, id, 0.0));
            break;
        case 0:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;

    } while (choice != 0);

    return 0;
}
