## Requirements

**Compiler**: GCC 9.3+, Clang 10.0+, or MSVC 2019+

**CMake**: 3.10 or later

**OpenSSL**: Required for SHA-256 hashing

**GTest**: Required for running unit tests


Originally developed on Linux Ubuntu 18.04

## Installation
### Build from Source 
1. **Clone the repository**
   
   ```
   git clone git@github.com:sharparrow003/DirectoryCompare.git
   cd DirectoryCompare
   ```
2. **Build the project using helper script `build.sh`**
   
   ```
   ./build.sh build
   ```
   
     Build files generated and added to directory build.
## Usage
**Run executable using helper script `build.sh`**
   
   Call build.sh by passing the two directories to be compared as arguments.
   ```
   ./build.sh run test_data/files_a/ test_data/files_b/
   ```

## Testing
### Testing with large number of sample files
**(Option 1) Generate test data using helper script `build.sh`**

   By default this command will create 100,000 files in the directories `test_data/files_a` and `test_data/files_b`.
   
   Refer to `test_data/expected_common.txt`, `test_data/a_only.txt` and `test_data/b_only.txt` for the expected output for the files generated by the script.

  ```
   ./build.sh create_test_data
  ```
**(Option 2) Generate test data using helper script `generate_test_data.py`**

   By default this command will create 100,000 files in the directories `test_data/files_a` and `test_data/files_b`.
   
   Refer to `test_data/expected_common.txt`, `test_data/a_only.txt` and `test_data/b_only.txt` for the expected output for the files generated by the script.

  ```
   python3 generate_test_data.py
  ```

**Run executable with sample test data using helper script build.sh**

  Call build.sh by passing the two directories to be compared as arguments.
   ```
   ./build.sh run test_data/files_a/ test_data/files_b/
   ```

### Unit Testing
   1. **Build unit tests with helper script `build.sh`**

   ```
   build.sh build_unit_tests
   ```

   2. **Run unit tests with helper script `build.sh`**

   ```
   build.sh run_unit_tests
   ```

**NOTE: If CMake cannot find GTest in your Linux environment, here are some steps you can follow to resolve the issue**

```
# These steps work on Ubuntu
sudo apt-get install libgtest-dev
cd /usr/src/gtest
sudo cmake CMakeLists.txt
sudo make
sudo cp *.a /usr/lib
```

## Cleaning
  This command will delete the `build` directory
  
   ```
   ./build.sh clean
   ```

This command will delete the `test_data` directory
  
   ```
   ./build.sh clean_test_data
   ```

This command will delete both the `build` and `test_data` directories
  
   ```
   ./build.sh clean_all
   ```

## Code Structure and Key Files
1. `src/main.cpp`: Entry point of the program. Handles command line argument parsing, initializes `DirectoryComparator` and starts directory comparison process.
2. `src/DirectoryComparator.cpp` and `include/DirectoryComparator.h`: Contains the core logic for comparing directories including file traversal, hasing and result generation.
3. `include/HashingUtility.h`: Provides utilities for hasing file contents using SHA-256
4. `tests`: Directory containing unit tests
5. `generate_test_data.py`: Python script used to generate test directories and files with varying sizes and contents, including subdirectories. The data generated in test_data directory helps stress test the program and verify its correctness.
6. `test_data`: Directory in which sample test data is creaeted and added by the generate_test_data.py script
7. `build.sh`: Bash script used to streamline building, running and cleaning project
8. `build`: Directory that is used to build project

## Output Files
1. `build/DirComparator`: Executable that is created after project is compiled.
2. `build/libDirComparatorLib.so`: Shared library file that is created after project is compiled.
3. `build/common.txt`: Created after executable is run. Contains the paths of files that are identical in both directories.
4. `build/a_only.txt`: Created after executable is run. Contains the paths of files that are unique to the first directory.
5. `build/b_only.txt`: Created after executable is run. Contains the paths of files that are unique to the second directory.
6. `test_data/expected_common.txt`: Created by generate_test_data.py. Contains the paths of files that are identical in both test_data sub-directories. Used for verifying test results.
7. `test_data/expected_a_only.txt`: Created by generate_test_data.py. Contains the paths of files that are unique to the first test_data sub-directory files_a. Used for verifying test results.
8. `test_data/expected_b_only.txt`: Created by generate_test_data.py. Contains the paths of files that are unique to the first test_data sub-directory files_b. Used for verifying test results.

