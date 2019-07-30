#include <serialServer.h>
#include "serverModel.h"

serialServer sServer(&Serial);

void setup() {
    Serial.begin(115200);
    
    delay(2000);
    Serial.println("init Connection");

    sServer.setComands(cmdArr);
    sServer.setFunctions(ptrFunc);
}

void loop() {
    sServer.handleConnection();
}
