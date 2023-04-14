#ifndef TRACTIVE_H
#define TRACTIVE_H
#include "tractive.h"
#include "grabber.h"
#include "gsmTransmitter.h"
#include "baseType.h"
#define FLASH_SIZE 50400 // In Byte

#include<array>
using namespace std;
class tractive{
    array<Byte,FLASH_SIZE> flash;


    tractive();
    

};

#endif