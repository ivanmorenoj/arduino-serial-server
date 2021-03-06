#ifndef SERIALSERVER_H_
#define SERIALSERVER_H_

#include <Arduino.h>
#include <Stream.h>

#define BUFF_SIZE   100

class serialServer
{
private:
    Stream* _ser;
    byte _numOfCommands;
    char _buffer[BUFF_SIZE];
    char **_commandsArr;
    char *(**_responseFunct)(char *,unsigned int);

public:
    serialServer(Stream *stream);
    serialServer();
    ~serialServer();
    void setStream(Stream *stream);
    void setComands(const char ** ptrArr);
    void setFunctions(char * (**ptr)(char *,unsigned int));
    void handleConnection();
    
};

#endif //SERIALSERVER_H_
