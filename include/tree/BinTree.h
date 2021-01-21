/**
 * @file       binTree.h
 * @author     Lumi (LumiOwO@hotmail.com)
 * @date       2021-01-11
 * 
 * @brief    Base class for binary tree.
 * 
 * *********************************************************************************
 * 
 * 
 * *********************************************************************************
 */

#include <memory>
#include <vector>
#include <queue>

namespace DS {

template <typename T>
class BinTreeNode {
/**
 * @brief    Node for binary tree.
 * 
 */
public:
    /// The value of node. 
    T _value;
    /// Smart pointer for left subTree
    std::shared_ptr<BinTreeNode> _left;
    /// Smart pointer for right subTree
    std::shared_ptr<BinTreeNode> _right;

    /// Constructors
    BinTreeNode() : _value(0), _left(nullptr), _right(nullptr) { }
    BinTreeNode(T value) : _value(value), _left(nullptr), _right(nullptr) { }
    BinTreeNode(T value, std::shared_ptr<BinTreeNode> left, std::shared_ptr<BinTreeNode> right) :
        _value(value), _left(left), _right(right) { }

    /// Destructors
    virtual ~BinTreeNode() { }

    /**
     * @brief    Visit the value of node.
     * It's an empty function in this base class.
     * You can override and add more functions to it in your subclass.
     * 
     * @return   T      The value of node.
     * 
     */
    virtual T Visit() { return _value; }

    /**
     * @brief    Pre-Order Traversal.
     * 
     * @param    out         Pointer to an std::vector. Default nullptr.
     * 
     */
    virtual void PreOrder(std::vector<T> *out = nullptr) {
        T t = Visit();
        if(out) out->push_back(t);

        if(_left) _left->PreOrder(out);
        if(_right) _right->PreOrder(out);
    }

    /**
     * @brief    In-Order Traversal.
     * 
     * @param    out         Pointer to an std::vector. Default nullptr.
     * 
     */
    virtual void InOrder(std::vector<T> *out = nullptr) {
        if(_left) _left->InOrder(out);

        T t = Visit();
        if(out) out->push_back(t);

        if(_right) _right->InOrder(out);
    }

    /**
     * @brief    Post-Order Traversal.
     * 
     * @param    out         Pointer to an std::vector. Default nullptr.
     * 
     */
    virtual void PostOrder(std::vector<T> *out = nullptr) {
        if(_left) _left->PostOrder(out);
        if(_right) _right->PostOrder(out);

        T t = Visit();
        if(out) out->push_back(t);
    }

    /**
     * @brief    Level-Order Traversal.
     * 
     * @param    out         Pointer to an std::vector. Default nullptr.
     * 
     */
    virtual void LevelOrder(std::vector<T> *out = nullptr) {
        std::queue<BinTreeNode*> q;
        q.push(this);
        while(!q.empty()) {
            BinTreeNode* cur = q.front();
            q.pop();

            T t = cur->Visit(); 
            if(out) out->push_back(t);

            if(cur->_left) q.push(cur->_left.get());
            if(cur->_right) q.push(cur->_right.get());
        }
    }
}; ///< class BinTreeNode


/// typedef the smart pointer to node as BinTree
template <typename T>
using BinTree = std::shared_ptr< BinTreeNode<T> >;


}; ///< namespace DS