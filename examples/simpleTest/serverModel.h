#ifndef SERVERMODEL_H_
#define SERVERMODEL_H_

/* Functions */
char * UnknownCommand(char *buff);
char * CCResponse(char *buff);

/* Variables needed for the server */
static const char * cmdArr[] = {"[CC]", 0};
static char * (*ptrFunc[2])(char *) = {UnknownCommand,CCResponse};

#endif