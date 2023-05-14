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
    // Chain of resp FluentValidator
    // ValidationResult => vector<ValidationWarning>  vector<ValidationError>
    ifstream file(path);
    if (!file.is_open())
    {
        throw invalid_argument("Filename " + path.filename().string() + " not found.");
    }

    string line;
    getline(file, line);

    if (line.length() == 0)
    {
        throw invalid_argument("File " + path.filename().string() + " does not contain any data.");
    }

    int numLines;
    stringstream ss(line);

    if (!(ss >> numLines && ss.eof()) || numLines == 0)
    {
        throw invalid_argument("Number of lines in " + path.filename().string() + " has a wrong fornat: " + line);
    }

    vector<vector<string>> lines;
    while (getline(file, line))
    {
        lines.push_back(splitString(line, ","));
    }
    if (!file.eof() || lines.size() != numLines)
    {
        throw invalid_argument("File " + path.filename().string() + " has a wrong format. Number of lines (" +
                               to_string(numLines) + ") doesn't match the real file length.");
    }

    file.close();
    return lines;
}

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