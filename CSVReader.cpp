#include "CSVReader.h"
#include <fstream>
#include <sstream>
using namespace std;

vector<string> CSVReader::splitString(string str, string delimiter)
{
    vector<string> res;
    size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != string::npos)
    {
        res.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }
    res.push_back(str.substr(start));
    return res;
}

vector<filesystem::path> CSVReader::findFilesFromDirectory(string directory, string extension)
{
    if (!filesystem::exists(directory))
    {
        throw invalid_argument("The directory " + directory + " doesn't exist.");
    }
    vector<filesystem::path> csv_files;
    for (const auto &filename : filesystem::directory_iterator(directory))
    {
        if (filename.path().extension() == extension)
        {
            csv_files.push_back(filename.path());
        }
    }
    if (csv_files.empty())
    {
        throw invalid_argument("The directory " + directory + " doesn't contain any " + extension + " files.");
    }
    return csv_files;
}

vector<vector<string>> CSVReader::readCSV(filesystem::path path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        throw invalid_argument("Filename " + path.filename().string() + " not found");
    }
    string line;
    getline(file, line);

    const int numLines = stoi(line);

    vector<vector<string>> lines;
    for (int i = 0; i < numLines; i++)
    {
        getline(file, line);
        lines.push_back(splitString(line, ","));
    }

    file.close();
    return lines;
}

vector<Country> CountryCSVReader::readAndParseCountries(filesystem::path path)
{
    vector<vector<string>> csvLines = this->readCSV(path);
    vector<Country> countries;
    for (auto &line : csvLines)
    {
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
                throw invalid_argument("Value " + line[i] + " in the line doesn't match the int value");
            }
        }
        country.calculate_votes_sum();
        countries.push_back(country);
    }
    return countries;
}

std::vector<Country> CountryCSVReader::readAndParseCountriesFromDirectory(std::string directory)
{
    vector<Country> countries;
    vector<filesystem::path> csv_files = this->findFilesFromDirectory(directory, ".csv");
    for (auto &file : csv_files)
    {
        vector<Country> new_file_countries = this->readAndParseCountries(file);
        countries.insert(countries.end(), new_file_countries.begin(), new_file_countries.end());
    }
    return countries;
}