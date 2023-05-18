#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "ReadData.h"

std::map<int, int> ReadData::fillCoinMap(const std::string& coinfile) 
{
    std::ifstream inputFile(coinfile);
    std::string line;
    std::map<int, int> coins;

    //Storing the denomination values within an array
    int denomValue[] = {5, 10, 20, 50, 100, 200, 500, 1000};

    //Check if file not found
    if (!inputFile) {
        std::cout << "WARNING: COINS.DAT NOT FOUND" << std::endl;
        exit(0);
    }

        while (std::getline(inputFile, line)) {
            std::stringstream ss(line);
            std::string denomination_str;
            std::string quantity_str;

            //attempt to retrieve an uninterrupted line in the format denomination,quantity
            try {
                // Check if line contains at least 2 values seperated by comma
                if (std::getline(ss, denomination_str, ',') &&
                    std::getline(ss, quantity_str, ',')) {
                    //Check if values are integer values
                    int denomination = std::stoi(denomination_str);
                    int quantity = std::stoi(quantity_str);
                    //initiate a new map element with key denominatiom, initialise value to quantity
                    if(quantity >= 0 && denomination > 0)
                        coins[denomination] = quantity;
                    else
                        std::cout <<"Error: Invalid formatting on line -> " << line << std::endl;                   
                    
                } else {
                    // Empty Line, or only one value present
                    std::cout << "Error: No Data Present!" << std::endl;
            }

            } catch (std::invalid_argument const&) {
                // Empty value for values or values not integers (failed conversion) 
                std::cout << "Error: Invalid formatting on line -> " << line << std::endl;
            }  
        }

    //correct amount of denominations?
    if (coins.size() != 8) {
        std::cout << "WARNING: IMPROPER DATA DETECTED" << std::endl;
        exit(0);
    }

    // Close the input file
    inputFile.close();
    //Return map
    return coins;
}

