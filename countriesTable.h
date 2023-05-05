#include "country.h"
#include <vector>

class CountriesTable
{
private:
    std::vector<Country> countries;
    std::vector<Country> sort_column(size_t n);

public:
    CountriesTable(std::vector<Country> countries);
    size_t size();
    std::vector<Country> get_countries();
    std::vector<Country> calculate_winners();
};