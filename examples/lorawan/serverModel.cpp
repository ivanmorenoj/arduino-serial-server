#include "serverModel.h"
#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include <lorawan.h>

/* for unknown command */
char * cmdUnknown(char *buff,unsigned int n) {
    memset(buff,0,sizeof(buff));
    sprintf(buff,"UNKNOWN");
    return buff;
}

/* Command: [CC] */
char * cmdCC(char *buff,unsigned int n) {
    sprintf(buff,"OK");
    return buff;
}

/* Command: [SP] send payload*/
char * cmdSP(char *buff,unsigned int n) {
    char auxbuff[100];
    memset(auxbuff,0,100);
    
    for (byte i = 4; i < n; i++) {
        auxbuff[i - 4] = buff[i];
        Serial.print(buff[i]);
    }

    /*lora.sendUplink(auxbuff,n-4,1);
    loraWanCounter++; */

    sprintf(buff,"OK");
    return buff;
}
