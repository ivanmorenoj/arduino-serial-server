#include "serialServer.h"

serialServer::serialServer(Stream *stream) {
    this->_ser = stream;
}

void serialServer::setStream(Stream *stream) {
    this->_ser = stream;
}

serialServer::serialServer() {
    _ser = NULL;
}

serialServer::~serialServer() {
    /* Nothing */
}

void serialServer::setComands(const char ** ptrArr) {
    _commandsArr = (char **)ptrArr;
    _numOfCommands = 0;
    for (char ** aux = (char **)ptrArr; *aux; aux++, _numOfCommands++);
}

void serialServer::setFunctions(char * (**ptr)(char *,unsigned int n)) {
    _responseFunct = ptr;
}

void serialServer::handleConnection() {
    if (_ser->available()) {
        char auxbuff[BUFF_SIZE];
        /*byte size = 0;

        while (_ser->available() && size < 0xFF) {
            _buffer[size++] = _ser->read();
        }*/
        byte size = _ser->readBytesUntil('\n',_buffer, BUFF_SIZE);;

        while (_ser->available()) _ser->read();

        _ser->flush();
        
        int index = -1;
        for (byte i = 0; i < _numOfCommands ;i++)
            if (strncmp(_buffer,_commandsArr[i],strlen(_commandsArr[i])) == 0) {
                index = i;
                break;
            }

        memset(auxbuff,NULL,BUFF_SIZE);

        strncpy(auxbuff,_buffer,size);

        sprintf(_buffer,"%s\n",(_responseFunct[index + 1])(auxbuff,size));
        
        _ser->write(_buffer);

        _ser->flush();

        memset(_buffer,NULL,BUFF_SIZE);
    }

}

