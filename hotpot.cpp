#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//enum for menu categories
enum class Category 
{
    SoupBase, //0
    Addons, //1
    Desserts //2
};

//menu structure
struct MenuItem 
{
    // members
    string name;
    double price;
    Category category;
};

// work of art worth 100
void displayMenu()
{
    
}

int main()
{
    MenuItem hotpot_menu[15] = {
        // Soup Bases: 4
        {"Mala Soup Base", 15.90, Category::SoupBase},
        {"Tomato Soup Base", 14.50, Category::SoupBase},
        {"Yuanyang Hotpot", 20.00, Category::SoupBase},
        {"Herbal Soup Base", 14.00, Category::SoupBase},

        // Add-ons: 9
        {"Beef Slices (5pcs)", 12.50, Category::Addons},
        {"Fish Slices (5pcs)", 9.00, Category::Addons},
        {"Bacon (5pcs)", 10.00, Category::Addons},
        {"Fresh Tofu (5pcs)", 5.00, Category::Addons},
        {"Fish Balls (6pcs)", 6.90, Category::Addons},
        {"Lotus Root (7pcs)", 4.80, Category::Addons},
        {"Enoki Mushrooms (small)", 5.50, Category::Addons},
        {"White Rice", 2.00, Category::Addons},
        {"Maggi Noodles", 2.00, Category::Addons},

        // Desserts: 2
        {"Boba Hotpot", 10.90, Category::Desserts},
        {"Ais Cream", 3.00, Category::Desserts}};

    // display menu
    cout << "Welcome to Chongqing Spicy Hotpot!" << endl;
    for(const auto &item : hotpot_menu)
    {
        // display each item in the menu with sequence num and price
        cout << item.name << " - RM" << fixed << setprecision(2) << item.price << endl;
    }

    bool selected = false;
    bool yanyang = false;
    do
    {
        cout << "Pick soup base 1 > ";
        int soup_selection1 = 0;
        if (!(cin >> soup_selection1) || soup_selection1 <= 0 && soup_selection1 > /*category.soupbase*/)
        {

        }

        cout << "Pick soup base 2 > ";
        int soup_selection2 = 0;
        if (!(cin >> soup_selection2))
        {

        }

        switch (soup_selection1)
        {
        case constant expression:
            /* code */
            break;

        default:
            break;
        }
        // 1. Display base options
        // 2. Let user pick a base (one or special case yanyang)
        // 3. Display addon options (loop)
        // 4. Let user pick as many as they want
        // 5. Display dessert options
        // 6. Confirm order
        // 7. If confirmed, set selected = true;
        // ascii art for receipt

    } while (!selected);

    //allow to use 2 flavor if picked the yanyang base

    //

    //for loop display menu each
    //prompt for user inputs
    //receipt generation

    return 0;
}