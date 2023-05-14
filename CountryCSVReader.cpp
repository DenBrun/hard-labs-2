#include "CountryCSVReader.h"
#include <sstream>
using namespace std;

vector<Country> CountryCSVReader::readAndParseCountries(filesystem::path path)
{
    vector<vector<string>> csvLines = this->readCSV(path);
    vector<Country> countries;
    int line_length = csvLines[0].size();
    for (size_t line_num = 0; line_num < csvLines.size(); line_num++)
    {
        vector<string> line = csvLines[line_num];

        if (line.size() != line_length)
        {
            throw invalid_argument("File " + path.filename().string() +
                                   " doesn't have the same number of columns (line 2, " + to_string(line_num + 2) + ").");
        }

        string countryName = line[0];
        Country country(countryName);
        for (size_t i = 1; i < line.size(); i++)
        {
            int value;
            stringstream ss(line[i]);

            if (ss >> value && ss.eof())
            {
                country.add_vote(value);
            }
            else
            {
                throw invalid_argument("Value " + line[i] + " in the file " + path.filename().string() +
                                       " (line " + to_string(line_num + 2) + ") doesn't match the int value.");
            }
        }
        countries.push_back(country);
    }
    return countries;
}

CountriesTable CountryCSVReader::readAndParseCountriesFromDirectory(std::string directory)
{
    vector<Country> countries;
    vector<filesystem::path> csv_files = this->findFilesFromDirectory(directory, ".csv");
    for (auto &file : csv_files)
    {
        vector<Country> new_file_countries = this->readAndParseCountries(file);
        countries.insert(countries.end(), new_file_countries.begin(), new_file_countries.end());
    }
    return CountriesTable(countries);
}