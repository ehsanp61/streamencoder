#include<iostream>
#define CXX_STANDARD 17 // C++ version
#include "tractive.h"
#define WAIT_FOR_SEND 10 // in Second
#include <thread>
#include <memory>
using namespace std;

int main(int argc, int* args){
    shared_ptr<tractive> oTractive(new tractive);

    auto grabberRunner = [&](){
            while(1){
            try{
                if(oTractive->writeFlash(oTractive->oGrabber.readData())!=0)cout << "Mis Data!!" << endl;
            }catch(Exception){
                cout << "Exception in grabberRunner!!!"
            }
        }
    }

    auto gsmRunner = [&](){
            while(1){
            try{
                if(!oTractive->readyToSend){
                    std::this_thread::sleep_for(WAIT_FOR_SEND chrono_literals::s);
                    continue;
                }
                do{
                    auto dataPack = oTractive->readFlash();                    
                    if(get<0>(dataPack) == ENDOFREAD){
                        //End of coding and start sending
                        oTractive->oGsm.endStream();
                        oTractive->oGsm.send();
                        break;
                    }else{
                        oTractive->oGsm->loadData(dataPack);
                    }
                }while(1)
                
            }catch(Exception){
                cout << "Exception in grabberRunner!!!"
            }
        }
    }

    thread grabberThread(grabberRunner);

    cout << "Hello Encoder";
    grabberThread.join();
    return 0;
}


