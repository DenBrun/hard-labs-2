#include "CSVReader.h"
#include <iostream>

using namespace std;

int main()
{
    try
    {
        CountryCSVReader countries_reader;
        CountriesTable table = countries_reader.readAndParseCountriesFromDirectory("examples_2/var1");
        table.calculate_winners();
        table.create_winners_csv();
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}
