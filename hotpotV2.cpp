#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
struct MenuItem
{
    string name;
    double value;
};
namespace
{
    // clean up stream
    void cleanup()
    {
        cin.clear();
        cin.ignore(1000, '\n');
    }

    void menu(const MenuItem &menu_soup, MenuItem menu_addons[], MenuItem menu_deserts[])
    {
        menu_soup[]
    }
};

int main4()
{
    // constant menu items amount
    const int soup_types = 5;
    const int addons_types = 5;
    const int desserts_types = 5;

    // loop for menu input if invalid
    MenuItem menu_soup_base[soup_types] =
        {
            {"Mala Soup Base", 15.90},
            {"Tomato Soup Base", 14.50},
            {"Pumpkin Soup Base", 13.00},
            {"Yuanyang hotpot", 20.00},
        };
    MenuItem menu_addons[soup_types] =
        {

        };
    MenuItem menu_soup_base[soup_types] =
        {

        };

    do
    {
        // set deal or separate deal
        // special cases yuanyang
        // soup base, addons and desserts loop - 5max
        //  receipt
        menu(menu_soup_base);
        cout << "What would you like to order?\n> ";
        cin >>
    } while (true);

    return 0;
}