#include "reader_manager.h"
#include "MfErrNo.h"
#include <QtGui>


ReaderManager::ReaderManager()
{
    this->reader = ReaderName();
}

int ReaderManager::read(BYTE sect_count){
    return 0;
}

int ReaderManager::connectReader(){
    uint16_t status = 0;
    //reader.Type = ReaderTCP;
    //strcpy(MonLecteur.IPReader, pszHost);
    reader.Type = ReaderCDC;
    reader.device = 0;
    status = OpenCOM1(&reader);
    qDebug() << "OpenCOM1" << status;
    return status;
}

char* ReaderManager::getVersion(){
    uint16_t status = 0;

    char version[30];
    uint8_t serial[4];
    char stackReader[20];
    status = Version(&reader, version, serial, stackReader);
    return version;
}

void ReaderManager::other(){
    uint16_t status = 0;

    uint8_t serial[4];
    char stackReader[20];
    status = Version(&reader, version, serial, stackReader);

    uint8_t atq[2];
    uint8_t sak[1];
    uint8_t uid[12];
    uint16_t uid_len = 12;
    uint8_t sect_count = 0;
    int i;
    char s_buffer[64];

    RF_Power_Control(&reader, TRUE, 0);

    status = ISO14443_3_A_PollCard(&reader, atq, sak, uid, &uid_len);

    if (status != MI_OK){
        printf("No available tag in RF field\n");
        return this->disconnectReader();
    }

    printf("Tag found: UID=");
    for (i = 0; i < uid_len; i++){
        printf("%02X", uid[i]);
    }
    printf(" ATQ=%02X%02X SAK=%02X\n", atq[1], atq[0], sak[0]);

    if ((atq[1] != 0x00) || ((atq[0] != 0x02) && (atq[0] != 0x04) && (atq[0] != 0x18))){
        printf("This is not a Mifare classic tag\n");
        goto tag_halt;
    }

    if ((sak[0] & 0x1F) == 0x08){
        // Mifare classic 1k : 16 sectors, 3+1 blocks in each sector
        printf("Tag appears to be a Mifare classic 1k\n");
        sect_count = 16;
    } else if ((sak[0] & 0x1F) == 0x18){
        // Mifare classic 4k : 40 sectors, 3+1 blocks in 32-first sectors, 15+1 blocks in the 8-last sectors
        printf("Tag appears to be a Mifare classic 4k\n");
        sect_count = 40;
    }

    sect_count = 16;
    status = read(sect_count);

    goto tag_halt;

    tag_halt:
        // Halt the tag
        status = ISO14443_3_A_Halt(&reader);
        if (status != MI_OK){
            printf("Failed to halt the tag\n");
            this->disconnectReader();
            return;
        }
}

void ReaderManager::disconnectReader(){
    int16_t status = 0;
    RF_Power_Control(&reader, FALSE, 0);
    status = LEDBuzzer(&reader, LED_OFF);
    status = CloseCOM1(&reader);
}
