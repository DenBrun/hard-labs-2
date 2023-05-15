#include "CSVReader.h"
class CountryCSVReader : public CSVReader
{
private:
    void validateFileContent(std::vector<std::vector<std::string>> csvLines, std::string filename);

public:
    std::vector<Country> readAndParseCountries(std::filesystem::path path);
    CountriesTable readAndParseCountriesFromDirectory(std::string directory);
};