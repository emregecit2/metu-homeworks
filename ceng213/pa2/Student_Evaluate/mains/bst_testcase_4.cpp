#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 4 : Default constructor; insert on empty binary search tree; print.
 */
int main() {

    std::cout << "-> Creating a binary search tree with default constructor." << std::endl;

    BST<int> tree;

    std::cout << "-> Inserting a node with data 104 to the tree." << std::endl;

    tree.insert(104);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
