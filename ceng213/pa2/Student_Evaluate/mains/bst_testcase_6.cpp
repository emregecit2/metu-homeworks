#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 6 : Default constructor; various inserts; remove node with two children; print.
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

    std::cout << "-> Removing the root node, a node with two children in this testcase, from the tree." << std::endl;

    tree.remove(tree.getRoot()->data);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
