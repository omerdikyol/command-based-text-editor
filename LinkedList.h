#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED
#include <iostream>
#include <string>

using namespace std;
class Node {
public:
    Node() {
        next = 0;
    }
    Node(string el, Node *ptr = 0) {
        info = el; next = ptr;
    }
    string info;
    Node *next;
};

class LinkedList {
public:

    Node *head, *tail;
	int size;

    LinkedList() {
        head = tail = 0;
		size = 0;
    }
    ~LinkedList();
    int isEmpty() {
        return head == 0;
    }
	int GetSize(void);
	string GetAt(int);
    void addToHead(string);
    void addToTail(string);
    string  deleteFromHead(); // delete the head and return its info;
    string  deleteFromTail(); // delete the tail and return its info;
    void deleteNode(string);
    bool isInList(string) const;
    void printAll() const;

};


#endif // LINKEDLIST_H_INCLUDED
