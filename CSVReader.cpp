#include "CSVReader.h"
#include "FileValidator.h"
#include <fstream>
using namespace std;

vector<string> CSVReader::splitString(string str, string delimiter)
{
    vector<string> res;
    size_t start = 0, end = 0;

    while ((end = str.find(delimiter, start)) != string::npos)
    {
        res.push_back(str.substr(start, end - start));
        start = end + delimiter.length();
    }
    res.push_back(str.substr(start));
    return res;
}

vector<filesystem::path> CSVReader::findFilesFromDirectory(string directory, string extension)
{
    if (!filesystem::exists(directory))
    {
        throw invalid_argument("The directory " + directory + " doesn't exist.");
    }
    vector<filesystem::path> csv_files;
    for (const auto &filename : filesystem::directory_iterator(directory))
    {
        if (filename.path().extension() == extension)
        {
            csv_files.push_back(filename.path());
        }
    }
    if (csv_files.empty())
    {
        throw invalid_argument("The directory " + directory + " doesn't contain any " + extension + " files.");
    }
    return csv_files;
}

vector<vector<string>> CSVReader::readCSV(filesystem::path path)
{
    // Chain of resp FluentValidator
    // ValidationResult => vector<ValidationWarning>  vector<ValidationError>
    FileExistsValidator *exists = new FileExistsValidator;
    NonEmptyFileValidator *not_empty = new NonEmptyFileValidator;
    NumLinesValidator *num_lines = new NumLinesValidator;
    exists->setNext(not_empty)->setNext(num_lines);

    string validationResult = exists->validate(path);

    if (!validationResult.empty())
    {
        throw invalid_argument(validationResult);
    }

    ifstream file(path);
    string line;
    getline(file, line);

    vector<vector<string>> lines;
    while (getline(file, line))
    {
        lines.push_back(splitString(line, ","));
    }

    file.close();
    return lines;
}
