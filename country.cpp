#include "country.h"

Country::Country(std::string name)
{
    this->name = name;
}

void Country::add_vote(int score)
{
    this->votes.push_back(score);
}

int Country::calculate_votes_sum()
{
    int sum = 0;
    for (const auto &i : this->votes)
    {
        sum += i;
    }
    this->votes_sum = sum;
    return sum;
}

int Country::get_votes_sum()
{
    return this->votes_sum;
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