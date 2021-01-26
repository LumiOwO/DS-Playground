/**
 * @file       RBTree.h
 * @author     Lumi (lumiowo@hotmail.com)
 * @date       2021-01-21
 * 
 * @brief    Red-black Tree.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include <memory>
#include <cassert>

namespace DS {

/// Enumeration for node color.
enum RBColor { BLACK, RED };

/**
 * @brief    Node for red-black tree.
 * 
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 * 
 */
template <typename T, bool ALLOW_DUP = false>
class RBTreeNode {
public:
    /// typedef the smart pointer
    using RBTree = std::shared_ptr<RBTreeNode<T, ALLOW_DUP>>;
    
    /// Color of node
    RBColor _color;
    /// Value of node
    T _value;
    /// Smart pointer to parent.
    /// Use weak_ptr in case of circular reference
    std::weak_ptr<RBTreeNode<T, ALLOW_DUP>> _parent;
    /// Smart pointer to left subTree
    RBTree _left;
    /// Smart pointer to right subTree
    RBTree _right;

    /// Constructors
    RBTreeNode()
        : _color(BLACK),
          _value(0),
          _parent(std::weak_ptr<RBTreeNode<T, ALLOW_DUP>>()),
          _left(nullptr),
          _right(nullptr) {}
    RBTreeNode(RBColor color, T value)
        : _color(color),
          _value(value),
          _parent(std::weak_ptr<RBTreeNode<T, ALLOW_DUP>>()),
          _left(nullptr),
          _right(nullptr) {}
    RBTreeNode(RBColor color, T value, RBTree parent, RBTree left, RBTree right)
        : _color(color),
          _value(value),
          _parent(parent),
          _left(left),
          _right(right) {}

    /// Destructors
    virtual ~RBTreeNode() { }

    /// Utilities
    bool IsRoot() const { return !_parent.lock(); }
    bool IsLeaf() const { return !_left && !_right; }

}; ///< class RBTreeNode

/// typedef the smart pointer
template <typename T, bool ALLOW_DUP = false>
using RBTree = std::shared_ptr<RBTreeNode<T, ALLOW_DUP>>;

/// Utilities
template <typename T, bool ALLOW_DUP>
inline bool IsBlack(RBTree<T, ALLOW_DUP> p) {
    return !p || p->_color == RBColor::BLACK;
}
template <typename T, bool ALLOW_DUP>
inline bool IsRed(RBTree<T, ALLOW_DUP> p) {
    return !IsBlack(p);
}

// ========================== Declarations ==========================

/**
 * @brief    Search for the value in a red-black tree.
 *
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    root               Const reference of the root pointer.
 * @param    value              The value to be searched.
 *
 * @return   RBTree     Pointer to the first node that contains the value.
 */
template <typename T, bool ALLOW_DUP>
RBTree<T, ALLOW_DUP> Search(const RBTree<T, ALLOW_DUP> &root, T value);

/**
 * @brief    Left-Rotate for current red-black tree node.
 *
 * Assume the value of current node is 2.
 *
 *        (2)<- self                     that ->(4)
 *       /   \                                 /  \
 *      /     \                               /    \
 *    (1)     (4)<- that      ==>    self ->(2)    (5)
 *           /   \                         /  \
 *          /     \                       /    \
 *        (3)     (5)                   (1)    (3)
 *
 *
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    top                Reference of the top node pointer.
 *
 */
template <typename T, bool ALLOW_DUP>
void LeftRotate(RBTree<T, ALLOW_DUP> &top);

/**
 * @brief    Right-Rotate for current node.
 *
 * Assume the value of current node is 4.
 *
 *        self ->(4)                    (2)<- that
 *              /  \                   /   \
 *             /    \                 /     \
 *    that ->(2)    (5)     ==>     (1)     (4)<- self
 *          /  \                           /   \
 *         /    \                         /     \
 *       (1)    (3)                     (3)     (5)
 * 
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    top                Reference of the top node pointer.
 *
 */
template <typename T, bool ALLOW_DUP>
void RightRotate(RBTree<T, ALLOW_DUP> &top);

/**
 * @brief    Insert the value into a red-black tree.
 *
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    root               Reference of the root pointer.
 * @param    value              The value to insert.
 *
 * @return   true               Success to insert.
 * @return   false              Fail to insert.
 */
template <typename T, bool ALLOW_DUP>
bool Insert(RBTree<T, ALLOW_DUP> &root, T value);

/**
 * @brief    Remove the value from a red-black tree.
 *
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    root               Reference of the root pointer.
 * @param    value              The value to remove.
 *
 * @return   RBTree             The pointer to the removed node.
 */
template <typename T, bool ALLOW_DUP>
RBTree<T, ALLOW_DUP> Remove(RBTree<T, ALLOW_DUP> &root, T value);

/**
 * @brief   Adjust the red-black tree during insert operation.
 *
 * Cases for insert can be found on
 * https://lumiowo.gitee.io/2021/01/22/%E7%BA%A2%E9%BB%91%E6%A0%91%E7%9A%84%E5%8E%9F%E7%90%86%E5%92%8C%E7%AE%97%E6%B3%95%E5%88%86%E6%9E%90/
 *
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    cur                Reference of current node pointer.
 * @param    root               Reference of the root pointer.
 *
 */
template <typename T, bool ALLOW_DUP>
void __Insert_Adjust(RBTree<T, ALLOW_DUP> &cur, RBTree<T, ALLOW_DUP> &root);

/**
 * @brief    Adjust the red-black tree during remove operation.
 *
 * @tparam   T                  Typename
 * @tparam   ALLOW_DUP          Whether to allow duplicate nodes.
 *
 * @param    cur                Const reference of current node pointer.
 * @param    root               Reference of the root pointer.
 *
 */
template <typename T, bool ALLOW_DUP>
void __Remove_Adjust(const RBTree<T, ALLOW_DUP> &cur,
                     RBTree<T, ALLOW_DUP> &root);

// ========================== Definitions ==========================

template <typename T, bool ALLOW_DUP>
RBTree<T, ALLOW_DUP> Search(const RBTree<T, ALLOW_DUP> &root, T value) {
    RBTree<T, ALLOW_DUP> cur = root;
    while (cur) {
        if (value == cur->_value) {
            break;
        } else if (value < cur->_value) {
            cur = cur->_left;
        } else {
            cur = cur->_right;
        }
    }
    return cur;
}

template <typename T, bool ALLOW_DUP>
void LeftRotate(RBTree<T, ALLOW_DUP> &top) {
    assert(top && top->_right);
    RBTree<T, ALLOW_DUP> self = top;
    RBTree<T, ALLOW_DUP> that = top->_right;
    RBTree<T, ALLOW_DUP> parent =
        top->_parent.lock();  ///< _parent is a weak_ptr

    // Rotate key nodes
    self->_parent = that;
    self->_right = that->_left;
    that->_left = self;
    that->_parent = parent;
    // Adjust subtrees
    if (self->_right) {
        self->_right->_parent = self;
    }
    // Adjust parent
    if (parent) {
        if (parent->_left == self) {
            parent->_left = that;
        } else {
            parent->_right = that;
        }
    }
    // Modify the pointer to top node
    top = that;
}

template <typename T, bool ALLOW_DUP>
void RightRotate(RBTree<T, ALLOW_DUP> &top) {
    assert(top && top->_left);
    RBTree<T, ALLOW_DUP> self = top;
    RBTree<T, ALLOW_DUP> that = top->_left;
    RBTree<T, ALLOW_DUP> parent =
        top->_parent.lock();  ///< _parent is a weak_ptr

    // Rotate key nodes
    self->_left = that->_right;
    self->_parent = that;
    that->_right = self;
    that->_parent = parent;
    // Adjust subtrees
    if (self->_left) {
        self->_left->_parent = self;
    }
    // Adjust parent
    if (parent) {
        if (parent->_left == self) {
            parent->_left = that;
        } else {
            parent->_right = that;
        }
    }
    // Modify the pointer to top node
    top = that;
}

template <typename T, bool ALLOW_DUP>
bool Insert(RBTree<T, ALLOW_DUP> &root, T value) {
    if(!root) {
        root = std::make_shared<RBTreeNode<T, ALLOW_DUP>>(BLACK, value);
        return true;
    }

    assert(root->IsRoot());
    // Find the node to insert
    RBTree<T, ALLOW_DUP> parent = nullptr;
    RBTree<T, ALLOW_DUP> cur = root;
    while (cur) {
        // Equals
        if (!ALLOW_DUP && value == cur->_value) {
            return false;
        }
        parent = cur;
        if (value <= cur->_value) {
            cur = cur->_left;
        } else {
            cur = cur->_right;
        }
    }
    // Add a new node to the tree
    cur = std::make_shared<RBTreeNode<T, ALLOW_DUP>>(RED, value);
    cur->_parent = parent;
    if(value <= parent->_value) {
        parent->_left = cur;
    } else {
        parent->_right = cur;
    }
    // Adjust the tree
    __Insert_Adjust(cur, root);

    return true;
}

template <typename T, bool ALLOW_DUP>
void __Insert_Adjust(RBTree<T, ALLOW_DUP> &cur, RBTree<T, ALLOW_DUP> &root) {
    assert(cur->_color == RED);

    RBTree<T, ALLOW_DUP> parent = cur->_parent.lock();
    // No parent: cur == root
    if (!parent) {
        assert(cur == root);
        cur->_color = BLACK;
        return;
    }
    // Case 1: parent is black
    if (parent->_color == BLACK) {
        return;
    }

    RBTree<T, ALLOW_DUP> grand = parent->_parent.lock();
    // No grandparent: parent == root
    // This case must have been done in Case 1
    assert(grand != nullptr);

    // Left
    if (parent == grand->_left) {
        RBTree<T, ALLOW_DUP> uncle = grand->_right;
        // Case 2: uncle is red
        if (IsRed(uncle)) {
            parent->_color = uncle->_color = BLACK;
            grand->_color = RED;
            __Insert_Adjust(grand, root);
        }
        // Case 3: uncle is black
        else {
            // Case 3.1: current is the right subtree of parent
            // Convert Case 3.1 to Case 3.2
            if(cur == parent->_right) {
                LeftRotate(parent);
                cur = parent->_left;
            }
            // Case 3.2: current is the left subtree of parent
            parent->_color = BLACK;
            grand->_color = RED;
            // Note that root may be changed after rotation
            bool change = (grand == root);
            RightRotate(grand);
            if (change) {
                root = grand;
            }
        }
    }
    // Right, symmetric
    else {
        RBTree<T, ALLOW_DUP> uncle = grand->_left;
        // Case 2: uncle is red
        if (IsRed(uncle)) {
            parent->_color = uncle->_color = BLACK;
            grand->_color = RED;
            __Insert_Adjust(grand, root);
        }
        // Case 3: uncle is black
        else {  // Symmetric!
            // Case 3.1: current is the left subtree of parent
            // Convert Case 3.1 to Case 3.2
            if (cur == parent->_left) {
                RightRotate(parent);
                cur = parent->_right;
            }
            // Case 3.2: current is the right subtree of parent
            parent->_color = BLACK;
            grand->_color = RED;
            // Note that root may be changed after rotation
            bool change = (grand == root);
            LeftRotate(grand);
            if (change) {
                root = grand;
            }
        }
    }
}

template <typename T, bool ALLOW_DUP>
RBTree<T, ALLOW_DUP> Remove(RBTree<T, ALLOW_DUP> &root, T value) {
    if (!root) {
        return nullptr;
    }
    assert(root->IsRoot());

    // Find the node that contains the value
    RBTree<T, ALLOW_DUP> cur = Search(root, value);
    if (!cur) {
        return nullptr;
    }
    // If current node has both left and right subtrees,
    // swap its value with the minimum node in right subtree
    // and remove the original value in right subtree
    if (cur->_left && cur->_right) {
        RBTree<T, ALLOW_DUP> minNode = cur->_right;
        while (minNode->_left) {
            minNode = minNode->_left;
        }
        std::swap(cur->_value, minNode->_value);
        cur = minNode;
    }

    // Adjust the tree
    if (IsBlack(cur)) {
        __Remove_Adjust(cur, root);
    }

    // Find parent
    RBTree<T, ALLOW_DUP> parent = cur->_parent.lock();
    if (!parent) {
        // Remove root node
        assert(cur == root);

        if (cur->IsLeaf()) {
            // No children
            root = nullptr;
        } else {
            // Only 1 child
            RBTree<T, ALLOW_DUP> that = cur->_left ? cur->_left : cur->_right;
            assert(that->IsLeaf());
            that->_color = BLACK;
            that->_parent = std::weak_ptr<RBTreeNode<T, ALLOW_DUP>>();
            root = that;
        }
        cur->_left = cur->_right = nullptr;
        return cur;
    }
    // Reference for parent's pointer
    RBTree<T, ALLOW_DUP> &child =
        parent->_left == cur ? parent->_left : parent->_right;
    
    // No subtrees
    if (cur->IsLeaf()) {
        child = nullptr;
    } 
    // Only one subtree
    else if (cur->_left) {
        child = cur->_left;
        cur->_left->_parent = cur->_parent;
    } else {
        child = cur->_right;
        cur->_right->_parent = cur->_parent;
    }

    cur->_parent = cur->_left = cur->_right = nullptr;
    return cur;
}

template <typename T, bool ALLOW_DUP>
void __Remove_Adjust(const RBTree<T, ALLOW_DUP> &cur,
                     RBTree<T, ALLOW_DUP> &root) {
    assert(cur->_color == BLACK);

    RBTree<T, ALLOW_DUP> parent = cur->_parent.lock();
    if (!parent) {
        assert(cur == root);
        return;
    }
    // Left
    if (cur == parent->_left) {
        RBTree<T, ALLOW_DUP> sib = parent->_right;
        // Case 1: Sibling is red
        // Convert to black sibling cases
        if (IsRed(sib)) {
            parent->_color = RED;
            sib->_color = BLACK;
            bool change = (parent == root);
            LeftRotate(parent);
            if (change) {
                root = parent;
            }
            // Update parent and sibling
            parent = cur->_parent.lock();
            sib = parent->_right;
        }
        // Since current node is black,
        // there must be a non-null sibling
        assert(sib != nullptr);
        
        // Case 3: Right cousin is black, left cousin is red
        // Convert to case 2
        if (IsBlack(sib->_right) && IsRed(sib->_left)) {
            sib->_left->_color = BLACK;
            sib->_color = RED;
            RightRotate(sib);
        }
        // Case 2: Right cousin is red
        if (IsRed(sib->_right)) {
            sib->_right->_color = BLACK;
            sib->_color = parent->_color;
            parent->_color = BLACK;
            bool change = (parent == root);
            LeftRotate(parent);
            if (change) {
                root = parent;
            }
        }
        // Case 4: Right cousin is black, left cousin is black
        else {
            assert(IsBlack(sib->_left));
            // Case 4.1: parent is red
            if (IsRed(parent)) {
                sib->_color = RED;
                parent->_color = BLACK;
            }
            // Case 4.2: parent is black
            else {
                sib->_color = RED;
                __Remove_Adjust(parent, root);
            }
        }
    } 
    // Right, symmetric
    else {
        RBTree<T, ALLOW_DUP> sib = parent->_left;
        // Case 1: Sibling is red
        // Convert to black sibling cases
        if (IsRed(sib)) {
            parent->_color = RED;
            sib->_color = BLACK;
            bool change = (parent == root);
            RightRotate(parent);
            if (change) {
                root = parent;
            }
            // Update parent and sibling
            parent = cur->_parent.lock();
            sib = parent->_left;
        }
        // Since current node is black,
        // there must be a non-null sibling
        assert(sib != nullptr);

        // ** Symmetric! **
        // Case 3: Left cousin is black, right cousin is red
        // Convert to case 2
        if (IsBlack(sib->_left) && IsRed(sib->_right)) {
            sib->_right->_color = BLACK;
            sib->_color = RED;
            LeftRotate(sib);
        }
        // Case 2: Left cousin is red
        if (IsRed(sib->_left)) {
            sib->_left->_color = BLACK;
            sib->_color = parent->_color;
            parent->_color = BLACK;
            bool change = (parent == root);
            RightRotate(parent);
            if (change) {
                root = parent;
            }
        }
        // Case 4: Left cousin is black, right cousin is black
        else {
            assert(IsBlack(sib->_right));
            // Case 4.1: parent is red
            if (IsRed(parent)) {
                sib->_color = RED;
                parent->_color = BLACK;
            }
            // Case 4.2: parent is black
            else {
                sib->_color = RED;
                __Remove_Adjust(parent, root);
            }
        }
    }
}

}; ///< namespace DS