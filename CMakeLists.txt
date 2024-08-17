cmake_minimum_required(VERSION 3.10)

# Project name and version
project(DirComparator VERSION 1.0)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add executable target
add_executable(DirComparator
    main.cpp
    DirectoryComparator.cpp
    HashingUtility.cpp
)

# Include directories
target_include_directories(DirComparator PRIVATE
    ${CMAKE_SOURCE_DIR}
)

# Find and link any necessary libraries (for example, OpenSSL for hashing)
find_package(OpenSSL REQUIRED)
target_link_libraries(DirComparator PRIVATE OpenSSL::SSL)

# Optionally, add custom compiler flags
if(MSVC)
    target_compile_options(DirComparator PRIVATE /W4 /WX)
else()
    target_compile_options(DirComparator PRIVATE -Wall -Wextra -Wpedantic -Werror)
endif()

# Install the executable (optional)
install(TARGETS DirComparator DESTINATION bin)