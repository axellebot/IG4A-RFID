#include "reader_manager.h"
#include "MfErrNo.h"
#include <QtGui>
unsigned char KEY_FAKE[6] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
unsigned char KEY_A[6]  = {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5}; // Lire Block 2
unsigned char KEY_B[6]  = {0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xB5}; // Lire + Ecrire Block 2
unsigned char KEY_C[6]  = {0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5}; // Lire + Increment + Transfert Block 3
unsigned char KEY_D[6]  = {0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0xD5}; // Lire + Decrement + Transfert Block 3

ReaderManager::ReaderManager()
{
    this->uid_len=12;
    this->uid = new uint8_t[uid_len];

    this->block_size=16;
    this->data=new uint8_t[block_size];

    this->reader = new ReaderName();
    this->reader->Type = ReaderCDC;
    this->reader->device = 0;

    this->connected=true;
}

ReaderManager::~ReaderManager(){
    this->disconnectReader(); // Disconnect Reader
    delete this->reader;
    delete uid;
    delete data;
}

int ReaderManager::connectReader(){
    // Open COM1
    status = OpenCOM1(reader);
    if (status != MI_OK){
        printf("OpenCOM1 [FAILED] %\n",status);
        return status;
    }
    printf("OpenCOM1 [SUCCEED] %\n",status);

    status = LEDBuzzer(reader, LED_ON);

    uint8_t serial[4];
    char stackReader[20];

    status = Version(reader, version, serial, stackReader);
    if (status != MI_OK){
        printf("Load [FAILED] %\n",status);
        return status;
    }
    printf("Load Version [SUCCEED] %\n",status);

    // Load Keys
    key_index = 0;
    status = Mf_Classic_LoadKey(reader, Auth_KeyA, KEY_A, key_index);

    if (status != MI_OK){
        printf("Load Key [FAILED]\n");
        return status;
    }
    printf("Load Key [SUCCEED]\n");

    // RF field ON
    RF_Power_Control(reader, TRUE, 0);
    if (status != MI_OK){
        printf("RF_Power_Control [FAILED] %\n",status);
        return status;
    }
    printf("RF_Power_Control [SUCCEED] %\n",status);

    //Recuperate card id
    status = ISO14443_3_A_PollCard(reader, atq, sak, uid, &uid_len);
    if (status != MI_OK){
        printf("No available tag in RF field\n");
        return status;
    }
    printf("Available tag in RF field\n");

    printf("TAG found with UID{");
    for (int i = 0; i < uid_len; i++){
        printf("%02X", uid[i]);
    }
    connected=true;
    return status;
}

int ReaderManager::disconnectReader(){
    // RF field ON
    status = RF_Power_Control(reader, FALSE, 0);
    if (status != MI_OK){
        printf("RF_Power_Control [FAILED] %\n",status);
        return status;
    }
    printf("RF_Power_Control [SUCCEED] %\n",status);

    status = LEDBuzzer(reader, LED_OFF);

    // Close COM1
    status = CloseCOM1(reader);
    if (status != MI_OK){
        printf("CloseCom [FAILED] %\n",status);
        return status;
    }
    printf("CloseCom [SUCCEED] %\n",status);

    connected=false;
    return status;
}

int ReaderManager::read(int sector,int block){
    unsigned char * KEY_ACCESS = getAccessKeyForSector(sector,false);

    status = Mf_Classic_Authenticate(reader, Auth_KeyA, FALSE, sector, KEY_ACCESS, 0);
    if (status != MI_OK){
        printf("Auth [FAILED]\n");
        return status;
    }
    printf("Auth [SUCCEED]\n");

    status = Mf_Classic_Read_Block(reader, FALSE, block, data, Auth_KeyB, 0);
    if (status != MI_OK){
        printf("Read_Block [FAILED]\n");
        return status;
    }
    printf("Read_Block [SUCCEED]\n");

    return status;
}

int ReaderManager::write(int sector,int block,char* value){
    // Changing data
    for(int k = 0; k <16; k++){
        data[k] = value[k];
    }

    unsigned char * KEY_ACCESS = getAccessKeyForSector(sector,true);

    status = Mf_Classic_Authenticate(reader, Auth_KeyB, FALSE, sector, KEY_ACCESS, 0);
    if (status != MI_OK){
        printf("Auth [FAILED]\n");
        return status;
    }
    printf("Auth [SUCCEED]\n");

    status = Mf_Classic_Write_Block(reader, FALSE, block, data, Auth_KeyB, 0);
    if (status != MI_OK){
        printf("Write_Block [FAILED]\n");
        return status;
    }
    printf("Write_Block [SUCCEED]\n");

    return status;
}

void ReaderManager::increment(int block){
    status = Mf_Classic_Authenticate(reader, Auth_KeyB, FALSE, 3, KEY_D, 0);
    status = Mf_Classic_Increment_Value(reader, FALSE, block, 1, block -1, Auth_KeyB, 0);
    status = Mf_Classic_Restore_Value(reader, FALSE, block -1, block, Auth_KeyB, 0);
}

void ReaderManager::decrement(int block){
    status = Mf_Classic_Authenticate(reader, Auth_KeyA, FALSE, 3, KEY_C, 0);
    status = Mf_Classic_Decrement_Value(reader, FALSE, block, 1, block -1, Auth_KeyA, 0);
    status = Mf_Classic_Restore_Value(reader, FALSE, block -1, block , Auth_KeyA, 0);
}

char* ReaderManager::getId(){
    char tmp[uid_len];
    for(int i=0;i<uid_len;i++){
        tmp[i]=(uid[i]==1)?'1':'0';
    }
    return tmp;
}

char* ReaderManager::getVersion(){
    return version;
}

/**
 * @brief ReaderManager::getData
 * @return value readable data
 */
char * ReaderManager::getData(){
    char value[block_size];
    for(int k = 0; k <block_size; k++){
        value[k]=data[k];
    }
    return value;
}

/**
 * @brief ReaderManager::isConnected
 * @return bool
 */
bool ReaderManager::isConnected(){
    return this->connected;
}

/**
 * @brief ReaderManager::getAccessKeyForSector
 * @param sector
 * @param writeAccess
 * @return char* return key for sector depending on access
 */
unsigned char* ReaderManager::getAccessKeyForSector(int sector,bool writeAccess){
    unsigned char *KEY_ACCESS;
    switch(sector){
    case 2 :
        // Use KEY_B
        KEY_ACCESS=(writeAccess)?KEY_B:KEY_A;
        break;
    case 3 :
        // Use KEY_D
        KEY_ACCESS=KEY_D;
        break;
    default :
        KEY_ACCESS=KEY_FAKE;
        break;
    }
    return KEY_ACCESS;
}
