#include "serverModel.h"
#include <string.h>
#include <stdio.h>

char * UnknownCommand(char *buff) {
    char tmp[50];
    strcpy(tmp,buff);
    sprintf(buff,"Unknown: %s", tmp);
    return buff;
}

char * CCResponse(char *buff){
    sprintf(buff,"OK");
    return buff;
}
