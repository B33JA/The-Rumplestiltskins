#include "Coin.h"
#include <iostream>
#include <fstream>

using std::string;

//Storing the denomination values within an array
int denomValue[] = {5, 10, 20, 50, 100, 200, 500, 1000};

int Coin::displayValue(Denomination denom){
    return denomValue[denom];
}

 