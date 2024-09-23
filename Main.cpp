#include <iostream>
#include <limits>

// Class BankAccount
class BankAccount
{
private:
    double balance;

public:
    explicit BankAccount(double initial_balance) : balance(initial_balance) {}

    virtual void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            std::cout << "Deposit successful! Current balance: " << balance << std::endl;
        }
        else
        {
            std::cout << "Invalid deposit amount!" << std::endl;
        }
    }

    virtual void withdraw(double amount) = 0; // Virtual FFunction

    void checkBalance() const
    {
        std::cout << "Current balance: " << balance << std::endl;
    }

    double getBalance() const
    {
        return balance;
    }

protected:
    void setBalance(double newBalance)
    {
        balance = newBalance;
    }
};
// System Clear, Pause, Numeric Checker
void SystemClear()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
};

void SystemPause()
{
#ifdef _WIN32
    system("pause");
#else
    std::cin.get();
#endif
}

void getValidAmount(double &amount)
{
    while (true)
    {
        std::cout << "\nEnter amount: ";
        std::cin >> amount;

        // Check for valid input
        if (std::cin.fail() || amount < 0)
        {
            std::cin.clear();                                                   
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
            std::cout << "Invalid input! Please enter a valid positive numeric amount." << std::endl;
        }
        else
        {
            
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
    }
}

// SavingsAccount Class
class SavingsAccount : public BankAccount
{
private:
    const double MIN_BALANCE = 1000.0;

public:
    SavingsAccount(double initialBalance) : BankAccount(initialBalance) {}

    void withdraw(double amount) override
    {
        if (amount > 0 && getBalance() - amount >= MIN_BALANCE)
        {
            setBalance(getBalance() - amount);
            std::cout << "Withdrawal successful! Current balance: " << getBalance() << std::endl;
        }
        else if (getBalance() - amount < MIN_BALANCE)
        {
            std::cout << "Insufficient balance! Minimum balance of " << MIN_BALANCE << " must be maintained." << std::endl;
        }
        else
        {
            std::cout << "Invalid withdrawal amount!" << std::endl;
        }
    }
};

// CurrentAccount Class
class CurrentAccount : public BankAccount
{
public:
    CurrentAccount(double initialBalance) : BankAccount(initialBalance) {}

    void withdraw(double amount) override
    {
        if (amount > 0 && getBalance() >= amount)
        {
            setBalance(getBalance() - amount);
            std::cout << "Withdrawal successful! Current balance: " << getBalance() << std::endl;
        }
        else if (getBalance() < amount)
        {
            std::cout << "Insufficient balance!" << std::endl;
        }
        else
        {
            std::cout << "Invalid withdrawal amount!" << std::endl;
        }
    }
};

// Sub-Menu-Savings-Current
void accountMenu(BankAccount &account)
{
    int subChoice;
    bool condition = false;
    double amount;

    while (!condition)
    {
        std::cout << "\nSub Menu\n";
        std::cout << "1 - Deposit\n";
        std::cout << "2 - Withdraw\n";
        std::cout << "3 - Check Balance\n";
        std::cout << "4 - Back\n";
        std::cout << "Enter your choice: ";
        std::cin >> subChoice;

        switch (subChoice)
        {
        case 1:
            SystemClear();
            std::cout << "Enter amount to deposit: ";
            getValidAmount(amount);
            account.deposit(amount);
            break;
        case 2:
            SystemClear();
            account.checkBalance();
            std::cout << "Enter amount to withdraw: ";
            getValidAmount(amount);
            account.withdraw(amount);
            break;
        case 3:
            SystemClear();
            account.checkBalance();
            break;
        case 4:
            SystemClear();
            condition = true;
            break;
        default:
            std::cin.clear();

            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin.ignore();
            SystemPause();
            SystemClear();
            break;
        }
    }
}

// Main Menu
void menu()
{
    int choice;
    bool running = true;

    SavingsAccount savings(1000.0);
    CurrentAccount current(1000.0);

    while (running)
    {
        std::cout << "\nMain Menu\n";
        std::cout << "1 - Savings Account\n";
        std::cout << "2 - Current Account\n";
        std::cout << "3 - Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            SystemClear();
            accountMenu(savings);
            break;

        case 2:
            SystemClear();
            accountMenu(current);
            break;

        case 3:
            SystemClear();
            std::cout << "Exiting program.\n";
            running = false;
            break;

        default:
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please try again.\n";
            std::cin.ignore();
            SystemPause();
            SystemClear();
            break;
        }
    }
}

int main()
{
    menu();
    return 0;
}
