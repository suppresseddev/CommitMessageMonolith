cmake_minimum_required(VERSION 3.10)
project(Monolith)

# set the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the source files (list them explicitly or use a wildcard)
add_executable(${PROJECT_NAME}
    monolith.cpp
    trie.h
    trie.cpp
    # other_source.cpp
    # other_header.hpp
)

# optional: include directories if you have headers in subfolders
# include_directories(include)

# optional: link libraries if needed
# target_link_libraries(${PROJECT_NAME} PRIVATE some_library)