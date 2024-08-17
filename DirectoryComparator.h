#ifndef DIRECTORYCOMPARATOR_H
#define DIRECTORYCOMPARATOR_H

#include <string>
#include <unordered_map>
#include <vector>
#include <filesystem>

using namespace std;

// Class declaration
class DirectoryComparator {
public:
    // Constructor
     DirectoryComparator(const string& dir_a, const string& dir_b);

    // Main function to perform comparison
    void compare();

    // Function to write results to files
    // void writeResults(const std::string& commonFile, const std::string& aOnlyFile, const std::string& bOnlyFile);

    // Destructor
    ~DirectoryComparator();


private:
    // Helper function to traverse a directory and store file paths and their hashes
    void traverseDirectory(const string& dir, unordered_map<string, vector<string>>& fileMap);

    // Helper function to hash a file's content
    string hashFile(const string& filePath);

    string dirA;
    string dirB;

    // Maps to store file hashes and their corresponding file paths
    unordered_map<string, vector<string>> filesA;
    unordered_map<string, vector<string>> filesB;

    // Vectors to store the results
    vector<string> commonFiles;
    vector<string> aOnlyFiles;
    vector<string> bOnlyFiles;
};

#endif // DIRECTORYCOMPARATOR_H