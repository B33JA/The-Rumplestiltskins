#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

using std::string;

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();

    // more functions to be added perhaps...

    //Method will display items
    void displayItems();

    //Method will handle users purchasing of items
    void purchaseItems();


private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    //unsigned count;
};

#endif  // LINKEDLIST_H


