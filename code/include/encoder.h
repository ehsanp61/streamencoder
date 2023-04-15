#ifndef ENCODER_H
#define ENCODER_H
#include <deque>

#define ENCODER_LEVEL 0 // 0 RLCoding, 1 RLCoding + 
#define QUANTIZATION_SCALE 2 
#include <iostream>

using namespace std;
typedef unsigned short int uShort;

class encoder{
    uShort runCount;
    Byte currectSymbol;

    public:
        encoder(void);
        deque<Byte> importData(Byte symbolIn);
        deque<Byte> endStream();
        Byte quantizationTier();
        Byte runlenthTier();
        Byte hofmanTier();


};
#endif