cmake_minimum_required(VERSION 3.10)
project(DirComparator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(UNIT_TESTS "Unit Tests" OFF)

# Define the library
add_library(DirComparatorLib SHARED
    src/DirectoryComparator.cpp
)

target_include_directories(DirComparatorLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Define the executable
add_executable(DirComparator
    src/main.cpp
)

# Find and link any necessary libraries (for example, OpenSSL for hashing)
find_package(OpenSSL REQUIRED)
target_link_libraries(DirComparator PRIVATE OpenSSL::SSL)

target_link_libraries(DirComparator PRIVATE DirComparatorLib)

# Install rules for making the project consumable
install(TARGETS DirComparatorLib DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

if (UNIT_TESTS)
    # Find the GTest package
    find_package(GTest REQUIRED)

    # Add the unit test executable
    add_executable(testDirComparator
        tests/test_DirectoryComparator.cpp
    )
    # Add the unit test executable
    add_executable(testHashingUtility
        tests/test_HashingUtility.cpp
    )

    # Link the test executable against the shared library and GTest
    target_link_libraries(testDirComparator PRIVATE DirComparatorLib GTest::GTest GTest::Main OpenSSL::SSL)
    target_link_libraries(testHashingUtility PRIVATE DirComparatorLib GTest::GTest GTest::Main OpenSSL::SSL)

    # Enable testing using CTest
    enable_testing()

    # Add the test
    add_test(NAME DirectoryComparatorTest COMMAND testDirComparator)
    add_test(NAME HashingUtilityTest COMMAND testHashingUtility)
endif (UNIT_TESTS)
