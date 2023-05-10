#ifndef READDATA_H
#define READDATA_H

#include <map>
#include <string>

class ReadData {

public: 
    std::map<int, int> fillCoinMap(const std::string& coinfile);
};

#endif