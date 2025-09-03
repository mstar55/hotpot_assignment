#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

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
struct OrderLine
{
    string name;
    double price;
    int amount;
    Category category;
};

namespace{
    //clean up the stream
    void cleanup()
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    //art work here
    void logo()
    {
        cout << "       .--.          " << endl;
        cout << "      (  CHONG     )         " << endl;
        cout << "      (     QING   )         " << endl;
        cout << "     ( SPICY HOTPOT )       " << endl;
        cout << "       -_________-         " << endl;
        cout << "          |     |            " << endl;
        cout << "          |_|            " << endl;
    }

    // compare between flavor chosen and already chosen flavor(s)
    bool isChosen(const string first, const MenuItem second[], int size)
    { //const cause values wont be modified
        for (int x = 0; x < size; x++)
        {
            if(second[x].name == first)
                return true;
            
        }
        return false;
    }
}

//enum for menu categorization, enum = using name instead of number for categorization



int main()
{
    /*
    ============
    Deifnitions
    ============
    */
    const int hotpot_type_amount = 3;
    string hotpot_types[hotpot_type_amount] = {
        {"Singular"},
        {"Yuanyang"},
        {"Four-Flavor"}};
    
    // menus + fixed array length
    const int menu_hotpot_types = 5;
    const int menu_addons_types = 9;
    const int menu_desserts_types = 2;
    const int main_menu_size = menu_hotpot_types + menu_addons_types + menu_desserts_types;
    MenuItem hotpot_menu[menu_hotpot_types] = {
        // Soup Bases: 4
        {"Mala Soup Base", 15.90, Category::SoupBase},
        {"Tomato Soup Base", 14.50, Category::SoupBase},
        {"Pumpkin Soup Base", 20.00, Category::SoupBase},
        {"Herbal Soup Base", 14.00, Category::SoupBase},
        {"Sukiyaki Soup Base", 15.00, Category::SoupBase}};
    MenuItem addons_menu[menu_addons_types] = {
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
    };
    MenuItem desserts_menu[menu_desserts_types] = {
        // Desserts: 2
        {"Boba Hotpot", 10.90, Category::Desserts},
        {"Ais Cream", 3.00, Category::Desserts}
    };

    //! make a main menu
    MenuItem main_menu[main_menu_size];
    HotpotType hotpot_type{};

    
    // max amount of flavor combo, four-flavor type
    MenuItem chosen_flavors[4] = {{},{},{},{}};
    OrderLine chosen_addons[menu_addons_types] = {};

    /*
    =================
    Prompting starts
    =================
    */
    logo();

    //display menu
    cout << "\n---------------------------------\n\n";
    cout << "Welcome to Chongqing Spicy Hotpot!\n" << endl;
    // for(const auto &item : main_menu)
    // {
    //     // display each item in the menu with sequence num and price
    //     cout << item.name << " - RM" << fixed << setprecision(2) << item.price << endl;
    // }

    //check hotpot types selection + input
    while(true)
    {
        // if second time ordering, ask if want to pick soup

        //display hotpot types from first to last
        for(int i = 0; i < static_cast<int>(HotpotType::Count) - 1; i++)
        {
            cout << i+1 << ". " << hotpot_types[i] << "\n";
        }

        //take selection and see if valid
        cout << "\n---------------------------------\n\n";
        cout << "What type of hotpot do you want? > ";
        int hotpot_selection = 0;

        //is the chosen hotpot type within "HotpotType" scope? if not, repeat la
        if (!(cin >> hotpot_selection) || hotpot_selection < static_cast<int>(HotpotType::Singular) || hotpot_selection >= static_cast<int>(HotpotType::Count))
        {
            cout << "read again la\n";
            cleanup();
            continue;
        }
        hotpot_type = static_cast<HotpotType>(hotpot_selection);
        break;
    }

    //flava.
    int flavor = 0, flavor2 = 0, flavor3 = 0, flavor4 = 0;
    for(int y = 0; y < menu_hotpot_types; y++)
    {
        cout << y + 1 << ". " << hotpot_menu[y].name << endl;
    } 

    // flavor selection for hotpot(s), cannot pick the same one again
    switch (hotpot_type)
    {
    case HotpotType::Singular:
        cout << "\n---------------------------------\n\n";
        cout << "You chose Singular-flavor hotpot\n";
        while (true)
        {
            cout << "pick your flavor > ";
            if (!(cin >> flavor) || flavor > menu_hotpot_types || flavor <= 0)
            {
                cout << "invalid hotpot flavor \n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor - 1] = hotpot_menu[flavor - 1];
            break;
        }
        break;
    case HotpotType::Yuanyang:
        cout << "\n---------------------------------\n\n";
        cout << "You chose Yuanyang hotpot, pick 2 flavors\n";
        while (true)
        {
            cout << "pick your flavor > ";
            if (!(cin >> flavor) || flavor > menu_hotpot_types || flavor <= 0)
            {
                cout << "invalid hotpot flavor \n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor - 1] = hotpot_menu[flavor - 1];
            break;
        }

        while (true)
        {
            cout << "pick your flavor2 > ";
            if (!(cin >> flavor2) || flavor2 > menu_hotpot_types || flavor2 <= 0)
            {
                cout << "invalid hotpot flavor \n";
                cleanup();
                continue;
            }
            if (isChosen(hotpot_menu[flavor2 - 1].name, chosen_flavors, menu_hotpot_types))
            {
                cout << "Flavor repeated haiya\n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor2 - 1] = hotpot_menu[flavor2 - 1];
            break;
        }
        break;
    case HotpotType::FourFlavor:
        cout << "You chose Four-flavor hotpot, pick 4 flavors\n";
        while (true)
        {
            cout << "pick your flavor > ";
            if (!(cin >> flavor) || flavor > menu_hotpot_types || flavor <= 0)
            {
                cout << "invalid hotpot flavor \n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor - 1] = hotpot_menu[flavor - 1];
            break;
        }

        while (true)
        {
            cout << "pick your flavor2 > ";
            if (!(cin >> flavor2) || flavor2 > menu_hotpot_types || flavor2 <= 0)
            {
                cout << "invalid hotpot flavor no. 2 \n";
                cleanup();
                continue;
            }
            if (isChosen(hotpot_menu[flavor2 - 1].name, chosen_flavors, menu_hotpot_types))
            {
                cout << "Flavor repeated haiya\n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor2 - 1] = hotpot_menu[flavor2 - 1];
            break;
        }

        while (true)
        {
            cout << "pick your flavor3 > ";
            if (!(cin >> flavor3) || flavor3 > menu_hotpot_types || flavor3 <= 0)
            {
                cout << "invalid hotpot flavor no. 3 \n";
                cleanup();
                continue;
            }
            if (isChosen(hotpot_menu[flavor3 - 1].name, chosen_flavors, menu_hotpot_types))
            {
                cout << "Flavor repeated haiya\n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor3 - 1] = hotpot_menu[flavor3 - 1];
            break;
        }

        while (true)
        {
            cout << "pick your flavor4 > ";
            if (!(cin >> flavor4) || flavor4 > menu_hotpot_types || flavor4 <= 0)
            {
                cout << "invalid hotpot flavor no. 4 \n";
                cleanup();
                continue;
            }
            if (isChosen(hotpot_menu[flavor4 - 1].name, chosen_flavors, menu_hotpot_types))
            {
                cout << "Flavor repeated haiya\n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor4 - 1] = hotpot_menu[flavor4 - 1];
            break;
        }
        break;

    default:
        cout << "what did you do? restart the whole thing again haiya";
        break;
    }

    /*
    =================
    Addons selection
    =================
    */
    cout << "\n---------------------------------\n\n";
    // display addons menu
    for(int i = 0; i < menu_addons_types; i++)
    {
        cout << i+1 << ". " << addons_menu[i].name << " - RM" << fixed << setprecision(2) << addons_menu[i].price << endl;
    }
    
    // addons selection, max_selection as cap
    cout << "pick your addons or 0 to continue." << endl;
    while(true)
    {   
        //! give clear indication for 0 to stop and what loop what is selected
        int addon = 0, amount = 0;
        cout << "addon > ";
        if(!(cin >> addon) || addon > menu_addons_types || addon < 0)
        {
            cout << "invalid addon";
            cleanup();
            continue;
        }else if(addon == 0) //if 0 is pressed, continue to desserts
            break;

        cout <<"amount > ";
        if (!(cin >> amount) || amount <= 0) // mmm
        {
            cout << "invalid amount";
            cleanup();
            continue;
        }

        //record it and loop until max_addons
        chosen_addons[addon - 1].name = addons_menu[addon - 1].name;
        chosen_addons[addon - 1].price = addons_menu[addon - 1].price;
        chosen_addons[addon - 1].category = addons_menu[addon - 1].category;
        chosen_addons[addon - 1].amount += amount;
        continue;
    }

    //desserts section
    cout << "pick your dessert (mandatory)\n";


    // 1. Display base options
    // 2. Let user pick a base (one or special case yuanyang)
    // 3. Display addon options (can skip and pick as many as needed)
    // 4. Display dessert options (mandatory)
    // 5. Confirm order
    // 6. If confirmed, set selected = true;
    // ascii art for receipt

    //allow to use 2 flavor if picked the yuanyang base

    //for loop display menu each
    //prompt for user inputs
    //receipt generation, can use \t for format syntaxing

    return 0;
}