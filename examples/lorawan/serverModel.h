#ifndef SERVERMODEL_H_
#define SERVERMODEL_H_

/* Functions */
char * cmdUnknown(char *buff,unsigned int n);
char * cmdCC(char *buff,unsigned int n);
char * cmdSP(char *buff,unsigned int n);

/* Variables needed for the server */
static const char * cmdArr[] = {"[CC]", "[SP]", 0};
static char * (*ptrFunc[3])(char *,unsigned int) = {cmdUnknown,cmdCC,cmdSP};

/* Extern variables */
extern unsigned int loraWanCounter;

#endif //SERVERMODEL_H_