#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <sstream>



using std::string;

LinkedList::LinkedList() {
    
    head = nullptr;

}

LinkedList::~LinkedList() {
    // TODO
}


void LinkedList::displayItems(){
    readStock();
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
}






void LinkedList::readStock(){
    std::ifstream inputFile("stock.dat");
    

    //Check if file found
    if(!inputFile){
        std::cout << "Error opening file" << std::endl;
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
         * Need to convert token of type string to the unsigned int
        */
        
        //Stores the dollar from token into price.dollars
        item.price.dollars = std::stoi(token.substr(0, token.find('.')));
        item.price.cents = std::stoi(token.substr(token.find('.') + 1));
    

        //Read number on hand
        if(!getline(ss, token, '|')){
            std::cerr << "Error: Missing NUmber On Hand for ItemID " << item.id << std::endl;   
        }

        //Change token to type unsigned int
        item.on_hand = std::stoul(token);
       
       addItem(item);
    }

    inputFile.close();
    return;
}
