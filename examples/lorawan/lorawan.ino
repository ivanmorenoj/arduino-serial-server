#include <serialServer.h>
#include <lorawan.h>
#include "serverModel.h"

byte recvStatus = 0;
char outStr[20];

const sRFM_pins RFM_pins = {
  .CS = SS,
  .RST = RFM_RST,
  .DIO0 = RFM_DIO0,
  .DIO1 = RFM_DIO1,
  .DIO2 = RFM_DIO2,
  .DIO5 = RFM_DIO5,
};


serialServer sServer(&Serial);

void setup() {
    Serial.begin(115200);
    
    delay(2000);
    if(!lora.init()){
        Serial.println("RFM95 not detected");
        delay(5000);
        return;
    }

    sServer.setComands(cmdArr);
    sServer.setFunctions(ptrFunc);

    // Set LoRaWAN Class change CLASS_A or CLASS_C
    lora.setDeviceClass(CLASS_A);

    // Set Data Rate
    lora.setDataRate(SF10BW125);

    // set channel to random
    lora.setChannel(MULTI);
}

void loop() {
    // Check Lora RX
    sServer.handleConnection();
    lora.update();

    recvStatus = lora.readData(outStr);
    if(recvStatus) {
        Serial.println(outStr);
    }
}
