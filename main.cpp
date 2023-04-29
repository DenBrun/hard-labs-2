#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

using namespace std;
void readCSV(string filename);
vector<filesystem::path> readFilesFromDirectory(string directory);

int main()
{
    try
    {
        vector<filesystem::path> csv_files = readFilesFromDirectory("examples_2/var1");
    }
    catch (const exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

vector<filesystem::path> readFilesFromDirectory(string directory)
{
    vector<filesystem::path> csv_files;
    for (const auto &filename : filesystem::directory_iterator(directory))
    {
        cout << filename.path().extension() << endl;
        if (filename.path().extension() == ".csv")
        {
            csv_files.push_back(filename.path());
        }
    }
    if (csv_files.empty())
    {
        throw invalid_argument("The directory " + directory + " doesn't contain any csv files.");
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