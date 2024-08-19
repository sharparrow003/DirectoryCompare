#include <gtest/gtest.h>
#include <filesystem>
#include "HashingUtility.h"

using namespace std;

class HashingUtilityTest : public ::testing::Test {
protected:
    string test_dir = "unit_test_data/hash_tests";

    void SetUp() override {
        filesystem::create_directories(test_dir);
    }

    void TearDown() override {
        filesystem::remove_all(test_dir);
    }

    // Helper function to create a test file with specific content
    void create_test_file(const string& path, const string& content) {
        ofstream file(path, ios::binary);
        file << content;
        file.close();
    }
};

// Test case: Hashing a small text file
TEST_F(HashingUtilityTest, SmallTextFile) {
    std::string file_path = test_dir + "/small.txt";
    create_test_file(file_path, "This is a small file.");

    string expected_hash = "f2f2e92aa531e5c03348dcfba693f3871564b3990b7529340ac486318dda4b97";  // Precomputed SHA-256 hash
    string actual_hash = HashingUtility::hashFile(file_path);

    ASSERT_EQ(actual_hash, expected_hash);
}