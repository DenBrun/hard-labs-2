#include "countriesTable.h"
using namespace std;

CountriesTable::CountriesTable(vector<Country> countries)
{
    this->countries = countries;
}

size_t CountriesTable::size()
{
    return this->countries.size();
}

vector<Country> CountriesTable::get_countries()
{
    return this->countries;
}