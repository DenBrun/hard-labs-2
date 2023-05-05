#include "country.h"

Country::Country(std::string name)
{
    this->name = name;
}

void Country::add_vote(int score)
{
    this->votes.push_back(score);
}

int Country::get_vote(size_t column)
{
    return this->votes[column];
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