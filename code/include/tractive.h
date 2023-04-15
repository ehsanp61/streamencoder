#ifndef TRACTIVE_H
#define TRACTIVE_H
#include "grabber.h"
#include "gsmTransmitter.h"
#include "baseType.h"
#include<tuple>
#include<array>


#define FLASH_SIZE 50400 // In Byte
#define BUF_ONE_ADD 0
#define BUF_TWO_ADD FLASH_SIZE/2
#define BUF_LEN FLASH_SIZE/2
#define ENDOFREAD -2
#define WAITFORREAD -1


using namespace std;
class tractive{
    array<Byte,FLASH_SIZE> flash;
    grabber oGrabber;
    gsmTransmitter oGsm;
    int bufPhase; // 0: low buf read high buf write  - 1: low buf write high buf read
    int bufReadPos;
    int bufWritePos;
    bool sent;// Use just by gsmTransmitter
    bool readyToSend; // Use just by grabber
    bool flashOverflow;

public:
    tractive();
    tuple<int,Byte> readFlash(void);
    int writeFlash(tuple<int,Byte> dataIn);
    bool phaseChange(void);
    bool endOfFlashForRead();
    bool endOfFlashForWrite();
    

};

#endif