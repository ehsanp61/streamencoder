#include "grabber.h"

/**
 * 
*/
tuple<int,Byte> grabber::readData(){
    std::this_thread::sleep_for(READ_FREQUENCY chrono_literals::min);
    int timeStamp = chrono::duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    return {timeStamp,getRandData()};
}
/**
 * 
 * 
*/
Byte grabber::getRandData(){
    return rand() % DATA_RANGE;
}


