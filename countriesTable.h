#include "country.h"
#include <vector>

class CountriesTable
{
private:
    std::vector<Country> countries;

public:
    CountriesTable(std::vector<Country> countries);
    size_t size();
    std::vector<Country> get_countries();
};