#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>



using std::string;

const std::string FILENAME = "stock.dat";
const std::string TEMP_FILENAME = "temp.dat";

LinkedList::LinkedList() {
    
    head = nullptr;
    readStock();

}

LinkedList::~LinkedList() {
    // TODO
}

Node* LinkedList::getHead() const {
    return head;
}

void LinkedList::displayItems(){
    std::cout << "Items Menu\n----------" << std::endl;
    std::cout << "ID   |Name                                    | Available | Price" << std::endl;
    std::cout << "-------------------------------------------------------------------" <<std::endl;


    Node* currentNode = head;
    std::string spaces(34, ' ');
    while(currentNode != nullptr){
        //std::cout << data->id;
        std::cout << currentNode->data->id << "|" << currentNode->data->name;
        std::cout << spaces; 
        std::cout << currentNode->data->on_hand << std::endl;

        //Moving to the next node
        currentNode = currentNode->next;
        
    }

    return;
}

void LinkedList::purchaseItems(){
    //To be implemented 
    std::cout << "I am being accessed" << std::endl;
}


void LinkedList::addItem(Stock item){
    Node* newNode = new Node(item);

    //if LinkedList is empty: set head to the nexNode
    if(head == nullptr){
        head = newNode;
        count++;
        return;
    }

    /**
     * If linked list is not empty: add item to the end of the LinkedList
    */

    //Go through the list to the last node
    Node* currentNode = head;
    while(currentNode->next != nullptr){
        currentNode = currentNode->next;
    }

    // Make the last node point to the new node
    currentNode->next = newNode;
    count++;
}






void LinkedList::readStock(){
    std::ifstream inputFile("stock.dat");
    

    //Check if file found
    if(!inputFile){
        std::cout << "WARNING: STOCK.DAT NOT FOUND" << std::endl;
        exit(0);
    }

    //Reading each line
    string line;
    while(getline(inputFile, line)){
        std::istringstream ss(line);

        //token for data
        string token;

        //Read itemID
        if(!getline(ss, token, '|')){
            
            //Output unbuffered error message
            std::cerr << "Error: Missing ItemID" << std::endl;
        }

        item.id = token;

        //Read ItemName
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing ItemName for ItemID " << item.id << std::endl;       
        }

        item.name = token;

        //Read Item Description
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing Description for ItemID " << item.id << std::endl;       
        }
        
        item.description = token;

        //Read price
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing Price for ItemID " << item.id << std::endl;      
        }

        /**
         * Need to convert token of type string to unsigned int
        */
        
        //Stores the dollar from token into price.dollars
        item.price.dollars = std::stoi(token.substr(0, token.find('.')));
        item.price.cents = std::stoi(token.substr(token.find('.') + 1));
    

        //Read number on hand
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing Number On Hand for ItemID " << item.id << std::endl;   
        }

        //Change token to type unsigned int
        item.on_hand = std::stoul(token);
       
       addItem(item);
    }

    inputFile.close();
    return;
}



void LinkedList::remove_list() {

    std::cout << "Enter the item id of the item to remove from the menu: ";

    string itemID;
    std::cin >> itemID;
    std::cout << itemID << std::endl;

    Node* current = head;
    Node* previous = nullptr;

    while (current != nullptr) {
        if (current->data->id == itemID) {
            if (previous == nullptr) {

                // Case 1: Item to remove is in the head node
                head = current->next;

            } else {

                // Case 2: Item to remove is in a non-head node
                previous->next = current->next;
            }

            std::cout << current->data->id << " - " << current->data->name << " - " << current->data->description << " has been removed from the system" << std::endl;
            delete current;
            return;
        }

        
        previous = current;
        current = current->next;
    }

    if(current == nullptr){
        std::cout << "Item ID: " << itemID << " not found" << std::endl;
        return;
    }

    return;
}




void LinkedList::reset_Stock(){
    std::ifstream inputFile("stock.dat");

    string line;
    string itemID;
    unsigned int on_hand;
    Node* currentNode = head;

    while(getline(inputFile, line)){
        std::istringstream ss(line);

        //token for data
        string token;

        //Read itemID
        if(!getline(ss, token, '|')){
            
            //Output unbuffered error message
            std::cerr << "Error: Missing ItemID" << std::endl;
        }
        

        //Storing the itemID in a variable;
        itemID = token;

        //Read ItemName
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing ItemName for ItemID " << item.id << std::endl;       
        }

        //Read Item Description
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing Description for ItemID " << item.id << std::endl;       
        }
        
        //Read price
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing Price for ItemID " << item.id << std::endl;      
        }

        /**
         * Need to convert token of type string to unsigned int
        */
        
        //Stores the dollar from token into price.dollars
        item.price.dollars = std::stoi(token.substr(0, token.find('.')));
        item.price.cents = std::stoi(token.substr(token.find('.') + 1));
    

        //Read number on hand
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing Number On Hand for ItemID " << itemID << std::endl;   
        }

        //Storing the no. on hand in a variable
        on_hand = std::stoul(token);


        //Set the current item stock = on_hand
        currentNode->data->on_hand = on_hand;
        currentNode = currentNode->next;
    }


    inputFile.close();
    std::cout << "All stock has been reset to the default level of X" << std::endl;
    return;

}


