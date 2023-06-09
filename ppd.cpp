#include <iostream>
#include <fstream>
#include <iomanip>
#include <ostream>
#include "LinkedList.h"
#include "Coin.h"
#include "ReadData.h"
#include "SaveData.h"

std::map<int, int> coinMap;
LinkedList list;
ReadData read;
SaveData save;
bool quit = true;
std::string stockfile, coinfile;


using std::string;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
void mainMenu();
int readAndValidate();
void programAllocator(int choice);

void parseData(const char* stockfile, const char* coinfile)
{
    coinMap = read.fillCoinMap(coinfile);
}

int main(int argc, char **argv)
{
    if(argc !=3)
    {
        std::cout << "Invalid command format. Please use" <<
        " ./ppd <stockfile> <coinsfile>\nEG: ./ppd stock.dat coins.dat" << std::endl;
        exit(0);
    }
    stockfile = argv[1];
    coinfile = argv[2];
    parseData(argv[1], argv[2]);
    while (quit) 
    {
        int choice = readAndValidate();
        programAllocator(choice);
    }
    

    return EXIT_SUCCESS;
}


//Simple method to display main menu options
void mainMenu(){
    
    std::cout << "\nMain Menu:\n  1.Display Items\n  2.Purchase Items\n  3.Save and Exit" << std::endl;
    std::cout << "Administrator-Only Menu:\n  4.Add Item\n  5.Remove Item\n  6.Display Coins\n  7.Reset Stock\n  8.Reset Coins\n  9.Abort Program" << std::endl;
    std::cout << "Select your option (1-9): ";
}

//Method will read user input and validate it
int readAndValidate(){
    mainMenu();
    try {

    // Will take user input as a string (ignores white spaces)
    string choice;
    std::getline(std::cin >> std::ws, choice);

    //Converts input to an int
    int number = std::stoi(choice);

         //Ensures that the number entered is a valid choice
        if(number < 1 || number > 9){
            std::cout << "This is not a valid input." <<  std::endl;
        }

    //Returns the users validated input
    return number;
    } 
    
    //Catches an incorrect type error (user enters something that isnt an integer)
    catch (std::exception const& e) {
    //prevent output if CTRL+D is pressed:
    
    if(std::cin.eof())
    {
        save.saveCoinMap(coinfile, coinMap);
        save.saveLinkedList(stockfile, list);
        exit(0);
    }
        
    std::cout << "This is not a valid input." << std::endl;
  }
    return 0;
}

std::string returnDenomType(int denom){
    if(denom>=100)
        return std::to_string(denom/100) + " Dollar";
    else
        return std::to_string(denom) + " Cents";
}

//display coins for menu
void displayCoins(){
    std::cout << "Coins Summary\n-------------" << std::endl;
    std::cout << "Denomination    |    Count" << std::endl;
    std::cout << "---------------------------" <<std::endl;
    for(const auto& val : coinMap)
    {
        std::cout << std::left << std::setw(16) << returnDenomType(val.first);
        std::cout << "|" << std::setw(11) << std::right << std::setw(10) << val.second << std::endl;
    }

}

//Determines where to go depending on the users choice
void programAllocator(int choice){
    
    if(choice == 1){
        list.displayItems();
    }

   else if(choice == 2){
        list.purchaseItems(coinMap);
   }
    //save data
   else if(choice == 3){

        save.saveCoinMap(coinfile, coinMap);
        save.saveLinkedList(stockfile, list);
        exit(0);
   }

    else if(choice == 4){
        list.createItem();
    }

    else if (choice == 5)
   {
    list.remove_list();
   }
   else if (choice == 6)
   {
    displayCoins();
   }
   else if (choice == 7)
   {
    list.reset_Stock();
   }
   else if (choice == 8)
   {
    coinMap = read.fillCoinMap(coinfile); //re-read coinfile, replacing current coinMap
    std::cout << "All coins have been reset to the default level of X." << std::endl;
   }
   else if (choice == 9)
   {
    std::cout << "Aborting." << std::endl;
    exit(0);
   }
}
