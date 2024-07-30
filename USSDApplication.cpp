#include <iostream>
#include <string>
#include <regex>
using namespace std;

class USSDApplication
{
public:
    virtual void showMenu() = 0;
    virtual void handleInput(int choice) = 0;
    virtual ~USSDApplication() {}
};

class BalanceInquiry : public USSDApplication
{
private:
    int &balance;

public:
    BalanceInquiry(int &bal) : balance(bal) {}

    void showMenu() override
    {
        cout << "Balance Inquiry Menu:\n";
        cout << "1. Check Balance\n";
        cout << "2. Main Menu\n";
    }

    void handleInput(int choice) override
    {
        if (choice == 1)
        {
            cout << "Your balance is " << balance << ".\n";
        }
        else if (choice == 2)
        {
            cout << "Returning to main menu...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
};

class DataBundlePurchase : public USSDApplication
{
private:
    int &balance;

public:
    DataBundlePurchase(int &bal) : balance(bal) {}

    void showMenu() override
    {
        cout << "Data Bundle Purchase Menu:\n";
        cout << "1. Buy 1GB (100 units)\n";
        cout << "2. Buy 5GB (400 units)\n";
        cout << "3. Main Menu\n";
    }

    void handleInput(int choice) override
    {
        int cost = 0;
        if (choice == 1)
        {
            cost = 100;
        }
        else if (choice == 2)
        {
            cost = 400;
        }

        if (cost > 0)
        {
            if (balance >= cost)
            {
                string phoneNumber;
                cout << "Enter your 11-digit phone number: ";
                cin >> phoneNumber;

                // Validate phone number length
                if (phoneNumber.length() == 11 && regex_match(phoneNumber, regex("\\d{11}")))
                {
                    balance -= cost;
                    cout << "You have purchased " << (choice == 1 ? "1GB" : "5GB") << " of data for phone number " << phoneNumber << ".\n";
                    cout << "Your new balance is " << balance << ".\n";
                }
                else
                {
                    cout << "Invalid phone number. Returning to main menu...\n";
                }
            }
            else
            {
                cout << "Insufficient balance. Returning to main menu...\n";
            }
        }
        else if (choice == 3)
        {
            cout << "Returning to main menu...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
};

class CustomerSupport : public USSDApplication
{
public:
    void showMenu() override
    {
        cout << "Customer Support Menu:\n";
        cout << "1. Talk to an agent\n";
        cout << "2. Main Menu\n";
    }

    void handleInput(int choice) override
    {
        if (choice == 1)
        {
            string query;
            cout << "Hello, welcome to USSD customer service, please submit your query, and we will attend to you as soon as possible.\n";
            cin.ignore(); // Clear the newline character left in the input buffer
            getline(cin, query);
            cout << "Thank you, we will get back to you ASAP. Returning to main menu...\n";
        }
        else if (choice == 2)
        {
            cout << "Returning to main menu...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }
};

// Main USSD application class
class USSDMainApp
{
private:
    USSDApplication *services[3];
    int balance;

public:
    USSDMainApp(int initialBalance) : balance(initialBalance)
    {
        services[0] = new BalanceInquiry(balance);
        services[1] = new DataBundlePurchase(balance);
        services[2] = new CustomerSupport();
    }

    ~USSDMainApp()
    {
        for (auto service : services)
        {
            delete service;
        }
    }

    void showMainMenu()
    {
        cout << "Main Menu:\n";
        cout << "1. Balance Inquiry\n";
        cout << "2. Data Bundle Purchase\n";
        cout << "3. Customer Support\n";
        cout << "4. Exit\n";
    }

    void handleMainInput(int choice)
    {
        if (choice >= 1 && choice <= 3)
        {
            services[choice - 1]->showMenu();
            int subChoice;
            cin >> subChoice;
            services[choice - 1]->handleInput(subChoice);
        }
        else if (choice == 4)
        {
            cout << "Exiting...\n";
        }
        else
        {
            cout << "Invalid choice.\n";
        }
    }

    void run()
    {
        int choice;
        do
        {
            showMainMenu();
            cin >> choice;
            handleMainInput(choice);
        } while (choice != 4);
    }
};

int main()
{
    int initialBalance = 1000; // Set initial balance
    USSDMainApp app(initialBalance);
    app.run();
    return 0;
}
