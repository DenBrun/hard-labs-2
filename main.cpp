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
        vector<Country> countries = countries_reader.readAndParseCountriesFromDirectory("examples_2/var1");
        cout << countries.size() << endl;
        for (auto &country : countries)
        {
            cout << country.to_string() << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}
