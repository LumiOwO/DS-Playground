/**
 * @file       test_RBTree.cpp
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-01-21
 *
 * @brief    Test for red-black tree.
 *
 * *********************************************************************************
 *
 *
 * *********************************************************************************
 */

#include <fstream>
#include <sstream>
#include <string>

#include "gtest/gtest.h"
#include "tree/RBTree.h"

using Node = DS::RBTreeNode<int>;
using Tree = DS::RBTree<int>;
using Node_D = DS::RBTreeNode<int, true>;
using Tree_D = DS::RBTree<int, true>;

/**
 * @brief    Convert a red-black tree into Graphviz description text.
 *
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    tree               The tree to convert.
 *
 * @return   std::string        Graphviz description text for the tree.
 */
template <typename T, bool ALLOW_DUP>
std::string ToString(DS::RBTree<T, ALLOW_DUP> tree) {
    if (!tree) return "";

    // Current node
    std::string color = DS::IsBlack(tree) ? "black" : "red";
    std::stringstream s;
    s << "addr" << tree.get() << " [label = < <B>" << tree->_value << "</B> >"
      << ", fillcolor = \"" << color << "\""
      << ", group = addr" << tree.get() << "];";

    // Left
    s << ToString(tree->_left);
    s << "addr" << tree.get() << " -> ";
    if (tree->_left) {
        s << "addr" << tree->_left.get() << ";";
    } else {
        s << "_left" << tree.get() << " [style=invis];";
        s << "_left" << tree.get() << " [style=invis];";
    }
    // Mid
    s << "addr" << tree.get() << " -> "
      << "_mid" << tree.get() << " [style=invis];"
      << "_mid" << tree.get() << " [style=invis, group = addr" << tree.get()
      << "];";
    // Right
    s << ToString(tree->_right);
    s << "addr" << tree.get() << " -> ";
    if (tree->_right) {
        s << "addr" << tree->_right.get() << ";";
    } else {
        s << "_right" << tree.get() << " [style=invis];";
        s << "_right" << tree.get() << " [style=invis];";
    }
    return s.str();
}

/**
 * @brief    Visualization function for Red-black Tree using Graphviz.
 *
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    tree               The tree to visualize.
 * @param    filename           Filename of generated image.
 *
 */
template <typename T, bool ALLOW_DUP>
void Graphviz(DS::RBTree<T, ALLOW_DUP> tree, std::string filename) {
    // Config
    std::string txtName("_temp_graphviz");
    std::ofstream out(txtName);
    out << "digraph " << filename << "{"
        << "fontname = \"Consolas\";"
        << "fontsize = 16;"
        << "node[style = \"filled\", shape = circle, fontcolor = \"white\""
           "fontname = \"Consolas\", fontsize = 30, fixedsize = true, width = "
           "1.0];"
        << "edge[fontname = \"Verdana\", fontsize = 10, arrowhead = \"none\", "
           "color = \"black\", style = \"solid\"];";
    // Main body
    out << ToString(tree) << "}";
    out.close();

    // Generate image
    std::string cmd = "dot -Tpng " + txtName + " -o " + filename + ".png";
    system(cmd.data());
}

/**
 * @brief    Test cases for rotation
 *
 */
class RotateTest : public ::testing::Test {
protected:
    Tree _n2;
    Tree _n1;
    Tree _n4;
    Tree _n3;
    Tree _n5;

    void SetUp() override {
        /**
         * Test case for rotation
         *
         *        (2)
         *       /   \
         *      /     \
         *    (1)     (4)
         *           /   \
         *          /     \
         *        (3)     (5)
         *
         */
        _n2 = std::make_shared<Node>(DS::BLACK, 2);
        _n1 = std::make_shared<Node>(DS::BLACK, 1);
        _n4 = std::make_shared<Node>(DS::BLACK, 4);
        _n3 = std::make_shared<Node>(DS::BLACK, 3);
        _n5 = std::make_shared<Node>(DS::BLACK, 5);
        _n2->_left   = _n1;
        _n2->_right  = _n4;
        _n1->_parent = _n2;
        _n4->_parent = _n2;
        _n4->_left   = _n3;
        _n4->_right  = _n5;
        _n3->_parent = _n4;
        _n5->_parent = _n4;
    }

    // void TearDown() override;
};

TEST_F(RotateTest, left) {
    Tree tree = _n2;
    Graphviz(tree, "rotate");

    DS::LeftRotate(tree);
    Graphviz(tree, "rotate_left");
}

TEST_F(RotateTest, right) {
    Tree tree = _n2;

    DS::RightRotate(tree);
    Graphviz(tree, "rotate_right");
}

/**
 * @brief    Test cases for insert.
 *
 */
class InsertTest : public ::testing::Test {
protected:
    Tree _n11, _n2, _n14, _n1, _n7, _n15, _n8;

    void SetUp() override {
        /**
         * Test case:
         *         (B11)
         *        /     \
         *       /       \
         *      /         \
         *    (R2)       (B14)
         *    /  \          \
         *   /    \          \
         * (B1)  (B7)       (R15)
         *          \
         *           \
         *          (R8)
         * 
         */
        _n11 = std::make_shared<Node>(DS::BLACK, 11);
        _n2  = std::make_shared<Node>(DS::RED, 2);
        _n14 = std::make_shared<Node>(DS::BLACK, 14);
        _n1  = std::make_shared<Node>(DS::BLACK, 1);
        _n7  = std::make_shared<Node>(DS::BLACK, 7);
        _n15 = std::make_shared<Node>(DS::RED, 15);
        _n8  = std::make_shared<Node>(DS::RED, 8);
        _n11->_left   = _n2;
        _n11->_right  = _n14;
        _n2->_parent  = _n11;
        _n2->_left    = _n1;
        _n2->_right   = _n7;
        _n14->_parent = _n11;
        _n14->_right  = _n15;
        _n1->_parent  = _n2;
        _n7->_parent  = _n2;
        _n7->_right   = _n8;
        _n15->_parent = _n14;
        _n8->_parent  = _n7;

    }
    // void TearDown() override;
};

TEST_F(InsertTest, ppt) {
    Tree root = _n11;
    ASSERT_TRUE(root != nullptr);
    Graphviz(root, "insert");

    ASSERT_TRUE(DS::Insert(root, 5));
    Graphviz(root, "insert_5");

    ASSERT_TRUE(DS::Insert(root, 4));
    Graphviz(root, "insert_5_4");
}

TEST_F(InsertTest, left) {
    Tree root = nullptr;
    Graphviz(root, "insert_left");

    ASSERT_TRUE(DS::Insert(root, 15));
    Graphviz(root, "insert_left_15");
    ASSERT_TRUE(DS::Insert(root, 14));
    Graphviz(root, "insert_left_15_14");
    ASSERT_TRUE(DS::Insert(root, 13));
    Graphviz(root, "insert_left_15_14_13");
    ASSERT_TRUE(DS::Insert(root, 12));
    Graphviz(root, "insert_left_15_14_13_12");
    ASSERT_TRUE(DS::Insert(root, 11));
    Graphviz(root, "insert_left_15_14_13_12_11");
}

TEST_F(InsertTest, right) {
    Tree root = nullptr;
    Graphviz(root, "insert_right");

    ASSERT_TRUE(DS::Insert(root, 15));
    Graphviz(root, "insert_right_15");
    ASSERT_TRUE(DS::Insert(root, 16));
    Graphviz(root, "insert_right_15_16");
    ASSERT_TRUE(DS::Insert(root, 17));
    Graphviz(root, "insert_right_15_16_17");
    ASSERT_TRUE(DS::Insert(root, 18));
    Graphviz(root, "insert_right_15_16_17_18");
    ASSERT_TRUE(DS::Insert(root, 19));
    Graphviz(root, "insert_right_15_16_17_18_19");
}

TEST_F(InsertTest, dup) {
    Tree root = nullptr;

    ASSERT_TRUE(DS::Insert(root, 3));
    ASSERT_TRUE(DS::Insert(root, 2));

    ASSERT_FALSE(DS::Insert(root, 3));
    ASSERT_FALSE(DS::Insert(root, 2));
}

/**
 * @brief    Test cases for remove.
 *
 */
class RemoveTest : public ::testing::Test {
protected:
    Tree _n10, _n5, _n15, _n3, _n7, _n11, _n17, _n6, _n8;
    void SetUp() override {
        /**
         * Test case:
         *          (B10)
         *         /     \
         *        /       \
         *       /         \
         *     (B5)        (B15)
         *     /  \        /   \
         *    /    \      /     \
         *  (B3)  (R7)  (B11)  (B17)
         *        /  \
         *       /    \
         *     (B6)  (B8)
         * 
         */
        _n10 = std::make_shared<Node>(DS::BLACK, 10);
        _n5  = std::make_shared<Node>(DS::BLACK, 5);
        _n15 = std::make_shared<Node>(DS::BLACK, 15);
        _n3  = std::make_shared<Node>(DS::BLACK, 3);
        _n7  = std::make_shared<Node>(DS::RED  , 7);
        _n11 = std::make_shared<Node>(DS::BLACK, 11);
        _n17 = std::make_shared<Node>(DS::BLACK, 17);
        _n6  = std::make_shared<Node>(DS::BLACK, 6);
        _n8  = std::make_shared<Node>(DS::BLACK, 8);
        _n10->_left   = _n5;
        _n10->_right  = _n15;
        _n5->_parent  = _n10;
        _n5->_left    = _n3;
        _n5->_right   = _n7;
        _n15->_parent = _n10;
        _n15->_left   = _n11;
        _n15->_right  = _n17;
        _n3->_parent  = _n5;
        _n7->_parent  = _n5;
        _n7->_left    = _n6;
        _n7->_right   = _n8;
        _n11->_parent = _n15;
        _n17->_parent = _n15;
        _n6->_parent  = _n7;
        _n8->_parent  = _n7;
    }
    // void TearDown() override;
};

TEST_F(RemoveTest, ppt) {
    Tree root = _n10;
    ASSERT_TRUE(root != nullptr);
    Graphviz(root, "remove");

    ASSERT_TRUE(DS::Remove(root, 14) == nullptr);

    ASSERT_TRUE(DS::Remove(root, 3) != nullptr);
    Graphviz(root, "remove_1");

    ASSERT_TRUE(DS::Remove(root, 17) != nullptr);
    Graphviz(root, "remove_2");

    ASSERT_TRUE(DS::Remove(root, 8) != nullptr);
    Graphviz(root, "remove_3");

    ASSERT_TRUE(DS::Remove(root, 10) != nullptr);
    Graphviz(root, "remove_4");

    ASSERT_TRUE(DS::Remove(root, 6) != nullptr);
    Graphviz(root, "remove_5");

    ASSERT_TRUE(DS::Remove(root, 15) != nullptr);
    Graphviz(root, "remove_6");

    ASSERT_TRUE(DS::Remove(root, 7) != nullptr);
    Graphviz(root, "remove_7");

    ASSERT_TRUE(DS::Remove(root, 11) != nullptr);
    Graphviz(root, "remove_8");

    ASSERT_TRUE(DS::Remove(root, 5) != nullptr);
    Graphviz(root, "remove_9");

    ASSERT_TRUE(DS::Remove(root, 8) == nullptr);
}