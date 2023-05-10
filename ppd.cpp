#include <iostream>
#include <fstream>

#include "LinkedList.h"
#include "Coin.h"
#include "ReadData.h"
#include "SaveData.h"

std::map<int, int> coinMap;
ReadData read;
SaveData save;
std::string stockfile, coinfile;

using std::string;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
void parseData();
void mainMenu();
int readAndValidate();
void programAllocator(int choice);

void parseData(const char* stockfile, const char* coinfile)
{
    coinMap = read.fillCoinMap(coinfile);

    for(const auto& pair : coinMap)
    {
        std::cout << "D: " << pair.first << ", Q: " << pair.second << std::endl;
    }
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
    mainMenu();
    int choice = readAndValidate();
    programAllocator(choice);

    return EXIT_SUCCESS;
}


//Simple method to display main menu options
void mainMenu(){
    
    std::cout << "\nMain Menu:\n  1.Display Items\n  2.Purchase Items\n  3.Save and Exit" << std::endl;
    std::cout << "Administrator-Only Menu:\n  4.Add Item\n  5.Remove Item\n  6.Display Coins\n  7.Reset Clock\n  8.Reset Coins\n  9.Abort Program" << std::endl;
    std::cout << "Select your option (1-9)" << std::endl;
}

//Method will read user input and validate it
int readAndValidate(){

    try {

    // Will take user input as a string (ignores white spaces)
    string choice;
    std::getline(std::cin >> std::ws, choice);

    //Converts input to an int
    int number = std::stoi(choice);

         //Ensures that the number entered is a valid choice
        if(number < 0 | number > 9){
            std::cout << "This is not a valid input." <<  std::endl;
        }

    //Returns the users validated input
    return number;
    } 
    
    //Catches an incorrect type error (user enters something that isnt an integer)
    catch (std::exception const& e) {
    std::cout << "This is not a valid input." << std::endl;
  }
    return 0;
}

//Determines where to go depending on the users choice
void programAllocator(int choice){
    LinkedList list;
    if(choice == 1){

    }

   else if(choice == 2){
        list.purchaseItems();
   }
    //save data
   else if(choice == 3){

        save.saveCoinMap(coinfile, coinMap);
        exit(0);
   }
}