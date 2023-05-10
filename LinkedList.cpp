#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;

LinkedList::LinkedList() {
   head = nullptr;
   //Stock* stock = new Stock();

}

LinkedList::~LinkedList() {
    // TODO
}


/**
 * Constructor used to create items.
 * These items should then be stored in the LinkedList
*/

void LinkedList::displayItems(){
    //To be implemented 
    std::cout << "I am being accessed" << std::endl;
}

void LinkedList::purchaseItems(){
    //To be implemented 
    std::cout << "I am being accessed" << std::endl;
}
