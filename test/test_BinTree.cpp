#include "binTree/binTree.h"
#include <iostream>

template <typename T>
void PrintVector(std::vector<T> &vec) {
    for(T t : vec) {
        std::cout << t << ' ';
    }
}

template <typename T>
void PrintTree(DS::BinTree<T> tree) {
    // PreOrder
    std::vector<T> res;
    tree->PreOrder(&res);
    std::cout << "PreOrder: ";
    PrintVector(res);
    std::cout << std::endl;
    // InOrder
    res.clear();
    tree->InOrder(&res);
    std::cout << "InOrder: ";
    PrintVector(res);
    std::cout << std::endl;
    // PostOrder
    res.clear();
    tree->PostOrder(&res);
    std::cout << "PostOrder: ";
    PrintVector(res);
    std::cout << std::endl;
    // LevelOrder
    res.clear();
    tree->LevelOrder(&res);
    std::cout << "LevelOrder: ";
    PrintVector(res);
    std::cout << std::endl;
}

int main() {
    using Node = DS::BinTreeNode<int>;
    using Tree = DS::BinTree<int>;

    /**
     *       4
     *   2       6
     * 1   3   5   7
     * 
     */
    Node n1(1), n3(3), n5(5), n7(7);
    Node n2(2, &n1, &n3), n6(6, &n5, &n7);
    Node n4(4, &n2, &n6);

    std::cout << "1:\n";
    PrintTree(&n4);

    std::cout << "2:\n";
    PrintTree(&n1);

    n6._left = n6._right = nullptr;
    std::cout << "3:\n";
    PrintTree(&n4);
}