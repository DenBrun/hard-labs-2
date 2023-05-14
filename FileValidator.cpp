#include "FileValidator.h"
#include <fstream>
#include <sstream>

Validator *Validator::setNext(Validator *next)
{
    this->nextValidator = next;
    return next;
}

string FileExistsValidator::validate(const filesystem::path &path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        return "Filename " + path.filename().string() + " not found.";
    }
    file.close();

    if (this->nextValidator != nullptr)
    {
        return this->nextValidator->validate(path);
    }
    return "";
}

string NonEmptyFileValidator::validate(const filesystem::path &path)
{
    ifstream file(path);
    string line;
    getline(file, line);

    if (line.length() == 0)
    {
        return "File " + path.filename().string() + " does not contain any data.";
    }
    file.close();
    if (this->nextValidator != nullptr)
    {
        return this->nextValidator->validate(path);
    }
    return "";
}

string NumLinesValidator::validate(const filesystem::path &path)
{
    ifstream file(path);
    string line;
    getline(file, line);

    int numLines;
    stringstream ss(line);

    if (!(ss >> numLines && ss.eof()) || numLines == 0)
    {
        return "Number of lines in " + path.filename().string() + " has a wrong fornat: " + line;
    }

    int lineCount = 0;
    while (getline(file, line))
    {
        lineCount++;
    }

    if (!file.eof() || lineCount != numLines)
    {
        return "File " + path.filename().string() + " has a wrong format. Number of lines (" +
               to_string(numLines) + ") doesn't match the real file length.";
    }

    file.close();
    if (this->nextValidator != nullptr)
    {
        return this->nextValidator->validate(path);
    }
    return "";
}