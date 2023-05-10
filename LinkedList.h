#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"

using std::string;

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    Stock item;

    // more functions to be added perhaps...

    //Method will display items
    void displayItems();

    //Method will handle users purchasing of items
    void purchaseItems();

    //Used to add items to the linked list
    void addItem(Stock item);

    //Used to read data from stock.dat
    void readStock();


private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    //unsigned count;
};

#endif  // LINKEDLIST_H


