#include "gsmTransmitter.h"


/**
 *
*/
gsmTransmitter::gsmTransmitter(void){
    state = false;
    dataCounter = 0;
    transmitterBuffer.clear();
}

/**
 *
*/
vector<Byte> gsmTransmitter::send(int mode){
    try{
        vector<Byte> outStream;
        while (!transmitterBuffer.empty()){
            if(mode == 0)
                cout << "GSM Send:" << (int)transmitterBuffer.front() << endl;
            if(mode == 1)
                outStream.push_back(transmitterBuffer.front());
            transmitterBuffer.pop_front();
        }
        state = false;
        return outStream;
    }catch(exception){
        cout << "Exception in GSM send!!" << endl;
    }
}
/**
 *
 *
*/
void gsmTransmitter::loadData(tuple<int,Byte> dataIn){
    cout << "Send Data(" << dataCounter++ << ")" << endl;
    if(!state){
        state = true;
        transmitterBuffer.push_back((get<0>(dataIn) >> 24) & 0xFF);
        transmitterBuffer.push_back((get<0>(dataIn) >> 16) & 0xFF);
        transmitterBuffer.push_back((get<0>(dataIn) >> 8) & 0xFF);
        transmitterBuffer.push_back((get<0>(dataIn) >> 0) & 0xFF);
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
void gsmTransmitter::endStream(void){
    deque<Byte> outSymbols = oEncoder.endStream();
    while(!outSymbols.empty()){
        transmitterBuffer.push_back(outSymbols.front());
        outSymbols.pop_front();
    }
}
