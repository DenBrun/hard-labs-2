#include "CSVReader.h"
class CountryCSVReader : public CSVReader
{
public:
    std::vector<Country> readAndParseCountries(std::filesystem::path path);
    CountriesTable readAndParseCountriesFromDirectory(std::string directory);
};