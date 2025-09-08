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
// no vector used
// receipt generation, can use \t for format syntaxing

enum class Category
{
    // selection start from 0 - 2
    SoupBase,
    Addons,
    Desserts,
    Count // end, not a category
};
enum class HotpotType
{
    Singular = 1,
    Yuanyang = 2,
    FourFlavor = 3,
    Count
};

// order structure
struct OrderLine
{
    string name = "";
    double price = 0.0;
    int amount = 0;
    Category category = {};

    void addAmount(int extra)
    {
        amount += extra;
    }

    bool subtractAmount(int sub)
    {
        // added bc +(-1) = -1, -(-1) = 1
        amount += sub;

        //safety
        if(amount < 0){
            amount = 0;
            return false;
        } 
        return true;
    }

    double netTotal() const
    { // nothing will be changed, just returned
        return price * amount;
    }
};
// menu structure
struct MenuItem
{
    string name = " ";
    double price = 0.0;
    Category category = {};

    // vroom vroom for the housing of amounts
    // make an orderline struct type of member function that returns the same thing as orderline but with stuff from MenuItem
    // const because nothing will be modified in MenuItem
    OrderLine order() const{

        // amount = 0 because it is only called for copying and at the start
        return {name, price, 0, category};
    }
};

const int hotpot_type_amount = 3;
string hotpot_types[hotpot_type_amount] = {
    {"Singular"},
    {"Yuanyang"},
    {"Four-Flavor"}};

// menus + fixed array length
const int menu_hotpot_types = 5;
const int menu_addons_types = 9;
const int menu_desserts_types = 2;
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
    {"Ice Cream", 3.00, Category::Desserts}
};

//record prices for Report struct
struct Prices
{
    double net_total;
    double taxed_total;
    double service_tax;

    double net() const{
        return net_total;
    }

    double tax_amount() const {
        return service_tax;
    }

    double taxed_final() const
    {
        return taxed_total;
    }
};

// report structure
struct Report
{
    string hotpot_type;
    OrderLine hotpot_flavor_order[menu_hotpot_types];
    OrderLine addons_order[menu_addons_types];
    OrderLine desserts_order[menu_desserts_types];
    Prices prices;

    void report_Form_simple() const{
        //display simple list of order
        cout << "hotpot type: " << hotpot_type << right << setw(20) << "pre-tax: " << setprecision(2) << prices.net() << right << setw(10) << "\ttotal: " << prices.taxed_final() << "\n";
    }

    void report_Form_detailed(int order_num) const{

        // display details for the singular order
        //  Table header
        cout << "===========================================\n";
        cout << left << setw(25) << setfill(' ') << "Item"
             << right << setw(8) << "Qty"
             << right << setw(10) << "Price" << "\n";
        cout << "-------------------------------------------\n";

        // Hotpot Type
        cout << "Hotpot Type: " << hotpot_type << "\n";

        for (int i = 0; i < menu_hotpot_types; i++)
        {
            if (!hotpot_flavor_order[i].name.empty() && hotpot_flavor_order[i].price > 0)
            {
                cout << left << setw(25) << hotpot_flavor_order[i].name
                     << right << setw(8) << 1 // hotpot base always qty 1
                     << right << setw(10) << fixed << setprecision(2) << hotpot_flavor_order[i].price
                     << "\n";
            }
        }

        // Addons
        cout << "\nAddons: \n";
        for (int i = 0; i < menu_addons_types; i++)
        {
            if (addons_order[i].amount > 0)
            {
                cout << left << setw(25) << addons_order[i].name
                     << right << setw(8) << addons_order[i].amount
                     << right << setw(10) << fixed << setprecision(2) << addons_order[i].netTotal()
                     << "\n";
            }
        }

        // Desserts
        cout << "\nDesserts: \n";
        for (int i = 0; i < menu_desserts_types; i++)
        {
            if (desserts_order[i].amount > 0)
            {
                cout << left << setw(25) << desserts_order[i].name
                     << right << setw(8) << desserts_order[i].amount
                     << right << setw(10) << fixed << setprecision(2) << desserts_order[i].netTotal()
                     << "\n";
            }
        }

        cout << "-------------------------------------------\n";
        cout << left << setw(25) << "Subtotal"
             << right << setw(18) << fixed << setprecision(2) << prices.net() << "\n";

        cout << left << setw(25) << "Service Tax (6%)"
             << right << setw(18) << fixed << setprecision(2) << prices.tax_amount() << "\n";

        cout << left << setw(25) << "TOTAL"
             << right << setw(18) << fixed << setprecision(2) << prices.taxed_final() << "\n";

        cout << "===========================================\n";
    }
};

namespace
{
    // clean up the stream
    void cleanup()
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    // orginally mean new category but is too useful, so got used elsewhere
    void newCat()
    {
        //based on system cmd clearing
        #ifdef _WIN32
            system("CLS");
        #else
            system("clear");
        #endif
    }

    // art work here
    void logo()
    {
        cout << "                      @@     @       @    @         @@               @*      @@        " << "\n";
        cout << "                         =@@@ @     *    @           @@            @@     =@  @        " << "\n";
        cout << "                            @@@   @@         @        @         -@   @-  @@            " << "\n";
        cout << "            @@             @@    @@         @        @@           @ @   @:             " << "\n";
        cout << "     @           @              @                  @@                                  " << "\n";
        cout << "      @           @             @                 @@   @@  @@@@@                       " << "\n";
        cout << "       @@@@   @   @@             @@                    @  @@@@  @@                     " << "\n";
        cout << "           @@@  @   @               @                   @       @                      " << "\n";
        cout << "                 @@@@                 @@@@@@@@@@@@        @@@@@@                       " << "\n";
        cout << "                                     @@@@@@@@@@@@@@                                    " << "\n";
        cout << "                                                                                       " << "\n";
        cout << "             @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@             " << "\n";
        cout << "          @@  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@  @@@         " << "\n";
        cout << "          @@                                                               @@@         " << "\n";
        cout << "         @@% @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ @@@@        " << "\n";
        cout << "      #@@@    @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@   @@@@      " << "\n";
        cout << "                 @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    @@@@@@                 " << "\n";
        cout << "                   @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@    @@@@@@@                   " << "\n";
        cout << "                      @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      @@@@@@@                      " << "\n";
        cout << "                           @@@@@@@@@@@@@@@@@@       #@@@@@@@@                          " << "\n";
        cout << "                                   @@@@@@@@@@@@@@@@@#                                  " << "\n";
        cout << "                           @@@@@@@@                 @@@@@@@@                           " << "\n";
        cout << "                           @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@                          " << "\n";
        cout << "                         @@+================================@                          " << endl;
    }

    // compare between flavor chosen and already chosen flavor(s), function is made for hotpot flavors only
    bool isChosen(const string first, const OrderLine second[], int size)
    { // const cause values wont be modified
        for (int x = 0; x < size; x++)
        {
            if (second[x].name == first)
                return true;
        }
        return false;
    }

    bool exists_item(OrderLine cat_order[], int size)
    {
        for (size_t i = 0; i < size; i++)
        {
            if(!cat_order[i].name.empty())
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

    Prices receipt(
        HotpotType hotpot_type,
        OrderLine hotpot_orders[],
        OrderLine addon_orders[],
        OrderLine dessert_orders[],
        int total_flavors,
        int total_addons,
        int total_desserts)
    {
        time_t now = time(0);
        tm ltm;
        localtime_s(&ltm, &now);

        cout << "==========================================\n";
        cout << "         Chong Qing Spicy Hotpot\n";
        cout << "     8, Jalan Raja Abdullah, Chow Kit\n";
        cout << "          50300 Kuala Lumpur\n";
        cout << "          Tel: 012-345-6789\n";
        cout << "==========================================\n";

        cout << "Order No: " << 173 << "\n";
        cout << "Date:     " << setw(2) << setfill('0') << ltm.tm_mday << "-"
             << setw(2) << setfill('0') << (ltm.tm_mon + 1) << "-"
             << (1900 + ltm.tm_year) << "  "
             << setw(2) << setfill('0') << ltm.tm_hour << ":"
             << setw(2) << setfill('0') << ltm.tm_min << "\n";
        cout << "------------------------------------------\n";

        double nett = 0.0;

        // Table header
        cout << left << setw(25) << setfill(' ') << "Item"
             << right << setw(8) << "Qty"
             << right << setw(10) << "Price" << "\n";
        cout << "------------------------------------------\n";

        // Hotpot Type
        cout << "Hotpot Type: " << type_hotpot(hotpot_type) << "\n";

        for (int i = 0; i < total_flavors; i++)
        {
            if (!hotpot_orders[i].name.empty() && hotpot_orders[i].price > 0)
            {
                cout << left << setw(25) << hotpot_orders[i].name
                     << right << setw(8) << 1 // hotpot base always qty 1
                     << right << setw(10) << fixed << setprecision(2) << hotpot_orders[i].price
                     << "\n";
                nett += hotpot_orders[i].price;
            }
        }

        // Addons
        for (int i = 0; i < total_addons; i++)
        {
            if (addon_orders[i].amount > 0)
            {
                cout << left << setw(25) << addon_orders[i].name
                     << right << setw(8) << addon_orders[i].amount
                     << right << setw(10) << fixed << setprecision(2) << addon_orders[i].netTotal()
                     << "\n";
                nett += addon_orders[i].netTotal();
            }
        }

        // Desserts
        for (int i = 0; i < total_desserts; i++)
        {
            if (dessert_orders[i].amount > 0)
            {
                cout << left << setw(25) << dessert_orders[i].name
                     << right << setw(8) << dessert_orders[i].amount
                     << right << setw(10) << fixed << setprecision(2) << dessert_orders[i].netTotal()
                     << "\n";
                nett += dessert_orders[i].netTotal();
            }
        }

        cout << "------------------------------------------\n";
        cout << left << setw(25) << "Subtotal"
             << right << setw(18) << fixed << setprecision(2) << nett << "\n";

        double service_tax = nett * 0.06; // 6% service tax
        double total = nett + service_tax;

        cout << left << setw(25) << "Service Tax (6%)"
             << right << setw(18) << fixed << setprecision(2) << service_tax << "\n";

        cout << left << setw(25) << "TOTAL"
             << right << setw(18) << fixed << setprecision(2) << total << "\n";

        cout << "==========================================\n";
        cout << "     Thank you! Please Come Again!\n";
        cout << "==========================================\n";

        return {nett, total, service_tax};
    }

    int ordar(Report report[], int report_no)
    {
        /*
        ============
        Deifnitions
        ============
        */

        HotpotType hotpot_type{};

        // max amount of flavor combo, four-flavor type
        const int chosen_flavors_cap = 4;
        OrderLine chosen_flavors[chosen_flavors_cap] = {{}, {}, {}, {}};
        OrderLine chosen_addons[menu_addons_types] = {};
        OrderLine chosen_desserts[menu_desserts_types] = {};

        /*
        =================
        Prompting starts
        =================
        */

        // check hotpot types selection + input
        while (true)
        {
            // if second time ordering, ask if want to pick soup
            // new lines
            newCat();
            cout << "Our hotpot types: " << endl;

            // display hotpot types from first to last
            for (int i = 0; i < static_cast<int>(HotpotType::Count) - 1; i++)
            {
                cout << i + 1 << ". " << hotpot_types[i] << "\n";
            }

            // take selection and see if valid
            cout << "---------------------------------\n";
            cout << "\nWhat type of hotpot do you want?\n> ";
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
        // new lines
        newCat();
        cout << "Choose your soup base:\n\n";
        int flavor = 0, flavor2 = 0, flavor3 = 0, flavor4 = 0;
        for (int y = 0; y < menu_hotpot_types; y++)
        {
            cout << y + 1 << ". " << hotpot_menu[y].name << endl;
        }

        // flavor selection for hotpot(s), cannot pick the same one again
        int chosen_flavor_index = 0;
        switch (hotpot_type)
        {
        case HotpotType::Singular:
            cout << "\n---------------------------------\n\n";
            cout << "\nYou chose Singular-flavor hotpot\n";
            while (true)
            {
                cout << "pick your flavor\n> ";
                if (!(cin >> flavor) || flavor > menu_hotpot_types || flavor <= 0)
                {
                    cout << "invalid hotpot flavor \n";
                    cleanup();
                    continue;
                }
                chosen_flavors[chosen_flavor_index] = hotpot_menu[flavor - 1].order();
                break;
            }
            break;
        case HotpotType::Yuanyang:
            cout << "\n---------------------------------\n\n";
            cout << "\nYou chose Yuanyang hotpot, pick 2 flavors\n";
            while (true)
            {
                cout << "pick your flavor\n> ";
                if (!(cin >> flavor) || flavor > menu_hotpot_types || flavor <= 0)
                {
                    cout << "invalid hotpot flavor \n";
                    cleanup();
                    continue;
                }
                chosen_flavors[chosen_flavor_index] = hotpot_menu[flavor - 1].order();
                chosen_flavor_index++;
                break;
            }

            while (true)
            {
                cout << "\npick your flavor 2\n> ";
                if (!(cin >> flavor2) || flavor2 > menu_hotpot_types || flavor2 <= 0)
                {
                    cout << "invalid hotpot flavor \n";
                    cleanup();
                    continue;
                }
                if (isChosen(hotpot_menu[flavor2 - 1].name, chosen_flavors, chosen_flavor_index))
                {
                    cout << "Flavor repeated haiya\n";
                    cleanup();
                    continue;
                }
                chosen_flavors[chosen_flavor_index] = hotpot_menu[flavor2 - 1].order();
                chosen_flavor_index++;
                break;
            }
            break;
        case HotpotType::FourFlavor:
            cout << "\n---------------------------------\n\n";
            cout << "You chose Four-flavor hotpot, pick 4 flavors\n";
            while (true)
            {
                cout << "pick your flavor\n> ";
                if (!(cin >> flavor) || flavor > menu_hotpot_types || flavor <= 0)
                {
                    cout << "invalid hotpot flavor \n";
                    cleanup();
                    continue;
                }
                chosen_flavors[chosen_flavor_index] = hotpot_menu[flavor - 1].order();
                chosen_flavor_index++;
                break;
            }

            while (true)
            {
                cout << "pick your flavor 2\n> ";
                if (!(cin >> flavor2) || flavor2 > menu_hotpot_types || flavor2 <= 0)
                {
                    cout << "invalid hotpot flavor no. 2 \n";
                    cleanup();
                    continue;
                }
                if (isChosen(hotpot_menu[flavor2 - 1].name, chosen_flavors, chosen_flavor_index))
                {
                    cout << "Flavor repeated haiya\n";
                    cleanup();
                    continue;
                }
                chosen_flavors[chosen_flavor_index] = hotpot_menu[flavor2 - 1].order();
                chosen_flavor_index++;
                break;
            }

            while (true)
            {
                cout << "\npick your flavor 3\n> ";
                if (!(cin >> flavor3) || flavor3 > menu_hotpot_types || flavor3 <= 0)
                {
                    cout << "invalid hotpot flavor no. 3 \n";
                    cleanup();
                    continue;
                }
                if (isChosen(hotpot_menu[flavor3 - 1].name, chosen_flavors, chosen_flavor_index))
                {
                    cout << "Flavor repeated haiya\n";
                    cleanup();
                    continue;
                }
                chosen_flavors[chosen_flavor_index] = hotpot_menu[flavor3 - 1].order();
                chosen_flavor_index++;
                break;
            }

            while (true)
            {
                cout << "\npick your flavor 4\n> ";
                if (!(cin >> flavor4) || flavor4 > menu_hotpot_types || flavor4 <= 0)
                {
                    cout << "invalid hotpot flavor no. 4 \n";
                    cleanup();
                    continue;
                }
                if (isChosen(hotpot_menu[flavor4 - 1].name, chosen_flavors, chosen_flavor_index))
                {
                    cout << "Flavor repeated haiya\n";
                    cleanup();
                    continue;
                }
                chosen_flavors[chosen_flavor_index] = hotpot_menu[flavor4 - 1].order();
                chosen_flavor_index++;
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
       //new lines
        newCat();
        cout << "Pick your addons\n\n";
        // display addons menu
        for (int i = 0; i < menu_addons_types; i++)
        {
            cout << i + 1 << ". " << addons_menu[i].name << " - RM" << fixed << setprecision(2) << addons_menu[i].price << "\n";
        }

        // addons selection, max_selection as cap
        cout << "---------------------------------\n";
        cout << "\npick your addon(s) or 0 to continue.\n(use negative numbers to subtract from order)\n" << endl;
        while (true)
        {
            int addon_choice = 0, addon_amount = 0;
            cout << "addon choice > ";
            if (!(cin >> addon_choice) || addon_choice > menu_addons_types || addon_choice < 0)
            {
                cout << "invalid addon choice\n";
                cleanup();
                continue;
            }
            else if (addon_choice == 0) 
            {
                if(exists_item(chosen_addons, menu_addons_types))
                {
                    newCat();
                    cout << "you chose addons: \n";

                    // loop through addons that are not the same that has been chosen before, and print out the price for further changes
                    for (int i = 0; i < menu_addons_types; i++)
                    {
                        if (chosen_addons[i].amount > 0)
                            cout << i + 1 << ". " << chosen_addons[i].name << setw(30) << "-" << setw(5) << " RM" << fixed << setprecision(2) << chosen_addons[i].price << setw(7) << "-" << setw(7) << chosen_addons[i].amount << "\n";
                    }

                    //put inside if functin because, if basket doesn't have item, don't need to ask to continue
                    char conti = ' ';
                    cout << "\ndo you wish to continue? (y/n)\n> ";
                    if(cin >> conti && toupper(conti) == 'Y')
                        break;
                }
                continue;
            }

            cout << "Addon amount > ";
            if (!(cin >> addon_amount) || addon_amount == 0) // mmm
            {
                cout << "invalid amount\n";
                cleanup();
                continue;
            }

            // record it and loop until max_addons
            if (chosen_addons[addon_choice - 1].name.empty())
                // just copy addons_menu into chosen_addons but make the amount = 0, see struct MenuItem
                chosen_addons[addon_choice - 1] = addons_menu[addon_choice - 1].order();

            // adding into "amount" inside chosen_addons, see struct OrderLine
            if(addon_amount > 0)
            {
                chosen_addons[addon_choice - 1].addAmount(addon_amount);
                cout << addon_amount << " of " << chosen_addons[addon_choice - 1].name << " added to basket!\n\n";
            }
            else if (addon_amount < 0)
            {
                if (chosen_addons[addon_choice - 1].subtractAmount(addon_amount))
                {
                    cout << addon_amount << " of " << chosen_addons[addon_choice - 1].name << " subtracted to basket!\n";
                }else{
                    cout <<"error";
                    cleanup();
                    continue;
                }
            }
            continue;
        }

        /*
        ===================
        Desserts selection
        ===================
        */
        newCat();
        cout << "pick your dessert (at least one is mandatory)";
        cout << "\n\n---------------------------------\n";
        for (int z = 0; z < menu_desserts_types; z++)
        {
            cout << z + 1 << ". " << desserts_menu[z].name << " - RM" << fixed << setprecision(2) << desserts_menu[z].price << "\n";
        }

        cout << "\n---------------------------------\n";
        cout << "pick your desserts or 0 to continue" << endl;
        while (true)
        {
            int dessert_choice = 0, dessert_amount = 0;
            cout << "dessert > ";
            if (!(cin >> dessert_choice) || dessert_choice > menu_desserts_types || dessert_choice < 0)
            {
                cout << "stop finding errors everywhere\n";
                cout << "Invalid input, please enter a number between 0 and " << menu_desserts_types << ".\n";
                cleanup();
                continue;
            }
            else if (dessert_choice == 0)
            {
                if (!(exists_item(chosen_desserts, menu_desserts_types)))
                {
                    cout << "pick your dessert (at least one is mandatory)\n";
                    cleanup();
                    continue;
                }

                if (exists_item(chosen_desserts, menu_desserts_types))
                {
                    newCat();
                    cout << "\n\n";
                    cout << "you chose desserts: \n";

                    // loop through desserts, and see which exists
                    for (int i = 0; i < menu_desserts_types; i++)
                    {
                        if (chosen_desserts[i].amount > 0)
                            cout << "\n"
                                 << i + 1 << ". " << chosen_desserts[i].name << " - RM" << fixed << setprecision(2) << chosen_desserts[i].price << " - " << chosen_desserts[i].amount << " " << "order";
                    }
                }

                char conti = ' ';
                cout << "\n---------------------------------\n";
                cout << "\ndo you wish to continue? (y/n)\n> ";
                if (cin >> conti && toupper(conti) == 'Y')
                    break;
                cout << " ";
                continue;
            }

            cout << "Dessert amount > ";
            if (!(cin >> dessert_amount) || dessert_choice > menu_desserts_types || dessert_amount == 0)
            {
                cout << "cannot";
                cleanup();
                continue;
            }

            // also record and stop if press 0
            if (chosen_desserts[dessert_choice - 1].name.empty())
                chosen_desserts[dessert_choice - 1] = desserts_menu[dessert_choice - 1].order();

            if (dessert_amount > 0)
            {
                chosen_desserts[dessert_choice - 1].addAmount(dessert_amount);
                cout << dessert_amount << " " << chosen_desserts[dessert_choice - 1].name << " added to basket!\n";
            }
            else if (dessert_amount < 0)
            {
                if (chosen_desserts[dessert_choice - 1].subtractAmount(dessert_amount))
                {
                    cout << dessert_amount << " " << chosen_desserts[dessert_choice - 1].name << " subtracted from basket!\n"; 
                }else{
                    (cout << "error\n");
                    cleanup();
                    continue;
                }
            }
            continue;
        }

        // ascii art for receipt
        // chosen_desserts, hotpot_type, chosen_flavor
        // print receipt + calculations
        newCat();
        report[report_no].prices = receipt(hotpot_type, chosen_flavors, chosen_addons, chosen_desserts, chosen_flavors_cap, menu_addons_types, menu_desserts_types);
        
        //copy everything into report's current iteration
        report[report_no].hotpot_type = type_hotpot(hotpot_type);
        for (int i = 0; i < chosen_flavors_cap; i++)
            report[report_no].hotpot_flavor_order[i] = chosen_flavors[i];
        for (int i = 0; i < menu_addons_types; i++)
            report[report_no].addons_order[i] = chosen_addons[i];
        for (int i = 0; i < menu_desserts_types; i++)
            report[report_no].desserts_order[i] = chosen_desserts[i];

        cout << "\npress any key to continue\n> ";
        cleanup();
        cin.get();

        return report_no + 1;
    }

    void report(Report rep[], int max_rep)
    {
        int chosen_report = 0;
        do
        {
            newCat();
            cout << "Report for Chong Ching Hotpot\n\n";
            for(int i = 0; i < max_rep; i++)
            {
                if(rep[i].prices.net() > 0)
                {
                    cout << i + 1 << ". ";
                    rep[i].report_Form_simple();
                }
            }

            cout << "\n---------------------------------\n";
            cout << "\ninput order number to view detailed report or 0 to continue\n> ";
            if((cin >> chosen_report) && chosen_report > 0 && chosen_report <= max_rep)
            {
                cout << "\n\n";
                rep[chosen_report - 1].report_Form_detailed(chosen_report);
            }
            else{
                cleanup();
                cout << "\n\ninvalid input" << endl;
                continue;
            }
            cout << "\npress any key to continue\n> "; //test is inputing 0 still let me leave this
            cleanup();
            cin.get();
            break;

        }while (chosen_report != 0);
    }

    int code()
    {
        int choice = 0;
        int iteration = 0;
        const int max_reports = 10;
        Report reports[max_reports] = {};
        do
        {
            newCat();
            choice = 0;
            logo();

            // display menu
            cout << "\n========================================================================================================\n";
            cout << "Welcome to Chongqing Spicy Hotpot!\n" << endl;
            cout << "1. order\n" << "2. report\n" << "3. exit\n> ";

            if(!(cin >> choice) || choice <= 0 || choice > 3)
                cleanup();

            switch (choice)
            {
            case 1:
                // at max set report, don't record anymore
                if (iteration >= max_reports)
                {
                    cout << "max orders reached per one instance\n";
                    cleanup();
                    continue;
                }
                iteration = ordar(reports, iteration);
                break;

            case 2:
                report(reports, max_reports);

            default:
                break;
            }
            continue;
        }while(choice != 3);

        cout << "\nexiting\n";
        return 0;
    }
}

// enum for menu categorization, enum = using name instead of number for categorization

// so clean
int main()
{
    return code();
}