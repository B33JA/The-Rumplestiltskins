#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "SaveData.h"

void SaveData::saveCoinMap(const std::string& coinfile, const std::map<int,int>& coinMap)
{
    std::ofstream outputFile(coinfile);
    if(outputFile.is_open())
    {
        for(const auto& pair : coinMap)
        {
            outputFile << pair.first << "," << pair.second << std::endl;
        }
        outputFile.close();
        std::cout << "Successfully saved coins.dat" << std::endl;            
    }
    else
    {
        std::cout << "Unable to save file";
    }
}