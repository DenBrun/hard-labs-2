#include "countriesTable.h"
#include <filesystem>

class CSVReader
{
protected:
    std::vector<std::string> splitString(std::string str, std::string delimiter = " ");
    std::vector<std::filesystem::path> findFilesFromDirectory(std::string directory, std::string extension);

public:
    std::vector<std::vector<std::string>> readCSV(std::filesystem::path path);
};

class CountryCSVReader : public CSVReader
{
public:
    std::vector<Country> readAndParseCountries(std::filesystem::path path);
    CountriesTable readAndParseCountriesFromDirectory(std::string directory);
};