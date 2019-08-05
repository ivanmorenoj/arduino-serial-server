#include "serverModel.h"
#include <Arduino.h>
#include <string.h>
#include <stdio.h>
#include <lorawan.h>

static unsigned char asciiToHex(char c) {
    if (c >= '0' && c <= '9')
        return (unsigned char)(c - '0');
    else if (c >= 'A' && c <= 'F')
        return (unsigned char)(c - 55);
    else if (c >= 'a' && c <= 'f')
        return (unsigned char)(c - 87);
    else 
        return 0; 
}

static void parsePayload(char *_buff,unsigned int *_len) {
    char *auxbuff = new char[*_len + 1];
    strncpy(auxbuff,_buff,*_len);

    memset(_buff,0,*_len);

    unsigned int newLen = 0;
    for (int i = 0; i < *_len - 1; i+=2) {
        _buff[newLen]  = (asciiToHex(auxbuff[i]) & 0x0F) << 4;
        _buff[newLen++] |= (asciiToHex(auxbuff[i + 1]) & 0x0F);
    }

    *_len = newLen;

    delete []auxbuff;
}

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
    unsigned int newLen = n - 4;
    char auxbuff[100];
    memset(auxbuff,0,100);
    
    for (byte i = 4; i < n; i++)
        auxbuff[i - 4] = buff[i];

    parsePayload(auxbuff,&newLen);

    lora.sendUplink(auxbuff,newLen,1);
    loraWanCounter++;

    sprintf(buff,"OK");
    return buff;
}
