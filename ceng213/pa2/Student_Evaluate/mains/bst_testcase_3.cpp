#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 3 : Default constructor; various functions on empty binary search tree; print.
 */
int main() {

    std::cout << "-> Creating a binary search tree with default constructor." << std::endl;

    BST<int> tree;

    std::cout << "-> Creating a node with data 103. Node is not in the tree." << std::endl;

    BSTNode<int> *tempNode = new BSTNode<int>(103, NULL, NULL);

    std::cout << "-> Trying to remove a node with data 103 from the tree and then printing the tree." << std::endl;

    tree.remove(103);
    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    std::cout << "-> Trying to search a node with data 103 in the tree and then printing the tree." << std::endl;

    if (tree.search(103) == NULL) {
        std::cout << "no node with data 103 exists" << std::endl;
    }
    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    std::cout << "-> Checking if the tree contains the previously created node or not and then printing the tree." << std::endl;
    if (tree.contains(tempNode) == false) {
        std::cout << "tree does not contain that node" << std::endl;
    }
    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    delete tempNode;

    return 0;
}
