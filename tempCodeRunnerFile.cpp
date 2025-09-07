for(int i = 0; i < max_rep; i++)
        {
            if(rep[i].prices.net() > 0)
            {
                cout << i + 1 << ". " << setprecision(2) << rep[i].report_Form_simple() << "\n";
            }
        }