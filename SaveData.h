#ifndef SAVEDATA_H
#define SAVEDATA_H

#include "LinkedList.h"
#include <map>
#include <string>

class SaveData {

public: 
    //save map from memory into file -- if file is not present, create and save
    void saveCoinMap(const std::string& coinfile, const std::map<int,int>& coinMap);

    void saveLinkedList(const std::string& stockfile, const LinkedList& list);
};

#endif