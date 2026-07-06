#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "node.h"
#include <utility>

// Do not add any #include statements here.  If you have a convincing need for adding a different `#include` please post in the forum on KEATS.

// TODO your code goes here:
template <typename T>

class LinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    LinkedList(std::initializer_list<T> init) : head(nullptr), tail(nullptr), count(0) {
        for (const T& value : init) {
            push_back(value);
        }
    }

    ~LinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }

    void push_front(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->previous = newNode;
            head = newNode;
        }
        count++;
    }

    void push_back(const T& value) {
        Node<T>* newNode = new Node<T>(value);
        if (tail == nullptr) {
            head = tail = newNode;
        } else {
            newNode->previous = tail;
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    int size() const {
        return count;
    }

    T& front() const {
        return head->data;
    }

    T& back() const {
        return tail->data;
    }

    void reverse() {
        Node<T>* current = head;
        Node<T>* temp = nullptr;

        while (current) {
            temp = current->previous;
            current->previous = current->next;
            current->next = temp;
            current = current->previous;
        }

        if (temp) {
            head = temp->previous;
        }
    }

    NodeIterator<T> begin() const {
        return NodeIterator<T>(head);
    }

    NodeIterator<T> end() const {
        return NodeIterator<T>(nullptr);
    }

    NodeIterator<T> insert(NodeIterator<T> position, const T& value) {
        if (position == begin()) {
            push_front(value);
            return begin();
        }

        Node<T>* newNode = new Node<T>(value);
        Node<T>* current = head;
        NodeIterator<T> it = begin();
        
        while (it != position) {
            ++it;
            current = current->next;
        }

        newNode->next = current;
        newNode->previous = current->previous;
        current->previous->next = newNode;
        current->previous = newNode;
        count++;

        return NodeIterator<T>(newNode);
    }

    NodeIterator<T> erase(NodeIterator<T> position) {
        Node<T>* current = head;
        NodeIterator<T> it = begin();
        
        while (it != position) {
            ++it;
            current = current->next;
        }

        if (current == head) {
            head = current->next;
            if (head) {
                head->previous = nullptr;
            } else {
                tail = nullptr;
            }
        } else if (current == tail) {
            tail = current->previous;
            tail->next = nullptr;
        } else {
            current->previous->next = current->next;
            current->next->previous = current->previous;
        }

        Node<T>* nextNode = current->next;
        delete current;
        count--;

        return NodeIterator<T>(nextNode);
    }

    NodeIterator<T> begin() {
        return NodeIterator<T>(head);
    }

    NodeIterator<T> end() {
        return NodeIterator<T>(nullptr);
    }
};


// do not edit below this line


#endif