#ifndef NODE_H
#define NODE_H

#include <iostream>
using std::cout;
using std::cerr;
using std::endl;

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code for the Node class goes here:
// (Note the 'NodeIterator' class will report lots of errors until Node exists

template <typename T>
class Node {

public:

    T data;
    Node* next;
    Node* previous;

    Node(const T& value) : data(value), next(nullptr), previous(nullptr) {}
};

template<typename T>
class NodeIterator {

private:

    Node<T>* current;
    
public:

    NodeIterator(Node<T>* currentIn) : current(currentIn) {}

    T & operator*() {
        return current->data;
    }

     // TODO: complete the code for NodeIterator here

    const T & operator*() const {
        return current->data;
    }

    NodeIterator& operator++() {
        if (current) {
            current = current->next;
        }
        return *this;
    }

    NodeIterator operator++(int) {
        NodeIterator temp = *this;
        if (current) {
            current = current->next;
        }
        return temp;
    }

    bool operator==(const NodeIterator& other) const {
        return current == other.current;
    }

    bool operator!=(const NodeIterator& other) const {
        return current != other.current;
    }

    Node<T>* getNode() const {
        return current;
    }
};


// do not edit below this line


#endif