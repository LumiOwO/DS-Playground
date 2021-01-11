cmake_minimum_required(VERSION 3.5)

project(DS-Playground)

set(CMAKE_CXX_STANDARD 11)

# Binary Tree
add_library(BinTree INTERFACE)
target_include_directories(BinTree
    INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)

# tests
add_executable(Test_BinTree
    test/test_BinTree.cpp
)
target_link_libraries(Test_BinTree
    PRIVATE
    BinTree
)