#include "DirectoryComparator.h"
#include "HashingUtility.h"
#include <iostream>

// Constructor
DirectoryComparator::DirectoryComparator(const string& dir_a, const string& dir_b)
: dirA(dir_a), dirB(dir_b) {
	cout << __func__<< " dirA --> " << dirA << endl;
	cout << __func__<< " dirB --> " << dirB << endl;
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
    for (const auto& entry : filesystem::recursive_directory_iterator(dir)) {
        if (entry.is_regular_file()) {
            string hash = hashFile(entry.path().string());
            fileMap[hash].push_back(entry.path().string());
        }
    }
}