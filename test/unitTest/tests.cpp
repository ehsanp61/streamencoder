#include "grabber.h"
#include "tractive.h"
#include "gsmTransmitter.h"

#define IS_TRUE(x) { if (!(x)) cout << __FUNCTION__ << " failed on line " << __LINE__ << endl; }


/**
*Unit Tests
*/
bool testGetData(){
    bool result = true;

    grabber oGrabber;
    tuple<int,Byte> data, dataPre;
    for(int i = 0 ; i < 10 ; i++){
        data = oGrabber.readData();
        //cout << "i:"<< i << " " <<get<0>(data) << " ** " << (int)get<1>(data) << endl;
        if(i>0)
            if(get<0>(data) - get<0>(dataPre)!=READ_FREQUENCY)result = false;
        dataPre = data;
    }
    return result;
}

bool testTractive_init(){
    bool result = true;

    tractive otractive;
    IS_TRUE(otractive.test_init());

    return result;
}

bool testTractive_writeFlash(){
    bool result = true;
    tractive oTractive;
    Byte data = 0 ;
    for(int i = 0 ; i < FLASH_SIZE/5 ; i++){
        oTractive.writeFlash({i,data++});
    }
    if(oTractive.writeFlash({0,0}) != 1)result = false;

    return result;
}

bool testTractive_writeReadFlash(){
    bool result = true;

    tuple<int,Byte> dataPack,preDataPack;
    tractive oTractive;
    Byte data = 0 ;
    int cnt = 0;
    for(int j = 0 ; j < 30 ; j++){
        for(int i = 0 ; i <= (FLASH_SIZE/5)/2 ; i++){
            oTractive.writeFlash({cnt++,data++});
        }
        for(int i = 0 ; i <= (FLASH_SIZE/5)/2 ; i++){
            dataPack = oTractive.readFlash();
            if(i>0 && get<0>(dataPack) >= 0){
                if(get<0>(dataPack) - get<0>(preDataPack)!=1){
                        result = false;
                        cout << "error in time" << endl;
                }
                if((int)get<1>(dataPack) - (int)get<1>(preDataPack)!=1){
                        result = false;
                        if(!((int)get<1>(preDataPack)==255 && (int)get<1>(dataPack)==0))
                            cout << "error in data" << endl;
                }
                if((int)get<1>(preDataPack)==255 && (int)get<1>(dataPack)==0) result = true;
            }
            preDataPack = dataPack;
            //cout << "Read dataPack:" << get<0>(dataPack) << " ** " << (int)get<1>(dataPack) << endl;
        }
    }

    return result;
}

bool testGsmTransmitter_loadData(){
    //without Huffman Tier
    bool result = true;
    int i;
    gsmTransmitter oGsm;
    for(i = 1 ; i < 1001 ; i ++){
        oGsm.loadData({i,5});
    }
    for(i = 1 ; i < 122 ; i ++){
        oGsm.loadData({i,6});
    }
    for(i = 1 ; i < 23 ; i ++){
        oGsm.loadData({i,5});
    }
    oGsm.loadData({i++,6});
    oGsm.endStream();
    vector<Byte> outStream = oGsm.send(1);
    if(outStream.size()>0){
        if(outStream.at(3) != 1)result = false;
        if(outStream.at(4) != 3)result = false;
        if(outStream.at(5) != 232)result = false;
        if(outStream.at(6) != 5)result = false;
        if(outStream.at(7) != 0)result = false;
        if(outStream.at(8) != 121)result = false;
        if(outStream.at(9) != 6)result = false;
        if(outStream.at(10) != 0)result = false;
        if(outStream.at(11) != 22)result = false;
        if(outStream.at(12) != 5)result = false;
        if(outStream.at(13) != 0)result = false;
        if(outStream.at(14) != 1)result = false;
        if(outStream.at(15) != 6)result = false;
    }
    return result;
}

bool test_encoderHuffman(){
    bool result = true;

    encoder oEncoder;
    result = oEncoder.test_huffmanCode();

    return result;
}

bool testGsmTransmitter_huffmanCode(){
    bool result = true;
    int i;
    gsmTransmitter oGsm;
    for(i = 1 ; i < 2 ; i ++){
        oGsm.loadData({i,0});
    }
    for(i = 1 ; i < 51 ; i ++){
        oGsm.loadData({i,110});
    }
    for(i = 1 ; i < 2 ; i ++){
        oGsm.loadData({i,2});
    }
    oGsm.endStream();
    vector<Byte> outStream = oGsm.send(1);
    if(outStream.size()>0){
        if(outStream.at(3) != 1)result = false;
        if(outStream.at(4) != 0)result = false;
        if(outStream.at(5) != 254)result = false;
        if(outStream.at(6) != 158)result = false;
        if(outStream.at(7) != 43)result = false;
        if(outStream.at(8) != 40)result = false;
    }
    return result;
}



int main(){
    //bool test1 = false;
    //cout << "Test1 State:" << test1 << endl;
    IS_TRUE(testGetData());
    testTractive_init();
    IS_TRUE(testTractive_writeFlash());
    IS_TRUE(testTractive_writeReadFlash());
    IS_TRUE(testGsmTransmitter_loadData());
    IS_TRUE(test_encoderHuffman());
    IS_TRUE(testGsmTransmitter_huffmanCode());

    return 0;

}

