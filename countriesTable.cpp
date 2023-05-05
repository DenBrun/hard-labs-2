#include "countriesTable.h"
#include <algorithm>
using namespace std;

CountriesTable::CountriesTable(vector<Country> countries)
{
    this->countries = countries;
}

void CountriesTable::sort_by_column(size_t n)
{
    sort(this->countries.begin(), this->countries.end(), [n](Country &c1, Country &c2)
         { return c1.get_vote(n) > c2.get_vote(n); });
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
    int points_table[10] = {12, 10, 8, 7, 6, 5, 4, 3, 2, 1};
    for (size_t i = 0; i < this->size(); i++)
    {
        this->sort_by_column(i);
        for (size_t j = 0; j < (this->size() < 10 ? this->size() : 10); j++)
        {
            this->countries[j].add_points(points_table[j]);
        }
    }
    sort(this->countries.begin(), this->countries.end(), [](Country &c1, Country &c2)
         { return c1.get_points() > c2.get_points(); });
    return this->countries;
}