#ifndef SERVERMODEL_H_
#define SERVERMODEL_H_

/* Functions */
char * UnknownCommand(char *buff, unsigned int n);
char * CCResponse(char *buff, unsigned int n);

/* Variables needed for the server */
static const char * cmdArr[] = {"[CC]", 0};
static char * (*ptrFunc[2])(char *,unsigned int) = {UnknownCommand,CCResponse};

#endif