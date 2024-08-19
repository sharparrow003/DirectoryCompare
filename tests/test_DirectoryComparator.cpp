#include <gtest/gtest.h>
#include "DirectoryComparator.h"
#include "HashingUtility.h"
#include <filesystem>
#include <fstream>

using namespace std;

// Helper function to create a test file with specific content
void create_test_file(const string& path, const string& content) {
    ofstream file(path);
    file << content;
    file.close();
}

// Test Suite for DirectoryComparator
class DirectoryComparatorTest : public ::testing::Test {
protected:
    string test_dir_a = "unit_test_data/files_a";
    string test_dir_b = "unit_test_data/files_b";

    void SetUp() override {
        filesystem::create_directories(test_dir_a);
        filesystem::create_directories(test_dir_b);
    }

    void TearDown() override {
        filesystem::remove_all(test_dir_a);
        filesystem::remove_all(test_dir_b);
    }
};

// Test case for identical files in both directories
TEST_F(DirectoryComparatorTest, IdenticalFiles) {
    create_test_file(test_dir_a + "/file1.txt", "This is a test file.");
    create_test_file(test_dir_b + "/file1.txt", "This is a test file.");

    DirectoryComparator comparator(test_dir_a, test_dir_b);
    comparator.compare();

    // Assert the common file is identified correctly
    ASSERT_EQ(comparator.getCommonFiles().size(), 1);
    ASSERT_EQ(comparator.getAOnlyFiles().size(), 0);
    ASSERT_EQ(comparator.getBOnlyFiles().size(), 0);
}

// Test case for unique files in each directory
TEST_F(DirectoryComparatorTest, UniqueFiles) {
    create_test_file(test_dir_a + "/file1.txt", "Unique to dir_a");
    create_test_file(test_dir_b + "/file1.txt", "Unique to dir_b");

    DirectoryComparator comparator(test_dir_a, test_dir_b);
    comparator.compare();

    // Assert that there are no common files
    ASSERT_EQ(comparator.getCommonFiles().size(), 0);
    ASSERT_EQ(comparator.getAOnlyFiles().size(), 1);
    ASSERT_EQ(comparator.getBOnlyFiles().size(), 1);
}

// Test case for subdirectories having identical files
TEST_F(DirectoryComparatorTest, SubdirectoryCommonFiles) {
    filesystem::create_directories(test_dir_a + "/subdir");
    filesystem::create_directories(test_dir_b + "/subdir");

    create_test_file(test_dir_a + "/subdir/file1.txt", "This is a test file in subdir.");
    create_test_file(test_dir_b + "/subdir/file1.txt", "This is a test file in subdir.");

    DirectoryComparator comparator(test_dir_a, test_dir_b);
    comparator.compare();

    // Assert the common file in subdirectories is identified correctly
    ASSERT_EQ(comparator.getCommonFiles().size(), 1);
    ASSERT_EQ(comparator.getAOnlyFiles().size(), 0);
    ASSERT_EQ(comparator.getBOnlyFiles().size(), 0);
}

// Test case for subdirectories having different files
TEST_F(DirectoryComparatorTest, SubdirectoryUniqueFiles) {
    filesystem::create_directories(test_dir_a + "/subdir");
    filesystem::create_directories(test_dir_b + "/subdir");

    create_test_file(test_dir_a + "/subdir/file1.txt", "This is a test file in subdir unique to dir_a.");
    create_test_file(test_dir_b + "/subdir/file1.txt", "This is a test file in subdir unique to dir_b.");

    DirectoryComparator comparator(test_dir_a, test_dir_b);
    comparator.compare();

    // Assert the common file in subdirectories is identified correctly
    ASSERT_EQ(comparator.getCommonFiles().size(), 0);
    ASSERT_EQ(comparator.getAOnlyFiles().size(), 1);
    ASSERT_EQ(comparator.getBOnlyFiles().size(), 1);
}