#include <string>
#include <vector>

class Country
{
private:
    std::string name;
    std::vector<int> votes;
    int votes_sum;

public:
    Country(std::string name);
    void add_vote(int score);
    int calculate_votes_sum();
    int get_votes_sum();
    std::string to_string();
};