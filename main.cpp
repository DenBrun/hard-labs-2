#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
void readCSV(string filename);
vector<filesystem::path> findFilesFromDirectory(string directory, string extension);

int main()
{
    try
    {
        vector<filesystem::path> csv_files = findFilesFromDirectory("examples_2/var1", ".csv");
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

void readCSV(string filename)
{
    ifstream file(filename);
    if (!file.is_open())
    {
        throw invalid_argument("Filename " + filename + " not found");
    }
    string line;
    getline(file, line);
    cout << line;
    file.close();
}