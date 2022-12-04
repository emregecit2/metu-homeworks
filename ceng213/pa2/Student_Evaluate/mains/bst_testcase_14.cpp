#include <iostream>

#include "BST.h"
//#include "../BST.h"

/*
 * Case 14 : Default constructor; various inserts; various getSuccessors; print.
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
    tree.print(preorder);
    tree.print(postorder);

    int values[7] = {105, 106, 107, 110, 113, 114, 115};
    for (int i = 0 ; i < 7 ; ++i) {
        std::cout << "-> Getting the successor nodes of the node with data " << values[i] << "." << std::endl;
        BSTNode<int> *inorderSuccessor = tree.getSuccessor(tree.search(values[i]), inorder);
        BSTNode<int> *preorderSuccessor = tree.getSuccessor(tree.search(values[i]), preorder);
        BSTNode<int> *postorderSuccessor = tree.getSuccessor(tree.search(values[i]), postorder);

        if (inorderSuccessor == NULL) {
            std::cout << "no inorder successor node exists." << std::endl;
        } else {
            std::cout << "inorder successor node exists. data is " << inorderSuccessor->data << "." << std::endl;
        }

        if (preorderSuccessor == NULL) {
            std::cout << "no preorder successor node exists." << std::endl;
        } else {
            std::cout << "preorder successor node exists. data is " << preorderSuccessor->data << "." << std::endl;
        }

        if (postorderSuccessor == NULL) {
            std::cout << "no postorder successor node exists." << std::endl;
        } else {
            std::cout << "postorder successor node exists. data is " << postorderSuccessor->data << "." << std::endl;
        }
    }

    std::cout << "-> Printing the tree." << std::endl;

    tree.print(inorder);
    tree.print(preorder);
    tree.print(postorder);

    return 0;
}
