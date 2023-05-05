#include "country.h"

Country::Country(std::string name)
{
    this->name = name;
}

void Country::add_vote(int score)
{
    this->votes.push_back(score);
}

void Country::add_points(int value)
{
    this->points += value;
}

int Country::get_vote(size_t column)
{
    return this->votes[column];
}

std::string Country::get_name()
{
    return this->name;
}

std::string Country::to_string()
{
    std::string result = name + ' ';
    for (auto &i : votes)
    {
        result += std::to_string(i) + ' ';
    }
    return result;
}

int Country::get_points()
{
    return this->points;
}