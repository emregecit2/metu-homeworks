#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 9 : Default constructor; various inserts; various removes; print.
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

    std::cout << "-> Making some removals from the tree and printing it after each removal." << std::endl;

    std::cout << "-> remove(110) ..." << std::endl;

    tree.remove(110);
    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    std::cout << "-> removeAllNodes ..." << std::endl;

    tree.removeAllNodes();
    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
