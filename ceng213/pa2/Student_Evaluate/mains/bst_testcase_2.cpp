#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 2 : Default constructor; various utility functions on empty binary search tree; print.
 */
int main() {

    std::cout << "-> Creating a binary search tree with default constructor." << std::endl;

    BST<int> tree;

    std::cout << "-> Getting the root node." << std::endl;

    if (tree.getRoot() == NULL) {
        std::cout << "no root node" << std::endl;
    }

    std::cout << "-> Checking if the tree is empty or not." << std::endl;

    if (tree.isEmpty()) {
        std::cout << "tree is empty" << std::endl;
    }

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
