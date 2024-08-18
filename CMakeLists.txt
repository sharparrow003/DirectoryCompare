cmake_minimum_required(VERSION 3.10)
project(DirComparator VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

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