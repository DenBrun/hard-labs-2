#include <string>
#include <vector>

class Country
{
private:
    std::string name;
    std::vector<int> votes;
    int points = 0;

public:
    Country(std::string name);
    void add_vote(int score);
    void add_points(int value);
    int get_vote(size_t column);
    std::string to_string();
    int get_points();
};