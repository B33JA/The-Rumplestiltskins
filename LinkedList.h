#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "Node.h"
#include <map>

using std::string;

class LinkedList
{
public:
    LinkedList();
    ~LinkedList();
    Stock item;
    Coin coin; 

    // more functions to be added perhaps...

    //Method will display items
    void displayItems();

    //Method will handle users purchasing of items
    void purchaseItems(std::map<int,int>& coinMap);

    //Used to add items to the linked list
    void addItem(Stock item);

    //Used to create a new item to be added
    void createItem();

    //Used to read data from stock.dat
    void readStock();

    Node* getHead() const; // Accessor for head
    
    void remove_list();

    void reset_Stock();

    void retrieveItem();

    void formatPrice(int price, std::map<int,int>& coinMap);

    void subtractOnHand(string itemID);

    void addOnHand(string itemID);

    bool hasOnHand(string itemID);

    //temp helper functions
    int convertToPrice(int dollars, int cents);
    std::string convertToDollarsAndCents(int price);


private:
    // the beginning of the list
    Node* head;
  
    // how many nodes are there in the list?
    unsigned count;
};

#endif  // LINKEDLIST_H


