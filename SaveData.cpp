#include <iostream>
#include <fstream>
#include <iterator>
#include <sstream>
#include <string>
#include <map>
#include "SaveData.h"
//required for maintaining cents value
#include <iomanip>

void SaveData::saveCoinMap(const std::string& coinfile, const std::map<int,int>& coinMap)
{
    std::ofstream outputFile(coinfile);
    if(outputFile.is_open())
    {
        for(const auto& mapContent : coinMap)
        {
            outputFile << mapContent.first << "," << mapContent.second << std::endl;
        }
        outputFile.close();
        std::cout << "Successfully saved coins.dat" << std::endl;            
    }
    else
        std::cout << "Unable to save file" << coinfile << std::endl;
}

void SaveData::saveLinkedList(const std::string& stockfile, const LinkedList& list)
{
    std::ofstream outputFile(stockfile);
    if (outputFile.is_open()) 
    {
        Node* currentNode = list.getHead();
        while (currentNode != nullptr) 
        {
            outputFile << currentNode->data->id << "|" << currentNode->data->name
            << "|" << currentNode->data->description << "|" << currentNode->data->price.dollars
            << "." << std::setw(2) << std::setfill('0') << currentNode->data->price.cents << "|" << currentNode->data->on_hand << std::endl;
            currentNode = currentNode->next;
        }
        outputFile.close();
        std::cout << "Successfully saved stock.dat" << std::endl;     
    }
    else
        std::cout << "Unable to save file" << stockfile << std::endl;  
}