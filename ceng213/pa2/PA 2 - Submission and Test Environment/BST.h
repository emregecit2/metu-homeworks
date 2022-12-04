#ifndef BST_H
#define BST_H

#include <iostream>

#include "BSTNode.h"

enum TraversalPlan
{
    preorder,
    inorder,
    postorder
};

template <class T>
class BST
{
public: // DO NOT CHANGE THIS PART.
    BST();
    BST(const BST<T> &obj);

    ~BST();

    BSTNode<T> *getRoot() const;
    bool isEmpty() const;
    bool contains(BSTNode<T> *node) const;

    void insert(const T &data);

    void remove(const T &data);
    void removeAllNodes();

    BSTNode<T> *search(const T &data) const;
    BSTNode<T> *getSuccessor(BSTNode<T> *node, TraversalPlan tp) const;

    void print(TraversalPlan tp = inorder) const;

    BST<T> &operator=(const BST<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
    void print(BSTNode<T> *node, TraversalPlan tp) const;

    void insert(BSTNode<T> *node, const T &data)
    {
        if (data > node->data)
        {
            if (node->right)
                insert(node->right, data);
            else
                node->right = new BSTNode<T>(data, NULL, NULL);
        }
        else if (data < node->data)
        {
            if (node->left)
                insert(node->left, data);
            else
                node->left = new BSTNode<T>(data, NULL, NULL);
        }
    };

    T getMin(BSTNode<T> *node) const
    {
        while (node->left)
            node = node->left;
        return node->data;
    };

    void removeAllNodes(BSTNode<T> *node)
    {
        if (node)
        {
            removeAllNodes(node->left);
            removeAllNodes(node->right);
            delete node;
        }
    };

    BSTNode<T> *search(BSTNode<T> *node, const T &data) const
    {
        if (node)
        {
            if (node->data == data)
                return node;

            BSTNode<T> *L = search(node->left, data);
            if (L)
                return L;

            BSTNode<T> *R = search(node->right, data);
            return R;
        }
        return NULL;
    };

    void remove(BSTNode<T> *&node, T value)
    {
        if (node)
        {
            if (node->data > value)
                remove(node->left, value);
            else if (node->data < value)
                remove(node->right, value);
            else if (node->left && node->right)
            {
                node->data = getMin(node->right);
                remove(node->right, node->data);
            }
            else
            {
                BSTNode<T> *oldNode = node;
                node = node->left ? node->left : node->right;
                delete oldNode;
            }
        }
    };

    BSTNode<T> *copy(const BSTNode<T> *obj)
    {
        return obj ? new BSTNode<T>(obj->data, copy(obj->left), copy(obj->right)) : NULL;
    };

    bool contains(BSTNode<T> *root, BSTNode<T> *node) const
    {
        return root ? (root==node ? true : contains(root->left) || contains(root->right)) : false;
    }
    
    int getSize(BSTNode<T> *node) const{
        return node ? getSize(node->left) + getSize(node->right) + 1 : 0;
    }
    
    void inorderTraversal(BSTNode<T> *node, BSTNode<T> **&array, int &counter) const
    {
        if(node){
            inorderTraversal(node->left, array, counter);
            array[counter] = node;
            counter++;
            inorderTraversal(node->right, array, counter);
        }
    }
    
    void preorderTraversal(BSTNode<T> *node, BSTNode<T> **&array, int &counter) const
    {
        if(node){
            array[counter] = node;
            counter++;
            preorderTraversal(node->left, array, counter);
            preorderTraversal(node->right, array, counter);
        }
    }
    
    void postorderTraversal(BSTNode<T> *node, BSTNode<T> **&array, int &counter) const
    {
        if(node){
            postorderTraversal(node->left, array, counter);
            postorderTraversal(node->right, array, counter);
            array[counter] = node;
            counter++;
        }
    }
    
private: // DO NOT CHANGE THIS PART.
    BSTNode<T> *root;
};

#endif // BST_H

template <class T>
BST<T>::BST()
{
    root = NULL;
}

template <class T>
BST<T>::BST(const BST<T> &obj)
{
    root = copy(obj.root);
}

template <class T>
BST<T>::~BST()
{
    removeAllNodes(root);
}

template <class T>
BSTNode<T> *BST<T>::getRoot() const
{
    return root;
}

template <class T>
bool BST<T>::isEmpty() const
{
    return !root;
}

template <class T>
bool BST<T>::contains(BSTNode<T> *node) const
{
    return contains(root, node);
}

template <class T>
void BST<T>::insert(const T &data)
{
    if (root)
        insert(root, data);
    else
        root = new BSTNode<T>(data, NULL, NULL);
}

template <class T>
void BST<T>::remove(const T &data)
{
    remove(root, data);
}

template <class T>
void BST<T>::removeAllNodes()
{
    removeAllNodes(root);
    root = NULL;
}

template <class T>
BSTNode<T> *BST<T>::search(const T &data) const
{
    return search(root, data);
}

template <class T>
BSTNode<T> *BST<T>::getSuccessor(BSTNode<T> *node, TraversalPlan tp) const
{
    int size = getSize(root), i = 0, x = 0;
    BSTNode<T> **array = new BSTNode<T>*[size+1];
    array[size] = NULL;
    
    switch(tp){
        case inorder:
            inorderTraversal(root, array, x);
            break;
        case preorder:
            preorderTraversal(root, array, x);
            break;
        case postorder:
            postorderTraversal(root, array, x);
            break;
    }
    
    for(; i<size; i++){
        if(array[i]==node){
            break;
        }
    }
    BSTNode<T>* successor = array[i+1];
    delete[] array;
    return successor;
}

template <class T>
void BST<T>::print(TraversalPlan tp) const
{

    if (tp == inorder)
    {
        if (isEmpty())
        {
            std::cout << "BST_inorder{}" << std::endl;
            return;
        }
        std::cout << "BST_inorder{" << std::endl;

        print(root, inorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
    else if (tp == preorder)
    {
        if (isEmpty())
        {
            std::cout << "BST_preorder{}" << std::endl;
            return;
        }
        std::cout << "BST_preorder{" << std::endl;
        print(root, preorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
    else if (tp == postorder)
    {
        if (isEmpty())
        {
            std::cout << "BST_postorder{}" << std::endl;
            return;
        }
        std::cout << "BST_postorder{" << std::endl;
        print(root, postorder);
        std::cout << std::endl
                  << "}" << std::endl;
    }
}

template <class T>
BST<T> &BST<T>::operator=(const BST<T> &rhs)
{
    removeAllNodes();
    root = copy(rhs.root);
}

template <class T>
void BST<T>::print(BSTNode<T> *node, TraversalPlan tp) const
{

    // check if the node is NULL?
    if (node == NULL)
        return;

    if (tp == inorder)
    {
        // first, output left subtree and comma (if needed).
        print(node->left, inorder);
        if (node->left)
        {
            std::cout << "," << std::endl;
        }

        // then, output the node.
        std::cout << "\t" << node->data;

        // finally, output comma (if needed) and the right subtree.
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, inorder);
    }
    else if (tp == preorder)
    {
        std::cout << "\t" << node->data;

        if (node->left)
        {
            std::cout << "," << std::endl;
        }
        print(node->left, preorder);

        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, preorder);
    }
    else if (tp == postorder)
    {
        print(node->left, postorder);

        if (node->left)
        {
            std::cout << "," << std::endl;
        }
        print(node->right, postorder);
        if (node->right)
        {
            std::cout << "," << std::endl;
        }
        std::cout << "\t" << node->data;
    }
}