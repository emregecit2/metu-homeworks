#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 8 : Default constructor; various inserts; remove nodes with no child; print.
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

    std::cout << "-> Removing the node with data 106, a node with no child in this testcase, from the tree." << std::endl;

    tree.remove(106);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    std::cout << "-> Removing the node with data 114, a node with no child in this testcase, from the tree." << std::endl;

    tree.remove(114);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
