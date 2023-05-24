#include "LinkedList.h"
#include <iostream>
#include <fstream>
#include <map>
#include <ostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>


using std::string;

const std::string FILENAME = "stock.dat";
const std::string TEMP_FILENAME = "temp.dat";
std::vector<int> refundGiven;
std::vector<int> changeGiven;
bool inProgress;
int price;
string itemName;
string currentItemID;

LinkedList::LinkedList() {
    
    head = nullptr;
    readStock();
    inProgress = true;

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
    while (currentNode != nullptr) {

        
        std::cout << currentNode->data->id << "|";
        std::cout << std::left << std::setw(42) << currentNode->data->name;
        std::cout << std::setw(13) << currentNode->data->on_hand;
        std::cout << currentNode->data->price.dollars << ".";
        std::cout << currentNode->data->price.cents;

        //Will print "3.00" instead of "3.0"
        if(currentNode->data->price.cents == 0){
            std::cout << 0;
        }

        std::cout << std::endl;


        // Moving to the next node
        currentNode = currentNode->next;
    }

    return;
}

int LinkedList::convertToPrice(int dollars, int cents) {
    return dollars * 100 + cents;
}

std::string LinkedList::convertToDollarsAndCents(int price) 
{
    int dollars = price / 100;
    int cents = price % 100;
    std::string dollarString = "$" + std::to_string(dollars) + ".";
    std::string centString = std::to_string(cents);
    if (centString.size() == 1)
        centString = "0" + centString;  //If cents needs a zero, add a zero
        
    return dollarString + centString;
}

//print formatted price
void LinkedList::formatPrice(int price, std::map<int,int>& coinMap) 
{   //remove coin from coinMap
    if (price >= 100) 
    {
        int dollars = price / 100;       
        if(coinMap[price] == 0)
        {
            std::cout << "Unable to give ";
            std::cout << "$" + std::to_string(dollars) << "." << std::setw(2) << std::setfill('0') << "00";
            std::cout << " as change.";
            if(!refundGiven.empty())
                std::cout << "\n Cancelling and returning change of ";
            for (int change : refundGiven)
            {
                formatPrice(change, coinMap);
            }
            refundGiven.clear();
        }
        else 
        {
            std::cout << "$" + std::to_string(dollars) << " ";
            coinMap[price] = coinMap.at(price) - 1;
        } 
    } 
    else 
    {
        if(coinMap.at(price) == 0)
        {
            std::cout << "Unable to give ";
            std::cout << price << "c";
            std::cout << " as change.";
            if(!refundGiven.empty())
                std::cout << "\n Cancelling and returning change of ";
            for (int change : refundGiven)
            {
                formatPrice(change, coinMap);
            }
            refundGiven.clear();
        }
        else 
        {
            std::cout << price << "c ";
            coinMap[price] = coinMap.at(price) -1;
        }
    }
}

void calculateChange(int remainder, std::map<int,int>& coinMap) 
{
    int denominations[] = {1000, 500, 200, 100, 50, 20, 10, 5};

    for (int denomination : denominations) 
    {
        while (remainder >= denomination) 
        {
            changeGiven.push_back(denomination);
            remainder = remainder - denomination;
        }
    }
}

void LinkedList::purchaseItems(std::map<int,int>& coinMap){
    std::cout << "Purchase Item\n-------------" << std::endl;
    std::cout << "Please enter the id of the item you wish to purchase: ";
    retrieveItem();
    std::cin.ignore();
    while (inProgress && price > 0) 
    {
        std::cout << "You still need to give us " << convertToDollarsAndCents(price) << ": ";
        try 
        {
            // Will take user input as a string (ignores white spaces)
            string choice;
            std::getline(std::cin, choice);
            
            if(choice.empty())
            {
                if(!refundGiven.empty())
                    std::cout << "\nReturning change: ";
                for (int change : refundGiven)
                {
                    formatPrice(change, coinMap);
                }
                std::cout << std::endl;
                refundGiven.clear();
                return;
            }
            //Converts input to an int
            int inputAmount = std::stoi(choice);

            //Check whether inputAmount is a valid demonination
            try 
            {

                //accept input, increment register quantity
                int tempPrice = price;
                price = price - inputAmount;
                coinMap[inputAmount] = coinMap.at(inputAmount) + 1;
                refundGiven.push_back(inputAmount);
                if(price < 0)
                {
                    std::cout << "Here is your " << itemName << " and your change of " << 
                    convertToDollarsAndCents(inputAmount-tempPrice) << ": ";
                    calculateChange((inputAmount-tempPrice),coinMap);
                    for (int change : changeGiven)
                    {
                        formatPrice(change, coinMap);
                    }
                    subtractOnHand(currentItemID);
                    changeGiven.clear();
                    refundGiven.clear();
                }
            } 
            catch (const std::out_of_range&) 
            {
                //Demonination not found
                std::cout << "Error: " << convertToDollarsAndCents(inputAmount) << 
                " is not a valid denomination of money. Please try again." << std::endl;
            }

        }
        //Catches an incorrect type error (user enters something that isnt an integer)
        catch (std::exception const& e) 
        {
            //prevent output if CTRL+D is pressed:
            if(std::cin.eof())
            {   
                if(!refundGiven.empty())
                    std::cout << "\nReturning change: ";
                for (int change : refundGiven)
                {
                    formatPrice(change, coinMap);
                }
                std::cout << std::endl;
                refundGiven.clear();
                inProgress = false;
            }
            else
                std::cout << "This is not a valid input." << std::endl;
        }
    }
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
         * Need to convert token of type string to the unsigned int
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

void descCondenser(const std::string& desc)
{
    std::stringstream ss(desc);
    std::vector<std::string> word;
    std::string words;
    while (ss >> words) {
        word.push_back(words);
    }
    if(word.size() < 5)
        for (const auto& word : desc)
            std::cout << word;
    else
    {
        std::cout << word.at(0) << " "  << word.at(1) << " "  << word.at(2) 
        << " ... " << word[word.size() - 2] << " "  << word[word.size() - 1];
    }
    
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

void LinkedList::retrieveItem() {

    string itemID;
    std::cin >> itemID;

    if(!hasOnHand(itemID))
    {
        std::cout << "Sorry, out of stock! Try another item." << std::endl;
        return;
    }

    Node* current = head;

    while (current != nullptr) {
        if (current->data->id == itemID) 
        {
            std::cout << "You have selected \"" << current->data->name << " - ";
            descCondenser(current->data->description);
            std::cout << "\". This will cost you " << 
            convertToDollarsAndCents(convertToPrice(current->data->price.dollars, 
            current->data->price.cents)) <<"." << std::endl;
            std::cout << "Please hand over the money - type in the value of each note/coin in cents.\n";
            std::cout << "Press enter or ctrl-d on a new line to cancel this purchase:\n";
            price = convertToPrice(current->data->price.dollars, current->data->price.cents);
            itemName = current->data->name;
            currentItemID = itemID;
            return;
        }
        current = current->next;
    }

    if(current == nullptr){
        std::cout << "Item ID: " << itemID << " not found" << std::endl;
        inProgress = false;
        return;
    }
    return;
}

//Purchase made
void LinkedList::subtractOnHand(string itemID) {

    Node* current = head;

    while (current != nullptr) {
        if (current->data->id == itemID) 
        {
            current->data->on_hand--;
            return;
        }
        current = current->next;
    }
    return;
}

//Refund, return item
void LinkedList::addOnHand(string itemID) {

    Node* current = head;

    while (current != nullptr) {
        if (current->data->id == itemID) 
        {
            current->data->on_hand++;
            return;
        }
        current = current->next;
    }
    return;
}

//Can we buy?
bool LinkedList::hasOnHand(string itemID) {

    Node* current = head;

    while (current != nullptr) {
        if (current->data->id == itemID) 
        {
            if(current->data->on_hand > 0)
                return true;
        }
        current = current->next;
    }
    return false;
}
