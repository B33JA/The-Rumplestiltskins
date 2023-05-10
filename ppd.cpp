#include <iostream>
#include <fstream>

#include "LinkedList.h"
#include "Coin.h"

using std::string;

/**
 * manages the running of the program, initialises data structures, loads
 * data, display the main menu, and handles the processing of options. 
 * Make sure free memory and close all files before exiting the program.
 **/
void readdata(string name);
void mainMenu();
int readAndValidate();
void programAllocator(int choice);

int main(int argc, char **argv)
{
    /* validate command line arguments */
    // TODO

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

   else if(choice == 3){
        exit(0);
   }
}