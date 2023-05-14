#include <string>
#include <filesystem>
using namespace std;

class Validator
{
protected:
    Validator *nextValidator = nullptr;

public:
    virtual string validate(const filesystem::path &path) = 0;
    Validator *setNext(Validator *next);
};

class FileExistsValidator : public Validator
{
public:
    string validate(const filesystem::path &path) override;
};

class NonEmptyFileValidator : public Validator
{
public:
    string validate(const filesystem::path &path) override;
};

class NumLinesValidator : public Validator
{
public:
    string validate(const filesystem::path &path) override;
};