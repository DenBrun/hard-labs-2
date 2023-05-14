#include "CSVReader.h"
#include <fstream>
#include <sstream>
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
    ifstream file(path);
    if (!file.is_open())
    {
        throw invalid_argument("Filename " + path.filename().string() + " not found.");
    }

    string line;
    getline(file, line);

    if (line.length() == 0)
    {
        throw invalid_argument("File " + path.filename().string() + " does not contain any data.");
    }

    int numLines;
    stringstream ss(line);

    if (!(ss >> numLines && ss.eof()) || numLines == 0)
    {
        throw invalid_argument("Number of lines in " + path.filename().string() + " has a wrong fornat: " + line);
    }

    vector<vector<string>> lines;
    while (getline(file, line))
    {
        lines.push_back(splitString(line, ","));
    }
    if (!file.eof() || lines.size() != numLines)
    {
        throw invalid_argument("File " + path.filename().string() + " has a wrong format. Number of lines (" +
                               to_string(numLines) + ") doesn't match the real file length.");
    }

    file.close();
    return lines;
}
