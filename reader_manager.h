#ifndef READER_MANAGER_H
#define READER_MANAGER_H

#include "ODALID.h"

class ReaderManager
{
public:
    ReaderManager();
    int read(BYTE);
    int connectReader();
    void disconnectReader();
    char* getVersion();
    void other();
private :
    ReaderName reader;
};

#endif // READER_MANAGER_H
