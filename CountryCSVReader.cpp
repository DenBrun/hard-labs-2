#include "CountryCSVReader.h"
#include <sstream>
using namespace std;

void CountryCSVReader::validateFileContent(vector<vector<string>> csvLines, string filename)
{
    string errors = "";
    int line_length = csvLines[0].size();
    for (size_t line_num = 0; line_num < csvLines.size(); line_num++)
    {
        vector<string> line = csvLines[line_num];

        if (line.size() != line_length)
        {
            errors.append("Different number of columns: (line 2, " + to_string(line_num + 2) + ").\n");
        }
        for (size_t i = 1; i < line.size(); i++)
        {
            int value;
            stringstream ss(line[i]);

            if (!(ss >> value && ss.eof()))
            {
                errors.append("Value " + line[i] +
                              " (line " + to_string(line_num + 2) + ") doesn't match the int value.\n");
            }
        }
    }
    if (!errors.empty())
    {
        throw invalid_argument("\nFileContentErrors in file " + filename + ":\n" + errors);
    }
}

vector<Country> CountryCSVReader::readAndParseCountries(filesystem::path path)
{
    vector<vector<string>> csvLines = this->readCSV(path);

    this->validateFileContent(csvLines, path.filename().string());

    vector<Country> countries;
    for (size_t line_num = 0; line_num < csvLines.size(); line_num++)
    {
        vector<string> line = csvLines[line_num];

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
        }
        countries.push_back(country);
    }
    return countries;
}

CountriesTable CountryCSVReader::readAndParseCountriesFromDirectory(string directory)
{
    vector<Country> countries;
    vector<filesystem::path> csv_files = this->findFilesFromDirectory(directory, ".csv");
    int prev_columns = 0;
    for (size_t i = 0; i < csv_files.size(); i++)
    {
        vector<Country> new_file_countries = this->readAndParseCountries(csv_files[i]);
        int new_columns = new_file_countries[0].get_columns();
        if (!prev_columns)
        {
            prev_columns = new_columns;
        }
        else if (prev_columns != new_columns)
        {
            throw invalid_argument("Number of columns is different in files " +
                                   csv_files[i - 1].filename().string() + " " + csv_files[i].filename().string());
        }
        countries.insert(countries.end(), new_file_countries.begin(), new_file_countries.end());
    }
    return CountriesTable(countries);
}