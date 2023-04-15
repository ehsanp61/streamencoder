#ifndef GSMTRANSMITTER_H
#define GSMTRANSMITTER_H

#include <iostream>
#include <deque>
#include <tuple>
#include "baseType.h"
#include "encoder.h"

using namespace std;
class gsmTransmitter{
    deque<Byte> transmitterBuffer;
    encoder oEncoder;
    public:
        gsmTransmitter();
        void send(void);
        deque<Byte> loadData(tuple<int,Byte> dataIn); 
        deque<Byte> endStream(void);

};
#endif