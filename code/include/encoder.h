#ifndef ENCODER_H
#define ENCODER_H
#include <deque>
#include <array>

#define QUANTIZER_TIER 0
#define HUFFMAN_TIER 0
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
    array<deque<Byte>,(MAX_LENGTH+1)*256> huffmanCode;

    Byte quantizationTier(Byte);
    deque<Byte> rleTier(Byte);
    deque<Byte> huffmanTier(deque<Byte>);
    void makeHuffmanCode();
    public:
        encoder(void);
        deque<Byte> importData(Byte);
        deque<Byte> endStream(void);
        void saveCode(uShort, Byte, deque<Byte>);
        bool test_huffmanCode();



};
#endif
