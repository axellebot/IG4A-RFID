#ifndef READER_MANAGER_H
#define READER_MANAGER_H

#include "ODALID.h"

class ReaderManager
{
public:
    ReaderManager();
    ~ReaderManager();

    int connectReader();
    int disconnectReader();

    int read(int sector,int block);
    int write(int sector,int block,char* data);
    void increment(int block);
    void decrement(int block);

    char* getId();
    char* getVersion();
    char* getData();
    bool isConnected();

private :
    bool connected;
    BYTE key_index;
    int16_t status = 0; // Status
    uint16_t block_size =0; // Block Length
    uint16_t uid_len=0;
    uint8_t * uid; // ID
    uint8_t * data; // Store data;
    uint8_t atq[2];
    uint8_t sak[1];
    char version[30]; // Version

    ReaderName * reader;

    unsigned char* getAccessKeyForSector(int sector,bool accessWrite);
};

#endif // READER_MANAGER_H
