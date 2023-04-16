#ifndef GSMTRANSMITTER_H
#define GSMTRANSMITTER_H

#include <iostream>
#include <deque>
#include <tuple>
#include <vector>
#include "baseType.h"
#include "encoder.h"

using namespace std;
class gsmTransmitter{
    deque<Byte> transmitterBuffer;
    encoder oEncoder;
    bool state;
    int dataCounter;
    public:
        gsmTransmitter();
        vector<Byte> send(int);
        void loadData(tuple<int,Byte> dataIn);
        void endStream(void);

};
#endif
