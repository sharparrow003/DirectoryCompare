#include "DirectoryComparator.h"
#include "HashingUtility.h"
#include <iostream>
#include <algorithm>

#define COMMON_FILENAME "common.txt"
#define A_ONLY_FILENAME "a_only.txt"
#define B_ONLY_FILENAME "b_only.txt"

// Constructor
DirectoryComparator::DirectoryComparator(const string& dir_a, const string& dir_b)
: dirA(dir_a), dirB(dir_b) {
	cout << __func__<< " dirA: " << dirA << endl;
	cout << __func__<< " dirB: " << dirB << endl;
	cout << __func__<< " DirectoryComparator initialized!" << endl;
}

// Destructor
DirectoryComparator::~DirectoryComparator() {
}

void DirectoryComparator::compare() {
    traverseDirectory(dirA, filesA);
    traverseDirectory(dirB, filesB);

    // Compare hashes
    for (const auto& [hash, pathsA] : filesA) {
        if (filesB.find(hash) != filesB.end()) {
            commonFiles.insert(commonFiles.end(), pathsA.begin(), pathsA.end());
        } else {
            aOnlyFiles.insert(aOnlyFiles.end(), pathsA.begin(), pathsA.end());
        }
    }

    for (const auto& [hash, pathsB] : filesB) {
        if (filesA.find(hash) == filesA.end()) {
            bOnlyFiles.insert(bOnlyFiles.end(), pathsB.begin(), pathsB.end());
        }
    }
}

string DirectoryComparator::hashFile(const string& filePath) {
    return HashingUtility::hashFile(filePath);  // Delegates hashing to a utility
}

void DirectoryComparator::traverseDirectory(const string& dir, unordered_map<string, vector<string>>& fileMap) {
    cout << __func__<< " Traversing " << dir <<" ... " << endl;
    string filePath;
    for (const auto& entry : filesystem::recursive_directory_iterator(dir)) {
        filePath = entry.is_symlink() ? filesystem::read_symlink(entry.path().string()).string() : entry.path().string();
        if (filesystem::is_regular_file(filePath)) {
            try {
                string hash = hashFile(filePath);
                fileMap[hash].push_back(filePath);
            } catch (const filesystem::filesystem_error &e) {
                cerr << "Filesystem error for file " << entry.path() << ": " << e.what() << endl;
            } catch (const exception &e) {
                cerr << "General error for file " << entry.path() << ": " << e.what() << endl;
            }
        }
    }
    cout << __func__<< " Finished Traversing " << dir << endl;
}

void DirectoryComparator::writeResults() {
    cout << __func__<< "Number of common files: " << commonFiles.size() << endl;
    cout << __func__<< "Number of files unique to dirA: " << aOnlyFiles.size() << endl;
    cout << __func__<< "Number of files unique to dirB: " << bOnlyFiles.size() << endl;

    // Sort the vectors
    sort(commonFiles.begin(), commonFiles.end());
    sort(aOnlyFiles.begin(), aOnlyFiles.end());
    sort(bOnlyFiles.begin(), bOnlyFiles.end());

    ofstream commonStream(COMMON_FILENAME);
    for (const auto& path : commonFiles) {
        commonStream << path << endl;
    }

    ofstream aOnlyStream(A_ONLY_FILENAME);
    for (const auto& path : aOnlyFiles) {
        aOnlyStream << path << endl;
    }

    ofstream bOnlyStream(B_ONLY_FILENAME);
    for (const auto& path : bOnlyFiles) {
        bOnlyStream << path << endl;
    }

    cout << __func__<< "Expected result files created (common.txt, a_only.txt, b_only.txt)." << endl;
}