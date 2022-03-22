
#include "LinkedList.h"

LinkedList::~LinkedList() {
    for (Node *p; !isEmpty(); ) {
        p = head->next;
        delete head;
        head = p;
    }
}

void LinkedList::addToHead(string el) {
    head = new Node(el,head);
    if (tail == 0)
       tail = head;
	size++;
}

void LinkedList::addToTail(string el) {
    if (tail != 0) {      // if list not empty;
         tail->next = new Node(el);
         tail = tail->next;
    }
    else head = tail = new Node(el);
	size++;
}

int LinkedList::GetSize(){
	return size;
}

string LinkedList::GetAt(int x){
	Node *tmp = head;
	for(int i = 1;i<x && tmp!=NULL;i++){
		//cout << tmp->info <<endl;
		tmp = tmp->next;
	}
	return tmp->info;
}

string LinkedList::deleteFromHead() {
    string el = head->info;
    Node *tmp = head;
    if (head == tail)     // if only one node on the list;
         head = tail = 0;
    else head = head->next;
    delete tmp;
	size--;
    return el;
}


string LinkedList::deleteFromTail() {
    string el = tail->info;
    if (head == tail) {   // if only one node on the list;
         delete head;
         head = tail = 0;
    }
    else {                // if more than one node in the list,
         Node *tmp; // find the predecessor of tail;
         for (tmp = head; tmp->next != tail; tmp = tmp->next);
         delete tail;
         tail = tmp;      // the predecessor of tail becomes tail;
         tail->next = 0;
    }
	size--;
    return el;
}

void LinkedList::deleteNode(string el) {
    if (head != 0)                     // if non-empty list;
         if (head == tail && el == head->info) { // if only one
              delete head;                       // node on the list;
              head = tail = 0;
         }
         else if (el == head->info) {  // if more than one node on the list
              Node *tmp = head;
              head = head->next;
              delete tmp;              // and old head is deleted;
         }
         else {                        // if more than one node in the list
              Node *pred, *tmp;
              for (pred = head, tmp = head->next; // and a non-head node
                   tmp != 0 && !(tmp->info == el);// is deleted;
                   pred = pred->next, tmp = tmp->next);
              if (tmp != 0) {
                   pred->next = tmp->next;
                   if (tmp == tail)
                      tail = pred;
                   delete tmp;
              }
         }
}

bool LinkedList::isInList(string el) const {
    Node *tmp;
    for (tmp = head; tmp != 0 && !(tmp->info == el); tmp = tmp->next);
    return tmp != 0;
}

void LinkedList::printAll() const {
    for (Node *tmp = head; tmp != 0; tmp = tmp->next)
        cout << tmp->info << " ";
	cout << endl;
}

