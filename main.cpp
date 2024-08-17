#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include "DirectoryComparator.h"
#include "HashingUtility.h"

using namespace std; 

int main(int argc, char *argv[])
{
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <directory_a> <directory_b>" << endl;
        return 1;
    }

    string dir_a = argv[1];
    string dir_b = argv[2];

    try {
        // Initialize DirComparator
        DirectoryComparator dc(dir_a, dir_b);

        // Compare directories

        // Write output files
    } catch (exception& e) {
        cerr << "Error: " << e.what() << endl;
        return 2;
    }

    return 0;
}