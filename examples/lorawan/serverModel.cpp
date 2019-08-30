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

    sprintf(buff,"OK");
    return buff;
}

/* Command: [TP] send Tx Power */
char * cmdTP(char *buff,unsigned int n) {
    unsigned char txpower;

    txpower = asciiToHex(buff[4]) & 0x0F;
    lora.setTxPower(txpower);

    memset(buff,0,100);
    sprintf(buff,"OK");
    return buff;
}

/* Command: [AM] send Activation method */
char * cmdAM(char *buff,unsigned int n) {
    String tmpStr = String(buff + 4);

    memset(buff,0,100);
    sprintf(buff,"NOT SUPPORTED");

    if (tmpStr.indexOf("ABP") >= 0)
        sprintf(buff,"OK");

    return buff;
}

/* Command: [DR] send Data Rate */
char * cmdDR(char *buff,unsigned int n) {
    String tmpStr = String(buff + 4);

    memset(buff,0,100);
    sprintf(buff,"OK");

    if (tmpStr.indexOf("SF10BW125") >= 0)
        lora.setDataRate(SF10BW125);
    else if (tmpStr.indexOf("SF9BW125") >= 0)
        lora.setDataRate(SF9BW125);
    else if (tmpStr.indexOf("SF8BW125") >= 0)
        lora.setDataRate(SF8BW125);
    else if (tmpStr.indexOf("SF7BW125") >= 0)
        lora.setDataRate(SF7BW125);
    else
        sprintf(buff,"BAD");

    return buff;
}

/* Command: [CH] send Channel */
char * cmdCH(char *buff,unsigned int n) {
    String tmpStr = String(buff + 4);

    memset(buff,0,100);
    sprintf(buff,"OK");

    if (tmpStr.indexOf("MULTI") >= 0)
        lora.setChannel(MULTI);
    else if (tmpStr.indexOf("CH0") >= 0)
        lora.setChannel(CH0);
    else if (tmpStr.indexOf("CH1") >= 0)
        lora.setChannel(CH1);
    else if (tmpStr.indexOf("CH2") >= 0)
        lora.setChannel(CH2);
    else if (tmpStr.indexOf("CH3") >= 0)
        lora.setChannel(CH3);
    else if (tmpStr.indexOf("CH4") >= 0)
        lora.setChannel(CH4);
    else if (tmpStr.indexOf("CH5") >= 0)
        lora.setChannel(CH5);
    else if (tmpStr.indexOf("CH6") >= 0)
        lora.setChannel(CH6);
    else if (tmpStr.indexOf("CH7") >= 0)
        lora.setChannel(CH7);
    else
        sprintf(buff,"BAD");

    return buff;
}

/* Command: [NK] send Network key */
char * cmdNK(char *buff,unsigned int n) {
    lora.setNwkSKey(buff + 4);

    memset(buff,0,100);
    sprintf(buff,"OK");
    return buff;
}

/* Command: [AK] send App key */
char * cmdAK(char *buff,unsigned int n) {
    lora.setAppSKey(buff + 4);

    memset(buff,0,100);
    sprintf(buff,"OK");
    return buff;
}

/* Command: [DA] send Device Address */
char * cmdDA(char *buff,unsigned int n) {
    lora.setDevAddr(buff + 4);

    memset(buff,0,100);
    sprintf(buff,"OK");
    return buff;
}

/* Command: [FC] send Frame counter */
char * cmdFC(char *buff,unsigned int n) {
    uint32_t frameConunter = 0;

    for (byte i = 0; i < 8; i++)
        frameConunter |= asciiToHex(buff[11 - i]) << (4*i);

    lora.setFrameCounter((unsigned int)frameConunter);

    memset(buff,0,100);
    sprintf(buff,"OK");
    return buff;
}

