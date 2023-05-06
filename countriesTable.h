#include "country.h"
#include <vector>

class CountriesTable
{
private:
    std::vector<Country> countries;
    std::vector<Country> winners;
    size_t columns;
    size_t rows;
    void sort_by_column(size_t n);

public:
    CountriesTable(std::vector<Country> countries);
    size_t get_rows();
    size_t get_columns();
    std::vector<Country> get_countries();
    std::vector<Country> calculate_winners();
    void create_winners_csv();
};