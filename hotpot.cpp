#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
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
        cout << "logo\n";
    }

    // compare between flavor chosen and already chosen flavor(s)
    bool isChosen(string first, string second[])
    {
        for (int x = 0; x < second->length(); x++)
        {
            if(second[x] == first)
                return true;
            
        }
        return false;
    }
}

//enum for menu categorization, enum = using name instead of number for categorization
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

    const int hotpot_type_amount = 3;
    string hotpot_types[hotpot_type_amount] = {
        {"Singular"},
        {"Yuanyang"},
        {"Four-Flavor"}};
    string chosen_flavors[4] = {{},{},{},{}};
    const int menu_hotpot_types = 4;
    const int menu_addons_type = 9;
    const int menu_desserts_type = 2;
    const int main_menu_size = menu_hotpot_types + menu_addons_type + menu_desserts_type;
    MenuItem hotpot_menu[menu_hotpot_types] = {
        // Soup Bases: 4
        {"Mala Soup Base", 15.90, Category::SoupBase},
        {"Tomato Soup Base", 14.50, Category::SoupBase},
        {"Yuanyang Hotpot", 20.00, Category::SoupBase},
        {"Herbal Soup Base", 14.00, Category::SoupBase}};
    MenuItem addons_menu[menu_addons_type] = {
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
    MenuItem desserts_menu[menu_desserts_type] = {
        // Desserts: 2
        {"Boba Hotpot", 10.90, Category::Desserts},
        {"Ais Cream", 3.00, Category::Desserts}
    };

    //make a menu with 
    MenuItem main_menu[main_menu_size];
    int soup_selection1 = 0;
    int soup_selection2 = 0;
    HotpotType hotpot_type{};

    /*
    =================
    Prompting starts
    =================
    */

    //! display logo and introduction
    logo();

    //display menu
    cout << "Welcome to Chongqing Spicy Hotpot!" << endl;
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
        cout << "What type of hotpot do you want? > ";
        int hotpot_selection = 0;

        //is the chosen hotpot type within "HotpotType" scope? if not, repeat la
        if (!(cin >> hotpot_selection) || hotpot_selection < static_cast<int>(HotpotType::Singular) || hotpot_selection >= static_cast<int>(HotpotType::Count))
        {
            cout << "read again la";
            cleanup();
            continue;
        }
        hotpot_type = static_cast<HotpotType>(hotpot_selection);
        break;
    }

    //flava.
    int flavor = 0, flavor2 = 0, flavor3 = 0, flavor4 = 0;

    //! flavor selection for hotpot(s), cannot pick the same one again
    switch (hotpot_type)
    {
    case HotpotType::Singular:
        while (true)
        {
            cout << "pick your flavor > ";
            if (!(cin >> flavor) || flavor > hotpot_type_amount || flavor < hotpot_type_amount)
            {
                cout << "invalid hotpot flavor \n";
                cout << "one false is true";
                cleanup();
                continue;
            }
            chosen_flavors[flavor - 1] = hotpot_types[flavor - 1];
            break;
        }
        break;
    case HotpotType::Yuanyang:
        while (true)
        {
            cout << "pick your flavor > ";
            if (!(cin >> flavor) || flavor > hotpot_type_amount || flavor < hotpot_type_amount)
            {
                cout << "invalid hotpot flavor \n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor - 1] = hotpot_types[flavor - 1];
            break;
        }

        while (true)
        {
            cout << "pick your flavor2 > ";
            if (!(cin >> flavor2) || isChosen(hotpot_types[flavor2 - 1], chosen_flavors)  || flavor2 > hotpot_type_amount || flavor2 < hotpot_type_amount)
            {
                cout << "invalid hotpot flavor \n";
                cleanup();
            }
            chosen_flavors[flavor2 - 1] = hotpot_types[flavor2 - 1];
            break;
        }
        break;
    case HotpotType::FourFlavor:
        while (true)
        {
            cout << "pick your flavor > ";
            if (!(cin >> flavor) || flavor > hotpot_type_amount || flavor < hotpot_type_amount)
            {
                cout << "invalid hotpot flavor \n";
                cleanup();
                continue;
            }
            chosen_flavors[flavor - 1] = hotpot_types[flavor - 1];
            break;
        }

        while (true)
        {
            cout << "pick your flavor2 > ";
            if (!(cin >> flavor2) || isChosen(hotpot_types[flavor2 - 1], chosen_flavors) || flavor2 > hotpot_type_amount || flavor2 < hotpot_type_amount)
            {
                cout << "invalid hotpot flavor no. 2 \n";
                cleanup();
            }
            chosen_flavors[flavor2 - 1] = hotpot_types[flavor2 - 1];
            break;
        }
        break;

        while (true)
        {
            cout << "pick your flavor3 > ";
            if (!(cin >> flavor3) || isChosen(hotpot_types[flavor3 - 1], chosen_flavors) || flavor3 > hotpot_type_amount || flavor3 < hotpot_type_amount)
            {
                cout << "invalid hotpot flavor no. 3 \n";
                cleanup();
            }
            break;
        }
        chosen_flavors[flavor3 - 1] = hotpot_types[flavor3 - 1];
        break;

        while (true)
        {
            cout << "pick your flavor4 > ";
            if (!(cin >> flavor4) || isChosen(hotpot_types[flavor4 - 1], chosen_flavors) || flavor4 > hotpot_type_amount || flavor4 < hotpot_type_amount)
            {
                cout << "invalid hotpot flavor no. 4 \n";
                cleanup();
            }
            chosen_flavors[flavor4 - 1] = hotpot_types[flavor4 - 1];
            break;
        }
        break;

    default:
        cout << "what did you do? restart the whole thing again haiya";
        break;
    }

    // addons for hotpot, also ask for amount
    cout << "pick your addons or 0 to skip." << endl;
    //display addons menu
    // for(int i = 0; i < ; i++)
    // {
        
    // }
    //while loop of int i, make new array with {i} as its name, remove old array and replace one with the same name? store previous array list and set whole array to empty?

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