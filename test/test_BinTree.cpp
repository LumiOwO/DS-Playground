/**
 * @file       test_BinTree.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-01-21
 * 
 * @brief    Test for simple binary tree.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include "tree/BinTree.h"
#include "gtest/gtest.h"

using Node = DS::BinTreeNode<int>;
using Tree = DS::BinTree<int>;

class BinTreeTest : public ::testing::Test {
protected:
    /**
     * Test case: 
     * 
     *       4
     *   2       6
     * 1   3   5   7
     *
     */
    Tree _n1, _n3, _n5, _n7, _n2, _n6, _n4;
    
    void SetUp() override {
        _n1 = std::make_shared<Node>(1);
        _n3 = std::make_shared<Node>(3);
        _n5 = std::make_shared<Node>(5);
        _n7 = std::make_shared<Node>(7);
        _n2 = std::make_shared<Node>(2, _n1, _n3);
        _n6 = std::make_shared<Node>(6, _n5, _n7);
        _n4 = std::make_shared<Node>(4, _n2, _n6);
    }

    // void TearDown() override { }
};

TEST_F(BinTreeTest, root) {
    Tree tree = _n4;

    std::vector<int> ans{4, 2, 1, 3, 6, 5, 7};
    std::vector<int> res;
    tree->PreOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {1, 2, 3, 4, 5, 6, 7};
    res = {};
    tree->InOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {1, 3, 2, 5, 7, 6, 4};
    res = {};
    tree->PostOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {4, 2, 6, 1, 3, 5, 7};
    res = {};
    tree->LevelOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }
}

TEST_F(BinTreeTest, subtree) {
    Tree tree = _n2;

    std::vector<int> ans{2, 1, 3};
    std::vector<int> res;
    tree->PreOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {1, 2, 3};
    res = {};
    tree->InOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {1, 3, 2};
    res = {};
    tree->PostOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {2, 1, 3};
    res = {};
    tree->LevelOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }
}

TEST_F(BinTreeTest, leaf) {
    Tree tree = _n1;

    std::vector<int> ans{1};
    std::vector<int> res;
    tree->PreOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {1};
    res = {};
    tree->InOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {1};
    res = {};
    tree->PostOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }

    ans = {1};
    res = {};
    tree->LevelOrder(&res);
    for(size_t i = 0; i < ans.size(); i++) {
        EXPECT_EQ(ans[i], res[i]);
    }
}


