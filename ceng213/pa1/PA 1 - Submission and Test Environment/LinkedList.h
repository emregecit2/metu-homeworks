#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

#include "Node.h"

template <class T>
class LinkedList
{
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    int getSize() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;
    Node<T> *getNodeAtIndex(int index) const;

    void insertAtTheFront(const T &data);
    void insertAtTheEnd(const T &data);
    void insertAfterNode(const T &data, Node<T> *node);
    void insertAsEveryKthNode(const T &data, int k);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();
    void removeEveryKthNode(int k);

    void swap(Node<T> *node1, Node<T> *node2);
    void shuffle(int seed);

    void print(bool reverse = false) const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.
private: // DO NOT CHANGE THIS PART.
    Node<T> *head;

    int size;
};

template <class T>
LinkedList<T>::LinkedList()
{
    head = NULL;
    size = 0;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj)
{
    head = NULL;
    size = 0;
    Node<T> *curr = obj.head;
    for (int i = 0; i < obj.size; i++)
    {
        insertAtTheEnd(curr->data);
        curr = curr->next;
    }
}

template <class T>
LinkedList<T>::~LinkedList()
{
    if (size != 0)
    {
        Node<T> *curr = head;
        for (int i = 1; i < size; i++)
        {
            curr = curr->next;
            delete curr->prev;
        }
        delete curr;
    }
}

template <class T>
int LinkedList<T>::getSize() const
{
    return size;
}

template <class T>
bool LinkedList<T>::isEmpty() const
{
    return size == 0;
}

template <class T>
bool LinkedList<T>::contains(Node<T> *node) const
{
    Node<T> *curr = head;
    for (int i = 0; i < size; i++)
    {
        if (curr == node)
        {
            return true;
        }
        curr = curr->next;
    }
    return false;
}

template <class T>
Node<T> *LinkedList<T>::getFirstNode() const
{
    return head;
}

template <class T>
Node<T> *LinkedList<T>::getLastNode() const
{
    return head ? head->prev : NULL;
}

template <class T>
Node<T> *LinkedList<T>::getNode(const T &data) const
{
    Node<T> *curr = head;
    for (int i = 0; i < size; i++)
    {
        if (curr->data == data)
        {
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}

template <class T>
Node<T> *LinkedList<T>::getNodeAtIndex(int index) const
{
    Node<T> *curr = head;
    if (index >= size || index < 0)
    {
        return NULL;
    }
    for (int i = 0; i < index; i++)
    {
        curr = curr->next;
    }
    return curr;
}

template <class T>
void LinkedList<T>::insertAtTheFront(const T &data)
{
    if (size == 0)
    {
        head = new Node<T>(data);
        head->prev = head->next = head;
    }
    else
    {
        Node<T> *new_node = new Node<T>(data, head->prev, head);
        head->prev->next = new_node;
        head->prev = new_node;
        head = new_node;
    }
    size++;
}

template <class T>
void LinkedList<T>::insertAtTheEnd(const T &data)
{
    if (size == 0)
    {
        head = new Node<T>(data);
        head->prev = head->next = head;
    }
    else
    {
        Node<T> *new_node = new Node<T>(data, head->prev, head);
        head->prev->next = new_node;
        head->prev = new_node;
    }
    size++;
}

template <class T>
void LinkedList<T>::insertAfterNode(const T &data, Node<T> *node)
{
    Node<T> *curr = head;
    for (int i = 0; i < size; i++)
    {
        if (curr == node)
        {
            Node<T> *new_node = new Node<T>(data, curr, curr->next);
            curr->next->prev = new_node;
            curr->next = new_node;
            size++;
            break;
        }
        curr = curr->next;
    }
}

template <class T>
void LinkedList<T>::insertAsEveryKthNode(const T &data, int k)
{
    Node<T> *curr = head;
    if (k >= 2)
    {
        for (int j = 1; j < size + 1; j++)
        {
            if ((j + 1) % k == 0)
            {
                insertAfterNode(data, curr);
            }
            curr = curr->next;
        }
    }
}

template <class T>
void LinkedList<T>::removeNode(const T &data)
{
    if(size){
        Node<T> *curr = head;
        if (head->data == data)
        {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
            delete curr;
            if(!--size){
                head = NULL;
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                if (curr->data == data)
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    delete curr;
                    size--;
                    break;
                }
                curr = curr->next;
            }
        }
    }
}

template <class T>
void LinkedList<T>::removeNode(Node<T> *node)
{
    if(size){
        Node<T> *curr = head;
        if (head == node)
        {
            head->prev->next = head->next;
            head->next->prev = head->prev;
            head = head->next;
            delete curr;
            if(!--size){
                head = NULL;
            }
        }
        else
        {
            for (int i = 0; i < size; i++)
            {
                if (curr == node)
                {
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    delete curr;
                    size--;
                    break;
                }
                curr = curr->next;
            }
        }
    }
}

template <class T>
void LinkedList<T>::removeAllNodes()
{
    Node<T> *curr = head;
    for (int i = 1; i < size; i++)
    {
        curr = curr->next;
        delete curr->prev;
    }
    delete curr;
    size = 0;
    head = NULL;
}

template <class T>
void LinkedList<T>::removeEveryKthNode(int k)
{
    Node<T> *curr = head, *next;
    if (k >= 2)
    {
        Node<T> *t;
        for (int j = 1; j < size * k; j++)
        {
            next = curr->next;
            if (j % k == 0)
            {
                removeNode(curr);
            }
            curr = next;
        }
    }
}

template <class T>
void LinkedList<T>::swap(Node<T> *node1, Node<T> *node2)
{
    if (contains(node1) && contains(node2) && node1 != node2)
    {
        if (size != 2)
        {
            if (node1->next == node2)
            {
                node1->prev->next = node2;
                node2->next->prev = node1;

                node2->prev = node1->prev;
                node1->prev = node2;
                node1->next = node2->next;
                node2->next = node1;
            }
            else if (node2->next == node1)
            {
                node1->next->prev = node2;
                node2->prev->next = node1;

                node1->prev = node2->prev;
                node2->prev = node1;
                node2->next = node1->next;
                node1->next = node2;
            }
            else
            {
                Node<T> *t;
                node1->next->prev = node2;
                node1->prev->next = node2;
                node2->next->prev = node1;
                node2->prev->next = node1;

                t = node1->prev;
                node1->prev = node2->prev;
                node2->prev = t;

                t = node1->next;
                node1->next = node2->next;
                node2->next = t;
            }
        }
        if (node1 == head)
        {
            head = node2;
        }
        else if (node2 == head)
        {
            head = node1;
        }
    }
}

template <class T>
void LinkedList<T>::shuffle(int seed)
{
    for (int i = 0; i < size; i++)
    {
        swap(getNodeAtIndex(i), getNodeAtIndex((i * i + seed) % size));
    }
}

template <class T>
void LinkedList<T>::print(bool reverse) const
{
    if (isEmpty())
    {
        std::cout << "The list is empty." << std::endl;
        return;
    }

    if (reverse)
    {
        // traverse in reverse order (last node to first node).

        Node<T> *node = getLastNode();

        do
        {
            std::cout << *node << std::endl;
            node = node->prev;
        } while (node != getLastNode());
    }
    else
    {
        // traverse in normal order (first node to last node).

        Node<T> *node = getFirstNode();

        do
        {
            std::cout << *node << std::endl;
            node = node->next;
        } while (node != getFirstNode());
    }
}

template <class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs)
{
    Node<T> *curr = rhs.head;
    removeAllNodes();
    for (int i = 0; i < rhs.size; i++)
    {
        insertAtTheEnd(curr->data);
        curr = curr->next;
    }
    return *this;
}

#endif // LINKEDLIST_H
