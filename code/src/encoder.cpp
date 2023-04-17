#include "encoder.h"

encoder::encoder(void){
    runCount = 0;
    currectSymbol = 0;
    if(HUFFMAN_TIER)makeHuffmanCode();
}

deque<Byte> encoder::importData(Byte symbolIn){
    Byte symbol;
    deque<Byte> encodedSymbol;
    bool huffPossible = true;
    if(QUANTIZER_TIER)
        symbol = quantizationTier(symbolIn);
    else
        symbol = symbolIn;
    if(runCount>50)huffPossible = false;
    encodedSymbol = rleTier(symbol);
    if(encodedSymbol.size()>0)
        if(HUFFMAN_TIER){
            if(huffPossible)
                encodedSymbol =  huffmanTier(encodedSymbol);
            else
                encodedSymbol.push_front(255);
        }

    return encodedSymbol;
}
/**
 *
*/
deque<Byte> encoder::endStream(){
    deque<Byte> outputSymbol;
    bool huffPossible = true;
    outputSymbol.push_back((runCount >> 8) & 0XFF);
    outputSymbol.push_back((runCount >> 0) & 0XFF);
    outputSymbol.push_back(currectSymbol);
    if(runCount>50)huffPossible = false;
    if(outputSymbol.size()>0)
        if(HUFFMAN_TIER){
            if(huffPossible)
                outputSymbol =  huffmanTier(outputSymbol);
            else
                outputSymbol.push_front(255);
        }
    currectSymbol = 0;
    runCount = 0;
    return outputSymbol;
}
/**
 * Lossy Compression Tier for reducing dynamic range and increasing compression rate
 *
 * @param symbolIn: input symbol in Byte (0-254)
 * @return quantized output
*/
Byte encoder::quantizationTier(Byte symbolIn){
    return symbolIn/QUANTIZATION_SCALE;
}
/**
 *
*/
deque<Byte> encoder::rleTier(Byte symbolIn){
    deque<Byte> outputSymbol;
    if(runCount == 0){
        currectSymbol = symbolIn;
        runCount = 1;
        return outputSymbol;
    }
    if(currectSymbol == symbolIn){
        runCount++;
    }else{
        outputSymbol.push_back((runCount >> 8) & 0XFF);
        outputSymbol.push_back((runCount >> 0) & 0XFF);
        outputSymbol.push_back(currectSymbol);
        currectSymbol = symbolIn;
        runCount = 1;
    }
    return outputSymbol;
}
/**
 *
*/
deque<Byte> encoder::huffmanTier(deque<Byte> symbolIn){
    int huffmanInd;
    huffmanInd = (huffmanInd << 8) + symbolIn.at(0);
    huffmanInd = (huffmanInd << 8) + symbolIn.at(1);
    huffmanInd = (huffmanInd << 8) + symbolIn.at(2);
    return huffmanCode.at(huffmanInd);

}
/**
 *
*/
void encoder::makeHuffmanCode(){
    cout << "Start Huffman Code!!" << endl;

    Byte huffCodeSm1 = 0,huffCodeSm2 = 0,huffCodeSm3 = 0,huffCodeSm4 = 0;
    uShort rlCount = 0, firstInd = 1;
    int rlCountControl = STEP_LENGTH ;
    while(rlCountControl <= MAX_LENGTH){
        for(Byte j = 0 ; j <= 254 ; j++)
            for(rlCount = firstInd; rlCount <= rlCountControl ; rlCount++)
            {
                deque<Byte> huffCode;
                if(huffCodeSm1<253){
                    huffCode.push_back(huffCodeSm1);
                    huffCodeSm1++;
                    huffCodeSm2 = 0;
                }
                else{
                    switch(huffCodeSm1){
                        case 253:
                            if(huffCodeSm2<255){
                                huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                huffCode.push_back(huffCodeSm2);
                                huffCodeSm2++;
                            }else{
                                huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                huffCode.push_back(huffCodeSm2);
                                huffCodeSm1 = 254;
                                huffCodeSm3 = 0;
                                huffCodeSm2 = 0;
                            }
                            break;
                        case 254:
                            if(huffCodeSm3<255){
                                if(huffCodeSm2<255){
                                    huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                    huffCode.push_back(huffCodeSm2);
                                    huffCode.push_back(huffCodeSm3);
                                    huffCodeSm2++;
                                }else{
                                    huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                    huffCode.push_back(huffCodeSm2);
                                    huffCode.push_back(huffCodeSm3);
                                    huffCodeSm2 = 0;
                                    huffCodeSm3++;
                                }
                            }
                            else{
                                huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                huffCode.push_back(huffCodeSm2);
                                huffCode.push_back(huffCodeSm3);
                                huffCodeSm1 = 255;
                                huffCodeSm2 = 0;
                                huffCodeSm3 = 0;
                                huffCodeSm4 = 0;

                            }
                            break;
                        case 255:
                            if(huffCodeSm4<255){
                                if(huffCodeSm3<255){
                                    if(huffCodeSm2<255){
                                        huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                        huffCode.push_back(huffCodeSm2);
                                        huffCode.push_back(huffCodeSm3);
                                        huffCode.push_back(huffCodeSm4);
                                        huffCodeSm2++;
                                    }else{
                                        huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                        huffCode.push_back(huffCodeSm2);
                                        huffCode.push_back(huffCodeSm3);
                                        huffCode.push_back(huffCodeSm4);
                                        huffCodeSm2 = 0;
                                        huffCodeSm3++;
                                    }
                                }
                                else{
                                    huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                    huffCode.push_back(huffCodeSm2);
                                    huffCode.push_back(huffCodeSm3);
                                    huffCode.push_back(huffCodeSm4);
                                    huffCodeSm2 = 0;
                                    huffCodeSm3 = 0;
                                    huffCodeSm4++;
                                }
                            }
                            else{
                                huffCode.push_back(huffCodeSm1);  // first segment 252 (2 Byte Code)
                                huffCode.push_back(huffCodeSm2);
                                huffCode.push_back(huffCodeSm3);
                                huffCode.push_back(huffCodeSm4);
                                cout << "Huff Code is Not enough, add more codes!!" << endl;
                            }
                            break;
                    }
                }
                saveCode(rlCount,j,huffCode);
            }
            if(rlCountControl == MAX_LENGTH) break;
            firstInd = rlCountControl;
            rlCountControl = rlCountControl + STEP_LENGTH < MAX_LENGTH ?rlCountControl + STEP_LENGTH:MAX_LENGTH;
    }
    cout << "End making Huffman Code!!" << endl;
}
void encoder::saveCode(uShort rlCountIn, Byte symbolIn, deque<Byte> huffCodeIn){
        try{
        int huffInd = 0;
        huffInd = (huffInd << 8) + ((rlCountIn>>8) & 0xFF);
        huffInd = (huffInd << 8) + ((rlCountIn>>0) & 0xFF);
        huffInd = (huffInd << 8) + symbolIn;
        //cout << "huffInd:" << huffInd << endl;
        huffmanCode.at(huffInd) = huffCodeIn;
        //cout << "huffInd:" << huffInd << "write!!!" << endl;
        }catch(exception){
            cout << "Error In Huffman save Codes!!!" << endl;
        }
}

bool encoder::test_huffmanCode(){
    bool result=true;

    int huffInd = 0;
    uShort rlCountIn = 0;
    Byte symbolIn;
    deque<Byte> expHuffCode,assHuffCode;
    makeHuffmanCode();

    //case 1
    rlCountIn = 1;
    symbolIn = 0;
    expHuffCode.push_back(0);
    huffInd = (huffInd << 8) + ((rlCountIn>>8) & 0xFF);
    huffInd = (huffInd << 8) + ((rlCountIn>>0) & 0xFF);
    huffInd = (huffInd << 8) + symbolIn;
    if(expHuffCode != huffmanCode.at(huffInd))result = false;

    //case 2
    rlCountIn = 1;
    symbolIn = 2;
    expHuffCode.clear();
    expHuffCode.push_back(40);
    huffInd = 0;
    huffInd = (huffInd << 8) + ((rlCountIn>>8) & 0xFF);
    huffInd = (huffInd << 8) + ((rlCountIn>>0) & 0xFF);
    huffInd = (huffInd << 8) + symbolIn;
    if(expHuffCode != huffmanCode.at(huffInd))result = false;

    //case 3
    rlCountIn = 50;
    symbolIn = 110;
    expHuffCode.clear();
    expHuffCode.push_back(254);
    expHuffCode.push_back(158);
    expHuffCode.push_back(43);
    huffInd = 0;
    huffInd = (huffInd << 8) + ((rlCountIn>>8) & 0xFF);
    huffInd = (huffInd << 8) + ((rlCountIn>>0) & 0xFF);
    huffInd = (huffInd << 8) + symbolIn;
    assHuffCode = huffmanCode.at(huffInd);
    if(assHuffCode.size()>0){
        if(expHuffCode != assHuffCode)result = false;
    }

    return result;
}
