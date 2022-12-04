#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 13 : Default constructor; various inserts; assignment operator; print.
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

    std::cout << "-> Creating a duplicate tree with assignment operator." << std::endl;

    BST<int> duplicatedTree;
    duplicatedTree = tree;

    std::cout << "-> Printing the duplicate tree." << std::endl;

    duplicatedTree.print(inorder);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);

    std::cout << "-> Removing a node from the original tree." << std::endl;

    tree.remove(110);

    std::cout << "-> Printing the duplicate tree." << std::endl;

    duplicatedTree.print(inorder);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);

    return 0;
}
