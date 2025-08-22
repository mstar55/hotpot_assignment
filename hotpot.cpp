#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
namespace{
    void cleanup()
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    void logo()
    {
        cout << "logo\n";
    }
}

//enum for menu categorization
enum class Category 
{
    // selection start from 0 - 2
    SoupBase,
    Addons,
    Desserts,
    Count
};

enum class HotpotType
{
    Singular = 1,
    Yuanyang = 2,
    FourFlavor = 3,
    Count
};

//menu structure
struct MenuItem 
{
    string name;
    double price;
    Category category;
};

int main()
{
    /*
    ============
    Deifnitions
    ============
    */

    const int menu_item_amount = 15;
    const int hotpot_type_amount = 3;
    MenuItem hotpot_menu[menu_item_amount] = {
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
    string hotpot_types[hotpot_type_amount] = {
        {"Singular"},
        {"Yuanyang"},
        {"Four-Flavor"}
    };

    bool selected = false;
    bool yuanyang = false;
    int soup_selection1 = 0;
    int soup_selection2 = 0;
    HotpotType hotpot_type{};

    /*
    =================
    Prompting starts
    =================
    */

    //! display logo and introduction
    // logo();

    //display menu
    cout << "Welcome to Chongqing Spicy Hotpot!" << endl;
    for(const auto &item : hotpot_menu)
    {
        // display each item in the menu with sequence num and price
        cout << item.name << " - RM" << fixed << setprecision(2) << item.price << endl;
    }

    //pick hotpot types
    while(true)
    {
        //display hotpot types
        for(int i = 0; i < static_cast<int>(HotpotType::Count); i++)
        {
            cout << i+1 << ". " << hotpot_types[i] << "\n";
        }

        //take selection and see if valid
        cout << "What type of hotpot do you want? > ";
        int hotpot_selection = 0;

        //is the chosen hotpot type within "HotpotType" scope? if not, repeat la
        if (!(cin >> hotpot_selection) && hotpot_selection >= static_cast<int>(HotpotType::Singular) && hotpot_selection < static_cast<int>(HotpotType::Count))
        {
            cout << "read again la";
            cleanup();
            continue;
        }
        hotpot_type = static_cast<HotpotType>(hotpot_selection);
        break;
    }

    // loop for flavor depending on hotpot types, cannot pick the same one again
    switch (hotpot_type)
    {
    case HotpotType::Singular :
        while(true)
        {
            cout << "pick your flavor > ";
            if(!(cin >> ))
        }
        break;
    
    default:
        break;
    }

    do
    {
        switch (soup_selection1)
        {
        case constant expression:
            /* code */
            break;

        default:
            break;
        }
        // 1. Display base options
        // 2. Let user pick a base (one or special case yuanyang)
        // 3. Display addon options (loop)
        // 4. Let user pick as many as they want
        // 5. Display dessert options
        // 6. Confirm order
        // 7. If confirmed, set selected = true;
        // ascii art for receipt

    } while (!selected);

    //allow to use 2 flavor if picked the yuanyang base

    //

    //for loop display menu each
    //prompt for user inputs
    //receipt generation

    return 0;
}