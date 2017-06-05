#include "include/start.h"

void start(void){
    Chain toyChain=Porting();
    Chain *ptrchain=&toyChain;
    Serial.println("Initial device START.");
    Serial.begin(ptrchain->moniPort);

    pinInitial(ptrchain);
    wifiInitial(ptrchain);
  
    t.every(500, wifiMain);
    Serial.println("Initial device OVER.");
}

