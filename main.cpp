#include "CSVReader.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    // ./main examples_2/var1

    if (argc != 2)
    {
        cerr << "main: program requires 1 positional argument - directory path\n";
        cerr << "usage: main <directory_path>\n";
        return 1;
    }

    string directory = argv[1];

    try
    {
        CountryCSVReader countries_reader;
        CountriesTable table = countries_reader.readAndParseCountriesFromDirectory(directory);
        table.calculate_winners();
        table.create_winners_csv();
        cout << "File results.csv was successfully created.\n";
    }
    catch (const invalid_argument &e)
    {
        cerr << e.what() << '\n';
    }
    catch (const exception &e)
    {
        cerr << "The problem during the program execution: " << e.what() << '\n';
    }

    return 0;
}
