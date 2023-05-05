#include "countriesTable.h"
#include <algorithm>
using namespace std;

CountriesTable::CountriesTable(vector<Country> countries)
{
    this->countries = countries;
}

vector<Country> CountriesTable::sort_column(size_t n)
{
    vector<Country> column = this->countries;
    sort(column.begin(), column.end(), [n](Country &c1, Country &c2)
         { return c1.get_vote(n) > c2.get_vote(n); });
    return column;
}

size_t CountriesTable::size()
{
    return this->countries.size();
}

vector<Country> CountriesTable::get_countries()
{
    return this->countries;
}

vector<Country> CountriesTable::calculate_winners()
{
    return this->sort_column(0);
}