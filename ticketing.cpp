#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// structure
//  soup
//  addons
// desserts

// Structure to hold menu item
struct MenuItem
{
    string name;
    double price;
};

void logo()
{
    cout << "      _                               _             " << endl;
    cout << "  ___| |__   ___  _ __   __ _    __ _(_)_ __   __ _ " << endl;
    cout << " / __| '_ \ / _ \| '_ \ / _` |  / _` | | '_ \ / _` |" << endl;
    cout << "| (__| | | | (_) | | | | (_| | | (_| | | | | | (_| |" << endl;
    cout << " \___|_| |_|\___/|_| |_|\__, |  \__, |_|_| |_|\__, |" << endl;
    cout << "| |__   ___ | |_ _ __   |___/ |_   |_|        |___/ " << endl;
    cout << "| '_ \ / _ \| __| '_ \ / _ \| __|                   " << endl;
    cout << "| | | | (_) | |_| |_) | (_) | |_                    " << endl;
    cout << "|_| |_|\___/ \__| .__/ \___/ \__|                   " << endl;
    cout << "                |_|                                 " << endl;
}

// Function to display the menu
void displayMenu(const vector<MenuItem> &Soup_base_menu)
{
    cout << "\n=== Chongqing Spicy Hotpot Menu ===\n";
    for (size_t i = 0; i < Soup_base_menu.size(); ++i)
    {
        cout << i + 1 << ". " << Soup_base_menu[i].name << " - RM" << fixed << setprecision(2) << Soup_base_menu[i].price << endl;
    }
}

// Function to generate receipt
void generateReceipt(const vector<MenuItem> &Soup_base_menu, const vector<int> &order, int customerNumber)
{
    double total = 0.0;
    cout << "\n--- Receipt for Customer #" << customerNumber << " ---\n";
    for (int index : order)
    {
        cout << Soup_base_menu[index].name << " - RM" << fixed << setprecision(2) << Soup_base_menu[index].price << endl;
        total += Soup_base_menu[index].price;
    }
    cout << "Total: RM" << fixed << setprecision(2) << total << endl;
    cout << "Thank you for dining at Chongqing Spicy Hotpot!\n";
}

int main()
{
    vector<MenuItem> Soup_base_menu = {
        {"Mala Soup Base", 15.90},
        {"Tomato Soup Base", 14.50},
        {"Pumpkin Soup Base", 13.00},
        {"Yuanyang hotpot", 20.00},
        {"Beef Slices(5pcs)", 12.50},
        {"Fish Slices(5pcs)", 9.00},
        {"Bacon(5pcs)", 10.00},
        {"Fresh Tofu(5pcs)", 5.00},
        {"Fish Balls(6pcs)", 6.90},
        {"Lotus Root(7pcs)", 4.80},
        {"Enoki Mushrooms(small)", 5.50},
        {"White Rice", 2.00},
        {"Maggi noodles", 2.00},
        {"Boba hotpot", 10.90},
        {"Ais cream", 3.00},
    };

    int customerNumber = 1;
    char moreOrder;

    cout << "Welcome to Chongqing Spicy Hotpot Restaurant!\n";
    cout << "Experience authentic Sichuan flavors right here in KL.\n";

    // addon to different receipt if press y after done, ideally make a selection for combining receipt or new receipt
    //
    do
    {
        vector<int> order;
        logo();
        displayMenu(Soup_base_menu);

        cout << "\nEnter item numbers to order (0 to finish):\n";
        int choice;
        while (true)
        {
            cin >> choice;
            if (choice == 0)
                break;
            if (choice > 0 && choice <= Soup_base_menu.size())
            {
                order.push_back(choice - 1);
            }
            else
            {
                cout << "Invalid selection. Try again.\n";
            }
        }

        generateReceipt(Soup_base_menu, order, customerNumber++);
        cout << "\nWould you like to place another order? (y/n): ";
        cin >> moreOrder;

    } while (moreOrder == 'y' || moreOrder == 'Y');

    cout << "\nGoodbye! Hope to see you again!\n";
    return 0;
}