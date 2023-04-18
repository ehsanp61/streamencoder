#include "grabber.h"
#include "tractive.h"
#include "gsmTransmitter.h"
#include <fstream>
#include <sstream>



int main(){
    shared_ptr<tractive> oTractive(new tractive);
    bool endSimulation = false;

    auto grabberRunner = [&](){
            fstream simulationFile;
            stringstream ss;
            simulationFile.open("sampleAcc2.dat", ios::in );
            string fileLine,words;
            int dataIn,timeStamp,acc;
            cout << "Start import Data Exist:" << simulationFile.good() << endl;
            while(getline(simulationFile,fileLine)){
            try{
                words = "";
                ss.clear();
                ss << fileLine;
                ss >> words;
                if (stringstream(words) >> dataIn) timeStamp = dataIn;
                ss >> words;
                if (stringstream(words) >> dataIn) acc = dataIn;
                if(oTractive->writeFlash({timeStamp,acc})!=0)cout << "Miss Data!!" << endl;
                std::this_thread::sleep_for(chrono::milliseconds(10));
            }catch(exception){
                cout << "Exception in grabberRunner!!!";
                simulationFile.close();
            }
        }
        simulationFile.close();
        cout << "End of simulated Data!!!";
        endSimulation = true;
    };

    auto gsmRunner = [&](){
            ofstream encodedData;
            encodedData.open("encodedData2.dat", ios::out );
            vector<Byte> outCode;
            while(1){
            try{
                if(endSimulation)break;
                if(!oTractive->readyToSend){
                    std::this_thread::sleep_for(chrono::milliseconds(2));
                    //cout << "Try To Send!!!" << endl;
                    continue;
                }
                while(1){
                    auto dataPack = oTractive->readFlash();
                    if(get<0>(dataPack) == ENDOFREAD){
                        //End of coding and start sending
                        //cout << "Reach to End for send" << endl;
                        oTractive->oGsm.endStream();
                        outCode = oTractive->oGsm.send(1);
                        for(auto it = outCode.begin();it != outCode.end(); ++it)
                            encodedData << (int)(*it) << " ";
                        encodedData << endl;
                        //cout << "Sent To Out" << endl;
                        break;
                    }else{
                        oTractive->oGsm.loadData(dataPack);
                        //cout << "load Data For send" << endl;
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
