#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
vector<string> *readCSV(filesystem::path path);
vector<filesystem::path> findFilesFromDirectory(string directory, string extension);
vector<string> splitString(string str, string delimiter = " ");

int main()
{
    try
    {
        vector<filesystem::path> csv_files = findFilesFromDirectory("examples_2/var1", ".csv");
        vector<string> *lines = readCSV(csv_files[0]);
        cout << lines[2][0];
        delete[] lines;
        // splitString("Czech Republic,908743,761324,625681", ",");
    }
    catch (const exception &e)
    {
        cerr << e.what() << '\n';
    }

    return 0;
}

vector<filesystem::path> findFilesFromDirectory(string directory, string extension)
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

vector<string> *readCSV(filesystem::path path)
{
    ifstream file(path);
    if (!file.is_open())
    {
        throw invalid_argument("Filename " + path.filename().string() + " not found");
    }
    string line;
    getline(file, line);

    const int numLines = stoi(line);

    vector<string> *lines = new vector<string>[numLines];
    for (int i = 0; i < numLines; i++)
    {
        getline(file, line);
        lines[i] = splitString(line, ",");
    }

    file.close();
    return lines;
    // delete[] lines;
}

vector<string> splitString(string str, string delimiter)
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