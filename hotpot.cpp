#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <ctime>

using namespace std;

// 1. Display base options
// 2. Let user pick a base (one or special case yuanyang)
// 3. Display addon_choice options (can skip and pick as many as needed)
// 4. Display dessert options (mandatory)
// 5. Confirm order
// 6. confirm at the end?
// receipt generation, can use \t for format syntaxing

enum class Category 
{
    // selection start from 0 - 2
    SoupBase,
    Addons,
    Desserts,
    Count //end, not a category
};
enum class HotpotType
{
    Singular = 1,
    Yuanyang = 2,
    FourFlavor = 3,
    Count
};

//order structure
struct OrderLine
{
    string name;
    double price;
    int amount;
    Category category;

    void addAmount(int extra){
        amount += extra;
    }

    void subtractAmount(int sub){
        amount -= sub;
    }

    double netTotal() const{ //nothing will be changed, just returned
        return price * amount;
    }
};
//menu structure
struct MenuItem 
{
    string name;
    double price;
    Category category;

    //vroom vroom for the housing of amounts
    //make an orderline struct type of member function that returns the same thing as orderline but with stuff from MenuItem
    //const because nothing will be modified in MenuItem
    OrderLine order() const{ 

        // amount = 0 because it is only called for copying and at the start
        return {name, price, 0, category};
    }
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
        cout << "       .----------.       " << "\n";
        cout << "      (  CHONG     )         " << "\n";
        cout << "      (    QING    )         " << "\n";
        cout << "     ( SPICY HOTPOT )       " << "\n";
        cout << "       -__________-         " << "\n";
        cout << "          |     |            " << "\n";
        cout << "          |_____|            " << endl;
    }

    // compare between flavor chosen and already chosen flavor(s), function is made for hotpot flavors only
    bool isChosen(const string first, const OrderLine second[], int size)
    { //const cause values wont be modified
        for (int x = 0; x < size; x++)
        {
            if(second[x].name == first)
                return true;
        }
        return false;
    }

    string type_hotpot(HotpotType hotpot_type)
    {
        switch (hotpot_type)
        {
        case HotpotType::Singular:
            return "Singular";
        case HotpotType::Yuanyang:
            return "Yuanyang";
        case HotpotType::FourFlavor:
            return "Four Flavor";
        default:
            return "n/a";
        }
    }

    void receipt(HotpotType hotpot_type, OrderLine hotpot_orders[], OrderLine addon_orders[], OrderLine dessert_orders[], int total_flavors, int total_addons, int total_desserts)
    {
        time_t now = time(0);
        tm *ltm = localtime(&now);

        cout << "               RECEIPT" << endl;
        cout << "----------------------------------------" << endl;
        cout << "        Chong Qing Spicy Hotpot" << endl;
        cout << "Address: 8, Jalan Raja Abdullah, Chow Kit," << endl;
        cout << "         50300 Kuala Lumpur," << endl;
        cout << "Tel: 012-345-6789" << endl;
        cout << "----------------------------------------" << endl;

        // date time
        cout << "Date: "
             << setw(2) << setfill('0') << ltm->tm_mday << "-"
             << setw(2) << setfill('0') << (ltm->tm_mon + 1) << "-"
             << (1900 + ltm->tm_year)
             << "         "
             << setw(2) << setfill('0') << ltm->tm_hour << ":"
             << setw(2) << setfill('0') << ltm->tm_min
             << setfill(' ') << endl;

        cout << "----------------------------------------" << endl;
        cout << "Hotpot type ordered: " << type_hotpot(hotpot_type) << "\n";
        for(int i = 0; i < total_flavors; i++)
        {
            
        }
    }

    int code()
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
        const int addons_type_amount = 9;
        const int desserts_type_amount = 2;
        const int main_menu_size = menu_hotpot_types + addons_type_amount + desserts_type_amount;
        MenuItem hotpot_menu[menu_hotpot_types] = {
            // Soup Bases: 4
            {"Mala Soup Base", 15.90, Category::SoupBase},
            {"Tomato Soup Base", 14.50, Category::SoupBase},
            {"Pumpkin Soup Base", 20.00, Category::SoupBase},
            {"Herbal Soup Base", 14.00, Category::SoupBase},
            {"Sukiyaki Soup Base", 15.00, Category::SoupBase}};
        MenuItem addons_menu[addons_type_amount] = {
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
        MenuItem desserts_menu[desserts_type_amount] = {
            // Desserts: 2
            {"Boba Hotpot", 10.90, Category::Desserts},
            {"Ais Cream", 3.00, Category::Desserts}};

        //! make a main menu
        MenuItem main_menu[main_menu_size];
        HotpotType hotpot_type{};

        // max amount of flavor combo, four-flavor type
        OrderLine chosen_flavors[4] = {{}, {}, {}, {}};
        OrderLine chosen_addons[addons_type_amount] = {};
        OrderLine chosen_desserts[desserts_type_amount] = {};

        /*
        =================
        Prompting starts
        =================
        */
        logo();

        // display menu
        cout << "\n---------------------------------\n\n";
        cout << "Welcome to Chongqing Spicy Hotpot!\n"
             << endl;
        // for(const auto &item : main_menu)
        // {
        //     // display each item in the menu with sequence num and price
        //     cout << item.name << " - RM" << fixed << setprecision(2) << item.price << endl;
        // }

        // check hotpot types selection + input
        while (true)
        {
            // if second time ordering, ask if want to pick soup

            // display hotpot types from first to last
            for (int i = 0; i < static_cast<int>(HotpotType::Count) - 1; i++)
            {
                cout << i + 1 << ". " << hotpot_types[i] << "\n";
            }

            // take selection and see if valid
            cout << "\n---------------------------------\n\n";
            cout << "What type of hotpot do you want? > ";
            int hotpot_selection = 0;

            // is the chosen hotpot type within "HotpotType" scope? if not, repeat la
            if (!(cin >> hotpot_selection) || hotpot_selection < static_cast<int>(HotpotType::Singular) || hotpot_selection >= static_cast<int>(HotpotType::Count))
            {
                cout << "read again la\n";
                cleanup();
                continue;
            }
            hotpot_type = static_cast<HotpotType>(hotpot_selection);
            break;
        }

        // flava.
        int flavor = 0, flavor2 = 0, flavor3 = 0, flavor4 = 0;
        for (int y = 0; y < menu_hotpot_types; y++)
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
                chosen_flavors[flavor - 1] = hotpot_menu[flavor - 1].order();
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
                chosen_flavors[flavor - 1] = hotpot_menu[flavor - 1].order();
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
                chosen_flavors[flavor2 - 1] = hotpot_menu[flavor2 - 1].order();
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
                chosen_flavors[flavor - 1] = hotpot_menu[flavor - 1].order();
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
                chosen_flavors[flavor2 - 1] = hotpot_menu[flavor2 - 1].order();
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
                chosen_flavors[flavor3 - 1] = hotpot_menu[flavor3 - 1].order();
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
                chosen_flavors[flavor4 - 1] = hotpot_menu[flavor4 - 1].order();
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
        cout << "addons selection\n";
        // display addons menu
        for (int i = 0; i < addons_type_amount; i++)
        {
            cout << i + 1 << ". " << addons_menu[i].name << " - RM" << fixed << setprecision(2) << addons_menu[i].price << "\n";
        }

        // addons selection, max_selection as cap
        int unique_addons = 0;
        cout << "\npick your addons or 0 to continue." << endl;
        while (true)
        {
            //! give clearer indication for 0 to stop and what loop what is selected
            int addon_choice = 0, addon_amount = 0;
            cout << "addon_choice > ";
            if (!(cin >> addon_choice) || addon_choice > addons_type_amount || addon_choice < 0)
            {
                cout << "invalid addon_choice";
                cleanup();
                continue;
            }
            else if (addon_choice == 0) // if 0 is pressed, continue to desserts
                break;

            cout << "amount > ";
            if (!(cin >> addon_amount) || addon_amount <= 0) // mmm
            {
                cout << "invalid amount";
                cleanup();
                continue;
            }

            // record it and loop until max_addons
            if (chosen_addons[addon_choice - 1].amount == 0)
            {
                //just copy addons_menu into chosen_addons but make the amount = 0, see struct MenuItem
                chosen_addons[addon_choice - 1] = addons_menu[addon_choice - 1].order(); 

                unique_addons++;
                cout << "added to basket!\n";
            }

            //adding into "amount" inside chosen_addons, see struct OrderLine
            chosen_addons[addon_choice - 1].addAmount(addon_amount); 
            continue;
        }
        cout << "you chose: \n";

        //loop through addons that are not the same that has been chosen before, and print out the price for further changes
        for(int i = 0; i < addons_type_amount; i++)
        {
            if (chosen_addons[i].amount > 0)
                cout << i + 1 << ". " << chosen_addons[i].name << " - RM" << fixed << setprecision(2) << chosen_addons[i].price << " - " << chosen_addons[i].amount << "order\n";
        }

        // desserts section
        cout << "pick your dessert (at least one is mandatory)\n";
        for(int z = 0; z < desserts_type_amount; z++)
        {
            cout << z + 1 << ". " << desserts_menu[z].name << " - RM" << fixed << setprecision(2) << desserts_menu[z].price << "\n";
        }

        bool picked = false;
        while(true)
        {
            int dessert_choice = 0, dessert_amount = 0;
            if (!(cin >> dessert_choice) || dessert_choice > addons_type_amount || dessert_choice < 0)
            {
                cout << "stop finding errors everywhere";
                cleanup();
                continue;
            }
            else if (dessert_choice == 0)
            {
                if(picked)
                    break;
                
                cout << "pick your dessert (at least one is mandatory)\n";
                cleanup();
                continue;
            }
            
            cout << "Amount > ";
            if(!(cin >> dessert_amount) || dessert_amount <= 0)
            {
                cout << "cannot";
                cleanup();
                continue;
            }

            // also record and stop if press 0
            //  record it and loop until max_addons
            if (chosen_desserts[dessert_choice - 1].amount == 0)
            {
                chosen_desserts[dessert_choice - 1] = desserts_menu[dessert_choice - 1].order();
            }
            chosen_desserts[dessert_choice - 1].addAmount(dessert_amount);
            cout << "added to basket!\n";
            picked = true;
            continue;
        }

        // ascii art for receipt
        // chosen_desserts, hotpot_type, chosen_flavor
        // print receipt + calculations
        receipt(hotpot_type, chosen_flavors, chosen_addons, chosen_desserts, hotpot_type_amount, addons_type_amount, desserts_type_amount);
        
        return 0;
    }
}

//enum for menu categorization, enum = using name instead of number for categorization

//so clean
int main()
{
    return code();
}