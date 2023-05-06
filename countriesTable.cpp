#include "countriesTable.h"
#include <algorithm>
#include <fstream>
using namespace std;

CountriesTable::CountriesTable(vector<Country> countries)
{
    this->countries = countries;
    this->columns = countries[0].get_columns();
    this->rows = countries.size();
}

void CountriesTable::sort_by_column(size_t n)
{
    sort(this->countries.begin(), this->countries.end(), [n](Country &c1, Country &c2)
         { return c1.get_vote(n) > c2.get_vote(n); });
}

size_t CountriesTable::get_rows()
{
    return this->rows;
}

size_t CountriesTable::get_columns()
{
    return this->columns;
}

vector<Country> CountriesTable::get_countries()
{
    return this->countries;
}

vector<Country> CountriesTable::calculate_winners()
{
    int points_table[10] = {12, 10, 8, 7, 6, 5, 4, 3, 2, 1};
    for (size_t i = 0; i < this->columns; i++)
    {
        this->sort_by_column(i);
        for (size_t j = 0; j < (this->rows < 10 ? this->rows : 10); j++)
        {
            this->countries[j].add_points(points_table[j]);
        }
    }
    sort(this->countries.begin(), this->countries.end(), [](Country &c1, Country &c2)
         { return c1.get_points() > c2.get_points(); });
    this->winners.insert(winners.begin(), this->countries.begin(), this->countries.begin() + 10);
    return this->winners;
}

void CountriesTable::create_winners_csv()
{
    if (this->winners.size() == 0)
    {
        calculate_winners();
    }

    ofstream file("results.csv");
    if (!file.is_open())
    {
        throw invalid_argument("Unable to generate output file");
    }
    for (auto &country : this->winners)
    {

        file << country.get_name() + "," + to_string(country.get_points()) << endl;
    }
    file.close();
}