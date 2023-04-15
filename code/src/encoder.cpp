#include "encoder.h"

void encoder::encoder(void){

}

deque<Byte> encoder::importData(Byte symbolIn){

}
deque<Byte> encoder::endStream(){

}
Byte encoder::quantizationTier(Byte symbolIn){
    return symbolIn/QUANTIZATION_SCALE;
}
deque<Byte> encoder::runlenthTier(Byte symbolIn){
    if(currectSymbol == symbolIn){
        runCount++;
    }else{

    }
}
Byte encoder::hofmanTier(){

}