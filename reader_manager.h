#ifndef READER_MANAGER_H
#define READER_MANAGER_H

#include "ODALID.h"

class ReaderManager
{
public:
    ReaderManager();
    ~ReaderManager();

    char* read();
    int connectReader();
    int disconnectReader();
    char* getId();
    char* getVersion();
    void increment(int block);
    void decrement(int block);
    int write(int sector,int block,uint8_t* data);
private :
    BYTE key_index;
    int16_t status = 0; // Registering status
    uint16_t uid_len = 12; // ID Length
    BYTE uid[12]; // ID
    BYTE atq[2];
    BYTE sak[1];
    char version[30]; // Version

    ReaderName * reader;
};

#endif // READER_MANAGER_H
