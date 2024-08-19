## Requirements
**Compiler**: GCC 9.3+, Clang 10.0+, or MSVC 2019+
**CMake**: 3.10 or later
**OpenSSL**: Required for SHA-256 hashing

Originally developed on Linux Ubuntu 16.04

## Installation
### Build from Source 
1. **Clone the repository**
   
   ```
   git clone git@github.com:sharparrow003/anacondaDirCompare.git
   cd anacondaDirCompare
   ```
2. **Build the project using helper script build.sh**
   
   ```
   ./build.sh build
   ```
   
  Build files generated and added to directory build.
### Usage
**Run executable using helper script build.sh**
   
   Call build.sh by passing the two directories to be compared as arguments.
   ```
   ./build.sh run test_data/files_a/ test_data/files_b/
   ```

### Testing
**Generate test data using helper script build.sh**

   By default this command will create 100,000 files in the directories test_data/files_a and test_data/files_b.
   
   Refer to test_data/expected_common.txt, test_data/a_only.txt and test_data/b_only.txt for 

  ```
   ./build.sh create_test_data
  ```

**Run executable with sample test data using helper script build.sh**

  Call build.sh by passing the two directories to be compared as arguments.
   ```
   ./build.sh run test_data/files_a/ test_data/files_b/
   ```

### Cleaning Project
  This command will delete the build directory
  
   ```
   ./build.sh clean
   ```

This command will delete the test_data directory
  
   ```
   ./build.sh clean_test_data
   ```

This command will delete both the build and test_data directories
  
   ```
   ./build.sh clean_all
   ```

## Output Files
These files are generated in the build directory.
**common.txt**: Contains the paths of files that are identical in both directories.
**a_only.txt**: Contains the paths of files that are unique to the first directory
**b_only.txt**: Contains the paths of files that are unique to the second directory
