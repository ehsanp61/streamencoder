#ifndef GRABBER_H
#define GRABBER_H
#include <iostream>
#include "baseType.h"
#define DATA_RANGE 254
#include <chrono>
#include <thread>
#include<tuple>

#define READ_FREQUENCY 1 //Per Minutes
using namespace std;
using namespace std::chrono_literals;

class grabber{
    Byte getRandData();
    public:
        tuple<int,Byte> readData();
        

};
#endif