#ifndef SERVERMODEL_H_
#define SERVERMODEL_H_

/* Functions */
char * cmdUnknown(char *buff,unsigned int n);
char * cmdCC(char *buff,unsigned int n);
char * cmdSP(char *buff,unsigned int n);
char * cmdTP(char *buff,unsigned int n);
char * cmdAM(char *buff,unsigned int n);
char * cmdDR(char *buff,unsigned int n);
char * cmdCH(char *buff,unsigned int n);
char * cmdNK(char *buff,unsigned int n);
char * cmdAK(char *buff,unsigned int n);
char * cmdDA(char *buff,unsigned int n);
char * cmdFC(char *buff,unsigned int n);

/* Variables needed for the server */
static const char * cmdArr[] = {"[CC]", "[SP]", "[TP]", "[AM]", "[DR]", "[CH]", "[NK]", "[AK]", "[DA]", "[FC]", 0};
static char * (*ptrFunc[11])(char *,unsigned int) = {
    cmdUnknown, /* Unknown Command */ 
    cmdCC,      /* Check communication */
    cmdSP,      /* Send Payload */
    cmdTP,      /* send Tx Power */
    cmdAM,      /* send Activation method */
    cmdDR,      /* send Data Rate */  
    cmdCH,      /* send Channel */  
    cmdNK,      /* send Network key */  
    cmdAK,      /* send App key */  
    cmdDA,      /* send Device Address */  
    cmdFC       /* send Frame counter */
};

/* Extern variables */
extern unsigned int loraWanCounter;

#endif //SERVERMODEL_H_