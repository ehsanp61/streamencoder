#ifndef ENCODER_H
#define ENCODER_H
#include <deque>
#include <array>

#define QUANTIZER_TIER 0
#define HUFFMAN_TIER 1
#define QUANTIZATION_SCALE 2
#define MAX_LENGTH 50
#define STEP_LENGTH 20
#include <iostream>
#include "baseType.h"


using namespace std;
typedef unsigned short int uShort;

class encoder{
    uShort runCount;
    Byte currectSymbol;


    Byte quantizationTier(Byte);
    deque<Byte> rleTier(Byte);
    deque<Byte> huffmanTier(deque<Byte>);

    public:
        encoder(void);
        deque<Byte> importData(Byte);
        deque<Byte> endStream(void);
        void saveCode(uShort, Byte, deque<Byte>);

        array<deque<Byte>,MAX_LENGTH*254> huffmanCode;
        void makeHuffmanCode();
};
#endif
