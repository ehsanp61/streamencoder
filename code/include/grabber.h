#ifndef GRABBER_H
#define GRABBER_H
#include <iostream>
#include "baseType.h"
#define DATA_RANGE 254
#include <chrono>
#include <thread>
#include<tuple>

#define READ_FREQUENCY 2 //Here per milliseconds in real system Per Minutes
using namespace std;

class grabber{
    Byte getRandData();
    int dataCounter;
    public:
        tuple<int,Byte> readData();
        grabber();


};
#endif
