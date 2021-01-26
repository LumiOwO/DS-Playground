cmake_minimum_required(VERSION 3.5)

project(DS-Playground)

set(CMAKE_CXX_STANDARD 11)

# Tree
add_library(tree INTERFACE)
target_include_directories(tree
    INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)

# Google Test
add_subdirectory(thirdparty/googletest)

# Enable CTest testing
enable_testing()

# Testing executables
add_executable(test_BinTree
    test/test_BinTree.cpp
)
target_link_libraries(test_BinTree
    PRIVATE
    tree
    gtest 
    gtest_main
)
add_test(Test_BinTree Test_BinTree)

add_executable(test_RBTree
    test/test_RBTree.cpp
)
target_link_libraries(test_RBTree
    PRIVATE
    tree
    gtest
    gtest_main
)
add_test(test_RBTree test_RBTree)