#include <iostream>
#include <limits>
#include <string>
#include <cctype>

// Class BankAccount
class BankAccount
{
private:
    double balance;

public:
    explicit BankAccount(double initial_balance) : balance(initial_balance) {}

    // Vitual function for deposit
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

    // Virtual function for withdraw
    virtual void withdraw(double amount) = 0;

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

// Check if input is number, check decimal, if empty
bool isValidNumericString(const std::string &input)
{
    bool Decimal = false;

    for (char ch : input)
    {
        if (ch == '.')
        {
            if (Decimal)
            {
                return false;
            }
            Decimal = true;
        }
        else if (!isdigit(ch))
        {
            return false;
        }
    }
    return !input.empty(); 
}

// Amount input, checker
void getValidAmount(double &amount)
{
    std::string input;
    bool Valid = false; 

    while (!Valid)
    {
        std::cout << "\nEnter amount: ";
        std::cin >> input;

        if (isValidNumericString(input)) 
        {
            amount = std::stod(input);  
            if (amount < 0) 
            {
                std::cout << "Invalid input! Amount cannot be negative." << std::endl;
            }
            else
            {
                Valid = true; 
            }
        }
        else
        {
            std::cout << "Invalid input! Please enter a valid positive numeric amount." << std::endl;
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

    // Override withdraw method
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

    // Override deposit method
    void deposit(double amount) override
    {
        if (amount > 0)
        {
            setBalance(getBalance() + amount);
            std::cout << "Savings Account Deposit successful! Current balance: " << getBalance() << std::endl;
        }
        else
        {
            std::cout << "Invalid deposit amount!" << std::endl;
        }
    }
};

// CurrentAccount Class
class CurrentAccount : public BankAccount
{
public:
    CurrentAccount(double initialBalance) : BankAccount(initialBalance) {}

    // Override withdraw method
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

    // Override deposit method
    void deposit(double amount) override
    {
        if (amount > 0)
        {
            setBalance(getBalance() + amount);
            std::cout << "Current Account: Deposit successful! Current balance: " << getBalance() << std::endl;
        }
        else
        {
            std::cout << "Invalid deposit amount!" << std::endl;
        }
    }
};

// Sub-Menu-Savings-Current
void accountMenu(BankAccount &account)
{
    std::string subChoice;
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

        if (subChoice == "1" || subChoice == "2" || subChoice == "3" || subChoice == "4")
        {
            if (subChoice == "1")
            {
                SystemClear();
                std::cout << "Enter amount to deposit ";
                getValidAmount(amount);
                account.deposit(amount);
            }
            else if (subChoice == "2")
            {
                SystemClear();
                account.checkBalance();
                std::cout << "Enter amount to withdraw ";
                getValidAmount(amount);
                account.withdraw(amount);
            }
            else if (subChoice == "3")
            {
                SystemClear();
                account.checkBalance();
            }
            else if (subChoice == "4")
            {
                SystemClear();
                condition = true;
            }
        }
        else
        {
            std::cin.clear();
            std::cout << "Invalid choice. Please try again." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear invalid input
            SystemPause();
            SystemClear();
        }
    }
}

// Main Menu
void menu()
{
    std::string choice;
    bool running = true;

    SavingsAccount savings(1000.0);
    CurrentAccount current(0.0);

    while (running)
    {
        std::cout << "\nMain Menu\n";
        std::cout << "1 - Savings Account\n";
        std::cout << "2 - Current Account\n";
        std::cout << "3 - Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;


        if (choice == "1")
        {
            SystemClear();
            accountMenu(savings);
        }
        else if (choice == "2")
        {
            SystemClear();
            accountMenu(current);
        }
        else if (choice == "3")
        {
            SystemClear();
            std::cout << "Exiting program.\n";
            running = false;
        }
        else
        {
        
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please try again." << std::endl;
            SystemPause();
            SystemClear();
        }
    }
}

int main()
{
    menu();
    return 0;
}
