#include "tractive.h"


tractive::tractive(){
    flash.fill(0);    
    bufPhase = 0;
}

/**
 * This fuction read tuple of timestamp & data from flash
 * @return tuple<timestamp_int,data_byte>
*/
tuple<int,Byte> tractive::readFlash(void){
    int timestamp = 0;
    Byte data = 0;
    Byte dataPack[4];
    if(sent && (!readyToSend)) return {WAITFORREAD,0};
    if(readyToSend)readyToSend=false;
    if(endOfFlashForRead()){
        sent = true;
        return {ENDOFREAD,0}
    }
    dataPack[0] = flash.at(bufReadPos++);
    dataPack[1] = flash.at(bufReadPos++);
    dataPack[2] = flash.at(bufReadPos++);
    dataPack[3] = flash.at(bufReadPos++);
    data        = flash.at(bufReadPos++);

    timestamp = (timestamp << 8) + dataPack[0];
    timestamp = (timestamp << 8) + dataPack[1];
    timestamp = (timestamp << 8) + dataPack[2];
    timestamp = (timestamp << 8) + dataPack[3];
    return {timestamp,data};
}

/**
 * 
*/
int tractive::writeFlash(tuple<int,Byte> dataIn){
    Byte  bytes[5];
    bytes[0] = (get<0>(dataIn) >> 24) & 0xFF;
    bytes[1] = (get<0>(dataIn) >> 16) & 0xFF;
    bytes[2] = (get<0>(dataIn) >> 8)  & 0xFF;
    bytes[3] = (get<0>(dataIn) >> 0)  & 0xFF;
    bytes[4] =  get<1>(dataIn);
    if(endOfFlashForWrite()){
        phaseChange();
    }
    if(flashOverflow){ 
        return 1;
    }
    else{        
        flash.at(bufWritePos++) = bytes[0];
        flash.at(bufWritePos++) = bytes[1];
        flash.at(bufWritePos++) = bytes[2];
        flash.at(bufWritePos++) = bytes[3];
        flash.at(bufWritePos++) = bytes[4];        
    }
    return 0;
}

/**
 * 
*/
bool tractive::phaseChange(void){
    if(sent){
            bufReadPos = bufPhase == 0 ? 0 : FLASH_SIZE/2;
            bufWritePos = bufPhase == 0 ? FLASH_SIZE/2 : 0;
            bufPhase = bufPhase == 1 ? 0 : 1;
            readyToSend = true;
            sent = false;
            flashOverflow=false;
            return true;
    }else{
            flashOverflow=true;
            cout << "Miss Data(Flash Overflow)!!";
            return false;
    }
}
/**
 * 
*/
bool tractive::endOfFlashForWrite(void){
    if(bufPhase==0){
        if(bufWritePos>FLASH_SIZE/2-5)
            return true;
        else
            return false;
    }else{
        if(bufWritePos>FLASH_SIZE-5)
            return true;
        else
            return false;
    }
}
/**
 * 
*/
bool tractive::endOfFlashForRead(void){
    if(bufPhase==1){
        if(bufReadPos>FLASH_SIZE/2-5)
            return true;
        else
            return false;
    }else{
        if(bufReadPos>FLASH_SIZE-5)
            return true;
        else
            return false;
    }
}