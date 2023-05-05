#include "CSVReader.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    try
    {
        CountryCSVReader countries_reader;
        CountriesTable table = countries_reader.readAndParseCountriesFromDirectory("examples_2/var1");
        // cout << table.size() << endl;
        // for (auto &country : table.get_countries())
        // {
        //     cout << country.to_string() << endl;
        // }
        vector<Country> r = table.calculate_winners();
        for (auto &c : r)
        {
            cout << c.get_points() << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}
