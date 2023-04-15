#include "gsmTransmitter.h"


/**
 * 
*/
void gsmTransmitter::gsmTransmitter(void){
    state = false;
}   

/**
 * 
*/
void gsmTransmitter::send(void){
    try{
        while (!transmitterBuffer.empty()){
            cout << "GSM Send:" << transmitterBuffer.front() << endl;
            transmitterBuffer.pop_front();
        }
        state = false;
    }catch(...){
        cout << "Exception in GSM send!!" << endl;
    }
}
/**
 * 
 * 
*/
void gsmTransmitter::loadData(tuple<int,Byte> dataIn){
    if(!state){
        state = true;
        transmitterBuffer.push_back((dataIn >> 24) & 0xFF);
        transmitterBuffer.push_back((dataIn >> 16) & 0xFF);
        transmitterBuffer.push_back((dataIn >> 8) & 0xFF);
        transmitterBuffer.push_back((dataIn >> 0) & 0xFF);
    }
    deque<Byte> outSymbols = oEncoder.importData(get<1>(dataIn));
    while(!outSymbols.empty()){
        transmitterBuffer.push_back(outSymbols.front());
        outSymbols.pop_front();
    }
}
/**
 * 
*/
deque<Byte> gsmTransmitter::endStream(void){
    deque<Byte> outSymbols = oEncoder.endStream();
    while(!outSymbols.empty()){
        transmitterBuffer.push_back(outSymbols.front());
        outSymbols.pop_front();
    }    
}
