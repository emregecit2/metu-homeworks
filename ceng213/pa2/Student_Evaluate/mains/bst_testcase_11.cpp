#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 11 : Default constructor; various inserts; various searchs; print.
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

    for (int i = 104 ; i <= 116 ; ++i) {
        std::cout << "-> Searching node with data " << i << "." << std::endl;
        BSTNode<int> *temp = tree.search(i);
        if (temp == NULL) {
            std::cout << "no node with data " << i << " exists." << std::endl;
        } else {
            std::cout << "exists. data must be " << i << ". it is " << temp->data << "." <<std::endl;
        }
    }

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
