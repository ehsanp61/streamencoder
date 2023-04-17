#include "grabber.h"

grabber::grabber(){
    dataCounter = 0;
}

/**
 *
*/
tuple<int,Byte> grabber::readData(){
    std::this_thread::sleep_for(chrono::seconds(READ_FREQUENCY)); //minutes
    int timeStamp = chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return {timeStamp,getRandData()};
}
/**
 *
 *
*/
Byte grabber::getRandData(){
    cout << "Get Data(" << dataCounter++ << ")" << endl;
    return rand() % DATA_RANGE;
}


