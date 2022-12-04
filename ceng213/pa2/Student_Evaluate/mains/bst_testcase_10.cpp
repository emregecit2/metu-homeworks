#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 10 : Default constructor; various inserts; various removes; various inserts again; print.
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

    std::cout << "-> Making some removals from the tree." << std::endl;

    tree.remove(105);
    tree.remove(114);
    tree.remove(110);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);

    std::cout << "-> Making some more insertions to the list." << std::endl;

    tree.insert(104);
    tree.insert(116);
    tree.insert(109);
    tree.insert(111);

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
