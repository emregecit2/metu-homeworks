#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 7 : Default constructor; various inserts; remove nodes with single child; print.
 */
int main() {

    std::cout << "-> Creating a binary search tree with default constructor." << std::endl;

    BST<int> tree;

    std::cout << "-> Making some insertions to the tree." << std::endl;

    tree.insert(110);
    tree.insert(115);
    tree.insert(105);
    tree.insert(113);
    tree.insert(107);
    tree.insert(114);
    tree.insert(106);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);

    std::cout << "-> Removing the node with data 105, a node with one child in this testcase, from the tree." << std::endl;

    tree.remove(105);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    std::cout << "-> Removing the node with data 115, a node with one child in this testcase, from the tree." << std::endl;

    tree.remove(115);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
