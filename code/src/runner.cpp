#include<iostream>
#define CXX_STANDARD 17 // C++ version
#include "tractive.h"
#define WAIT_FOR_SEND 20 // in Second
#include <thread>
#include <memory>
#include <chrono>
using namespace std;
/*
int main(int argc, int* args){
    shared_ptr<tractive> oTractive(new tractive);

    auto grabberRunner = [&](){
            while(1){
            try{
                if(oTractive->writeFlash(oTractive->oGrabber.readData())!=0)cout << "Miss Data!!" << endl;
            }catch(exception){
                cout << "Exception in grabberRunner!!!";
            }
        }
    };

    auto gsmRunner = [&](){
            while(1){
            try{
                if(!oTractive->readyToSend){
                    std::this_thread::sleep_for(chrono::milliseconds(WAIT_FOR_SEND)); //seconds
                    cout << "Try To Send!!!" << endl;
                    continue;
                }
                while(1){
                    auto dataPack = oTractive->readFlash();
                    if(get<0>(dataPack) == ENDOFREAD){
                        //End of coding and start sending
                        cout << "Reach to End for send" << endl;
                        oTractive->oGsm.endStream();
                        oTractive->oGsm.send(0);
                        cout << "Sent To Out" << endl;
                        break;
                    }else{
                        oTractive->oGsm.loadData(dataPack);
                        cout << "load Data For send" << endl;
                    }
                }
            }catch(exception){
                cout << "Exception in grabberRunner!!!";
            }
        }
    };

    thread grabberThread(grabberRunner);
    thread gsmTransmitterThread(gsmRunner);

    cout << "Tractive Start!" << endl;
    grabberThread.join();
    gsmTransmitterThread.join();
    cout << "Tractive Stop!" << endl;
    return 0;
}
*/

