#include <string>
#include <vector>

class Country
{
private:
    std::string name;
    std::vector<int> votes;

public:
    Country(std::string name);
    void add_vote(int score);
    int get_vote(size_t column);
    std::string to_string();
};