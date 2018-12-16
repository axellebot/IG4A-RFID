#include <stdint-gcc.h>
#if (defined(UNDER_CE) || defined(_WIN32_WCE))
    /* WinCE is only a subset of Win32 */
    #ifndef WIN32
        #define WIN32
    #endif
    #ifndef WINCE
        #define WINCE
    #endif
#endif

#if (defined (_WIN32))
    #ifndef WIN32
        #define WIN32
    #endif
#endif

#ifdef WIN32

  /* Win32 code */
  /* ---------- */

    #include <windows.h>
    //#include <tchar.h>
    //#include "types.h"

    //typedef signed short SWORD;
    //typedef signed long  SDWORD;

    #ifndef ODALID_LIB
        #if (defined (__GNUC__))
            #define ODALID_LIB
        #else
            #define ODALID_LIB __declspec(dllimport)
        #endif
    #endif

    #if (defined(WINCE))
        /* Under Windows CE we use the stdcall calling convention */
        #define ODALID_API __stdcall
    #else
        #if (defined(FORCE_STDCALL))
        /* stdcall is forced */
            #define ODALID_API __stdcall
        #else
            /* cdecl is the default calling convention */
            #define ODALID_API __cdecl
        #endif
    #endif
#else

  /* Not Win32 */
  /* --------- */

  /* Linkage directive : not specified, use compiler default */
    #define ODALID_API

  /* Calling convention : not specified, use compiler default */
    #define ODALID_LIB

    #include <stdint.h>
    #include <stddef.h>
    typedef uint8_t BOOL;

    #ifndef TRUE
        #define TRUE 1
    #endif
    #ifndef FALSE
        #define FALSE 0
    #endif

    #ifdef HAVE_TCHAR_H
        #include <tchar.h>
    #else
        #ifdef UNICODE
            typedef wchar_t TCHAR;
        #else
            typedef char TCHAR;
        #endif
    #endif
#endif

#if defined (__cplusplus)
extern "C" {
#endif

typedef struct {
    uint8_t Type;
    uint8_t device;
    char IPReader[16];
}ReaderName;

#define ReaderTCP           1
#define ReaderCDC           2
#define ReaderPCSC          3

ODALID_LIB int16_t OpenCOM1(ReaderName *Name);
ODALID_LIB int16_t CloseCOM1(ReaderName *Name);

ODALID_LIB int16_t OpenCOMTCP(char *IPReader);
ODALID_LIB int16_t CloseCOMTCP(void);
ODALID_LIB int16_t OpenCOMCDC(uint8_t *device);
ODALID_LIB int16_t CloseCOMCDC(void);

#define LED_ON              0x07
#define LED_OFF             0x00
#define LED_GREEN_OFF       0x00
#define LED_GREEN_ON        0x04
#define LED_YELLOW_OFF      0x00
#define LED_YELLOW_ON       0x02
#define LED_RED_OFF         0x00
#define LED_RED_ON          0x01
#define BUZZER_OFF          0x00
#define BUZZER_ON           0x08

#define TypeA          0x01
#define TypeB          0x02
#define TypeCTS        0x08
#define TypeST         0x10
#define TypeInno       0x20
#define Type15693      0x40

ODALID_LIB char* GetErrorMessage(int16_t status);
ODALID_LIB int16_t GetLibrary(char *recv, uint16_t *len_recv);
ODALID_LIB int16_t Version(ReaderName *Name, char *version, uint8_t *serial, char *stack);
ODALID_LIB int16_t Get_Property(ReaderName *Name, uint8_t AddReg, uint8_t *Reg);
ODALID_LIB int16_t Set_Property(ReaderName *Name, uint8_t AddReg, uint8_t Reg);
ODALID_LIB int16_t RF_Power_Control(ReaderName *Name, BOOL RFOnOff, uint8_t Delay);
ODALID_LIB int16_t RF_Find(ReaderName *Name, uint8_t Type, uint8_t *TypeFind, uint8_t *uid, uint16_t *uid_len, uint8_t *info, uint16_t *info_len);
ODALID_LIB int16_t RF_Config_Card_Mode(ReaderName *Name, uint8_t Type);
ODALID_LIB int16_t RF_Transmit(ReaderName *Name, uint8_t *send, uint16_t *len_send, uint8_t *recv, uint16_t *len_recv, uint16_t timeout);
ODALID_LIB int16_t LEDBuzzer(ReaderName *Name, uint8_t LEDBuzzer);
ODALID_LIB int16_t LCD(ReaderName *Name, uint8_t line, char *send);



ODALID_LIB int16_t ISO14443_3_A_PollCard(ReaderName *Name, uint8_t *atq, uint8_t *sak, uint8_t *uid, uint16_t *uid_len);
ODALID_LIB int16_t ISO14443_3_A_PollCardWU(ReaderName *Name, uint8_t *atq, uint8_t *sak, uint8_t *uid, uint16_t *uid_len);
ODALID_LIB int16_t ISO14443_3_A_Halt(ReaderName *Name);

ODALID_LIB int16_t ISO14443_3_B_PollCard(ReaderName *Name, uint8_t afi, uint8_t param, uint8_t *CID, uint8_t *atqb, uint16_t *atqb_len);
ODALID_LIB int16_t ISO14443_3_B_Halt(ReaderName *Name, uint8_t *PUPI);

ODALID_LIB int16_t ISO14443_4_A_RATS(ReaderName *Name, uint8_t CID, uint8_t *ats, uint16_t *Len_ats);
ODALID_LIB int16_t ISO14443_4_A_PPS(ReaderName *Name, uint8_t CID, uint8_t dsi, uint8_t dri);
ODALID_LIB int16_t ISO14443_4_Deselect(ReaderName *Name, uint8_t Type);

ODALID_LIB int16_t ISO14443_4_Transparent(ReaderName *Name, uint8_t Type, uint8_t CID, uint8_t NAD, uint8_t *CmdADPU, uint16_t lenCmdADPU, uint8_t *RespADPU, uint16_t *lenRespADPU);

ODALID_LIB int16_t CTS_PollCard(ReaderName *Name, uint8_t *code, uint8_t *serial);

ODALID_LIB int16_t SR_PollCard(ReaderName *Name, uint8_t *cid, uint8_t *uid);
ODALID_LIB int16_t SR_Completion(ReaderName *Name);

ODALID_LIB int16_t INNOVATRON_PollCard(ReaderName *Name, uint8_t *div, uint8_t *atr, uint8_t *atr_len);
ODALID_LIB int16_t INNOVATRON_DISC(ReaderName *Name);

ODALID_LIB int16_t ISO15693_PollCard(ReaderName *Name, uint8_t *DSFID, uint8_t *uid);

//Valid access conditions for bc0, bc1 and bc2
#define ACC_BLOCK_TRANSPORT     0x00
#define ACC_BLOCK_READWRITE     0x04
#define ACC_BLOCK_VALUE         0x06
//Valid access conditions for bc3
#define ACC_AUTH_TRANSPORT      0x01
#define ACC_AUTH_NORMAL         0x03

#define Auth_KeyA				TRUE
#define Auth_KeyB				FALSE

ODALID_LIB int16_t Mf_Classic_LoadKey(ReaderName *Name, BOOL Auth_Key, uint8_t *key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Authenticate(ReaderName *Name, BOOL Auth_Key, BOOL internal_Key, uint8_t sector, uint8_t *key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Read_Block(ReaderName *Name, BOOL auth, uint8_t block, uint8_t *Data, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Write_Block(ReaderName *Name, BOOL auth, uint8_t block, uint8_t *Data, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Read_Sector(ReaderName *Name, BOOL auth, uint8_t sector, uint8_t *Data, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Write_Sector(ReaderName *Name, BOOL auth, uint8_t sector, uint8_t *Data, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_UpdadeAccessBlock(ReaderName *Name, BOOL auth, uint8_t sector, uint8_t old_key_index, uint8_t *new_key_A, uint8_t *new_key_B, uint8_t bc0, uint8_t bc1, uint8_t bc2, uint8_t bc3, BOOL Auth_Key);
ODALID_LIB int16_t Mf_Classic_Read_Value(ReaderName *Name, BOOL auth, uint8_t block, uint32_t *value,  BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Write_Value(ReaderName *Name, BOOL auth, uint8_t block, uint32_t value, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Increment_Value(ReaderName *Name, BOOL auth, uint8_t block, uint32_t valeur, uint8_t trans_block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Decrement_Value(ReaderName *Name, BOOL auth, uint8_t block, uint32_t valeur, uint8_t trans_block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t Mf_Classic_Restore_Value(ReaderName *Name, BOOL auth, uint8_t block, uint8_t trans_block, BOOL Auth_Key, uint8_t key_index);


ODALID_LIB int16_t Mf_Plus_Authenticate_SL1(ReaderName *Name, uint8_t *KeyBNr);
ODALID_LIB int16_t Mf_Plus_CommitPerso_SL0(ReaderName *Name);


typedef struct
{
    uint8_t bHwVendorID;
    uint8_t bHwType;
    uint8_t bHwSubType;
    uint8_t bHwMajorVersion;
    uint8_t bHwMinorVersion;
    uint8_t bHwStorageSize;
    uint8_t bHwProtocol;
    uint8_t bSwVendorID;
    uint8_t bSwType;
    uint8_t bSwSubType;
    uint8_t bSwMajorVersion;
    uint8_t bSwMinorVersion;
    uint8_t bSwStorageSize;
    uint8_t bSwProtocol;
    uint8_t abUid[7];
    uint8_t abBatchNo[5];
    uint8_t bProductionCW;
    uint8_t bProductionYear;
} DF_VERSION_INFO;


typedef union
{
    struct
    {
        uint16_t eFileSize;
    } stDataFileSettings;

    struct
    {
        int32_t lLowerLimit;
        int32_t lUpperLimit;
        uint16_t eLimitedCredit;
        uint8_t bLimitedCreditEnabled;
    } stValueFileSettings;

    struct
    {
        uint16_t eRecordSize;
        uint16_t eMaxNRecords;
        uint16_t eCurrNRecords;
    } stRecordFileSettings;
} DF_ADDITIONAL_FILE_SETTINGS;

ODALID_LIB char* Mf_DESFire_GetErrorMessage(int16_t status);

//----------------------------Security related
ODALID_LIB int16_t Mf_DESFire_AuthenticateHostEV0(ReaderName *Name, uint8_t DFKeyNo, uint8_t *pAccessKey);
ODALID_LIB int16_t Mf_DESFire_AuthenticateHostEV1(ReaderName *Name, uint8_t DFKeyNo, uint8_t *pAccessKey);
ODALID_LIB int16_t Mf_DESFire_AutenticateSAMEV0(ReaderName *Name, uint8_t DFKeyNo, uint8_t SAMKeyNo, uint8_t SAMKeyV);
ODALID_LIB int16_t Mf_DESFire_AutenticateSAMEV1(ReaderName *Name, uint8_t DFKeyNo, uint8_t SAMKeyNo, uint8_t SAMKeyV);
ODALID_LIB int16_t Mf_DESFire_ChangeKeySettings(ReaderName *Name, uint8_t  key_settings);
ODALID_LIB int16_t Mf_DESFire_GetKeySettings(ReaderName *Name, uint8_t *DFKeySettings, uint8_t *DFMaxNoKey);
ODALID_LIB int16_t Mf_DESFire_ChangeKey(ReaderName *Name, uint8_t key_number, int8_t *new_key, int8_t *old_key);
ODALID_LIB int16_t Mf_DESFire_GetKeyVersion(ReaderName *Name, uint8_t KeyNumber, uint8_t *pKeyVersion);

//----------------------------Picc level command
ODALID_LIB int16_t Mf_DESFire_CreateApplication(ReaderName *Name, uint32_t aid, uint8_t Key1, uint8_t Key2);
ODALID_LIB int16_t Mf_DESFire_DeleteApplication(ReaderName *Name, uint32_t aid);
ODALID_LIB int16_t Mf_DESFire_GetApplicationIDs(ReaderName *Name, uint8_t aid_max_count, uint32_t *aid_list, uint8_t *aid_count);
ODALID_LIB int16_t Mf_DESFire_GetDFNames(ReaderName *Name);
ODALID_LIB int16_t Mf_DESFire_SelectApplication(ReaderName *Name, uint32_t aid);
ODALID_LIB int16_t Mf_DESFire_FormatPICC(ReaderName *Name);
ODALID_LIB int16_t Mf_DESFire_GetVersion(ReaderName *Name, DF_VERSION_INFO *pVersionInfo);
ODALID_LIB int16_t Mf_DESFire_FreeMem(ReaderName *Name, uint8_t *pFreeMem);
ODALID_LIB int16_t Mf_DESFire_SetConfiguration(ReaderName *Name, uint8_t *pFreeMem);
ODALID_LIB int16_t Mf_DESFire_GetCardUID(ReaderName *Name, uint8_t *pFreeMem);

//----------------------------application level
ODALID_LIB int16_t Mf_DESFire_GetFileIDs(ReaderName *Name, uint8_t *file_id, uint8_t nb_file_id);
ODALID_LIB int16_t Mf_DESFire_GetISOIDs(ReaderName *Name, uint8_t *file_id, uint8_t nb_file_id);
ODALID_LIB int16_t Mf_DESFire_GetFileSettings(ReaderName *Name, uint8_t file_id);
ODALID_LIB int16_t Mf_DESFire_ChangeFileSettings(ReaderName *Name, uint8_t file_id, uint8_t  com_mode, uint16_t  access_rights);
ODALID_LIB int16_t Mf_DESFire_CreateStdDataFile(ReaderName *Name, uint8_t File_No, uint8_t comm_mode, uint16_t access_rights, uint32_t file_size);
ODALID_LIB int16_t Mf_DESFire_CreateBackupDataFile(ReaderName *Name, uint8_t File_No, uint8_t comm_mode, uint16_t access_rights,uint32_t file_size);
ODALID_LIB int16_t Mf_DESFire_CreateValueFile(ReaderName *Name, uint8_t File_No, uint8_t comm_mode, uint16_t access_rights, uint32_t lower_limit, uint32_t upper_limit, uint32_t initial_value, uint8_t limited_credit_enabled);
//ODALID_LIB int16_t Mf_DESFire_CreatelinearRecordFile
ODALID_LIB int16_t Mf_DESFire_CreateCyclicRecordFile(ReaderName *Name, uint8_t File_No, uint8_t comm_mode, uint16_t access_rights, uint32_t record_size, uint32_t max_records);
ODALID_LIB int16_t Mf_DESFire_DeleteFile(ReaderName *Name, uint8_t File_No);

//----------------------------Data manipulation command
ODALID_LIB int16_t Mf_DESFire_ReadData(ReaderName *Name, uint8_t File_No,  uint8_t comm_mode, uint32_t Offset, uint32_t Lenght, uint8_t *Data);
ODALID_LIB int16_t Mf_DESFire_WriteData(ReaderName *Name, uint8_t File_No, uint8_t com_mode, uint32_t Offset, uint32_t Lenght, uint8_t *Data);
ODALID_LIB int16_t Mf_DESFire_Credit(ReaderName *Name, uint8_t File_No, uint8_t com_mode, uint32_t Value);
ODALID_LIB int16_t Mf_DESFire_Debit(ReaderName *Name, uint8_t File_No, uint8_t com_mode, uint32_t Value);
ODALID_LIB int16_t Mf_DESFire_LimitedCredit(ReaderName *Name, uint8_t File_No, uint8_t com_mode, uint32_t Value);
ODALID_LIB int16_t Mf_DESFire_GetValue(ReaderName *Name, uint8_t File_No, uint8_t com_mode, uint32_t *Value);
ODALID_LIB int16_t Mf_DESFire_ReadRecord(ReaderName *Name, uint8_t File_No,  uint8_t comm_mode, uint32_t Offset, uint32_t Lenght, uint8_t *Data);
ODALID_LIB int16_t Mf_DESFire_WriteRecord(ReaderName *Name, uint8_t File_No, uint8_t com_mode, uint32_t Offset, uint32_t Lenght, uint8_t *Data);
ODALID_LIB int16_t Mf_DESFire_CommitTransaction(ReaderName *Name);

///////////



ODALID_LIB int16_t SR176_ReadBlock(ReaderName *Name, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t SR176_WriteBlock(ReaderName *Name, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t SR176_GetUID(ReaderName *Name, uint8_t *UID);
ODALID_LIB int16_t SR176_GetProtection(ReaderName *Name, uint8_t *LockReg);
ODALID_LIB int16_t SR176_ProtectBlock(ReaderName *Name, uint8_t cid, uint8_t LockReg);

ODALID_LIB int16_t SRixK_ReadBlock(ReaderName *Name, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t SRixK_WriteBlock(ReaderName *Name, uint8_t block, uint8_t *Data);
ODALID_LIB int16_t SRixK_GetUID(ReaderName *Name, uint8_t *UID);

ODALID_LIB int16_t CTS_ReadBlock(ReaderName *Name, uint8_t block, uint8_t *Data);

ODALID_LIB int16_t ISO15693_ReadSingleBlock(ReaderName *Name, uint8_t *UID, uint8_t block, uint8_t *buffer);
ODALID_LIB int16_t ISO15693_WriteSingleBlock(ReaderName *Name, uint8_t *UID, uint8_t block, uint8_t *Data, uint8_t *buffer);
ODALID_LIB int16_t ISO15693_LockBblock(ReaderName *Name, uint8_t *UID, uint8_t block, uint8_t *buffer);
ODALID_LIB int16_t ISO15693_ReadMultipleBlocks(ReaderName *Name, uint8_t *UID, uint8_t start_block, uint8_t nbre_block, uint8_t *buffer);
ODALID_LIB int16_t ISO15693_WriteMultipleBlocks(ReaderName *Name, uint8_t *UID, uint8_t start_block, uint8_t nbre_block, uint8_t *Data, uint8_t *buffer);

typedef struct
{
    uint8_t Fci[127];
    uint8_t FciLen;
    uint8_t DFName[16];
    uint8_t DFNameLen;
    uint8_t FciPropierty[32];
    uint8_t FciPropiertyLen;
    uint8_t FciIssuer[19];
    uint8_t FciIssuerLen;
    uint8_t ASN[8];
    uint8_t ASNLen;
    uint8_t Data[7];
    uint8_t DataLen;
    uint8_t NumberModification;
    uint8_t Platform;
    uint8_t Type;
    uint8_t SubType;
    uint8_t SoftIssuer;
    uint8_t SoftVersion;
    uint8_t SoftRevision;
    uint8_t Revision;
    uint8_t UID[8];
    BOOL  SessionActive : 1;
    BOOL Invalidated : 1;
    BOOL WithStoredValue : 1;
    BOOL NeedRatificationFrame : 1;
    BOOL WithPin : 1;
    uint8_t SessionCurMods;
    uint8_t CurrentPin[4];
    uint8_t CurrentKif;
    uint8_t CurrentKvc;

}CALYPSO_INFO;

#define CALYPSO_MIN_SESSION_MODIFS 3
#define CALYPSO_MIN_RECORD_SIZE    29


#define CALYPSO_SFI_ENVIRONMENT         0x07
#define CALYPSO_SFI_CONTRACTS           0x09
#define CALYPSO_SFI_COUNTERS            0x19
#define CALYPSO_SFI_EVENTS_LOG          0x08
#define CALYPSO_SFI_SPECIAL_EVENTS      0x1D
#define CALYPSO_SFI_CONTRACTS_LIST      0x1E

#define CALYPSO_KEY_ISSUER         0x01
#define CALYPSO_KIF_ISSUER         0x21
#define CALYPSO_KNO_ISSUER         0x0C

#define CALYPSO_KEY_LOAD           0x02
#define CALYPSO_KIF_LOAD           0x27
#define CALYPSO_KNO_LOAD           0x02

#define CALYPSO_KEY_DEBIT          0x03
#define CALYPSO_KIF_DEBIT          0x30
#define CALYPSO_KNO_DEBIT          0x0D

#define CALYPSO_INS_GET_RESPONSE   0xC0
#define CALYPSO_INS_SELECT         0xA4
#define CALYPSO_INS_INVALIDATE     0x04
#define CALYPSO_INS_REHABILITATE   0x44
#define CALYPSO_INS_APPEND_RECORD  0xE2
#define CALYPSO_INS_DECREASE       0x30
#define CALYPSO_INS_INCREASE       0x32
#define CALYPSO_INS_READ_BINARY    0xB0
#define CALYPSO_INS_READ_RECORD    0xB2
#define CALYPSO_INS_UPDATE_BINARY  0xD6
#define CALYPSO_INS_UPDATE_RECORD  0xDC
#define CALYPSO_INS_WRITE_RECORD   0xD2
#define CALYPSO_INS_OPEN_SESSION   0x8A
#define CALYPSO_INS_CLOSE_SESSION  0x8E
#define CALYPSO_INS_GET_CHALLENGE  0x84
#define CALYPSO_INS_CHANGE_PIN     0xD8
#define CALYPSO_INS_VERIFY_PIN     0x20

#define CALYPSO_INS_SV_GET         0x7C
#define CALYPSO_INS_SV_DEBIT       0xBA
#define CALYPSO_INS_SV_RELOAD      0xB8
#define CALYPSO_INS_SV_UN_DEBIT    0xBC

#define CALYPSO_INS_SAM_SV_DEBIT   0x54
#define CALYPSO_INS_SAM_SV_RELOAD  0x56


//ODALID_LIB int16_t Calypso_GetResponse(ReaderName *Name, uint8_t Type, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t Calypso_SelectApplication(ReaderName *Name, uint8_t Type, uint8_t *AID, uint8_t AID_len, CALYPSO_INFO *pInfo_Card);

ODALID_LIB int16_t Calypso_AppendRecord(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t sfi, uint8_t *Sam_Challenge, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t Calypso_Decrease(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint32_t DecValue, uint32_t *NewValue);
//ODALID_LIB int16_t Calypso_DecreaseMultiple(ReaderName *Name, uint8_t Type, uint8_t sfi, uint32_t DecValue);
ODALID_LIB int16_t Calypso_Increase(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint32_t IncValue, uint32_t *NewValue);
//ODALID_LIB int16_t Calypso_IncreaseMultiple(ReaderName *Name, uint8_t Type, uint8_t sfi, uint32_t DecValue);
ODALID_LIB int16_t Calypso_ReadRecord(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint8_t rec_size, uint8_t *Data, uint16_t *Datalen);
ODALID_LIB int16_t Calypso_UpdateRecord(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t Calypso_WriteRecord(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t rec_no, uint8_t sfi, uint8_t rec_size, uint8_t *Data, uint8_t Datalen);

ODALID_LIB int16_t Calypso_OpenSecureSession1(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t kvc, uint8_t rec_no, uint8_t sfi, uint8_t *Sam_Challenge, uint8_t *Card_Challenge, uint8_t *Ratification, uint8_t *Resp, uint16_t *Resplen, uint8_t *Data, uint16_t *Datalen);
ODALID_LIB int16_t Calypso_OpenSecureSession2(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t kvc, uint8_t rec_no, uint8_t sfi, uint8_t *Sam_Challenge, uint8_t *Card_Challenge, uint8_t *Ratification, uint8_t *Resp, uint16_t *Resplen, uint8_t *Data, uint16_t *Datalen, uint8_t *kvc_resp);
ODALID_LIB int16_t Calypso_OpenSecureSession3(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, uint8_t kvc, uint8_t rec_no, uint8_t sfi, uint8_t *Sam_Challenge, uint8_t *Card_Challenge, uint8_t *Ratification, uint8_t *Resp, uint16_t *Resplen, uint8_t *Data, uint16_t *Datalen, uint8_t *kvc_resp, uint8_t *kif_resp);
ODALID_LIB int16_t Calypso_CloseSecureSession(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card, BOOL ratify_now, uint8_t *Sam_Sign, uint8_t *Resp, uint16_t *Resplen);
ODALID_LIB int16_t Calypso_Invalidate(ReaderName *Name, uint8_t Type, CALYPSO_INFO *pInfo_Card);

#define TypeISO         0x00
#define TypeISO_T0      0x00
#define TypeISO_T1      0x01
#define TypeHSP         0x02

typedef struct
{
    uint16_t RXDataLEN;		// Recieved Data length from smart card(excluding SW1 and SW2 bytes)
    uint8_t SW1;          	// Status byte 1
    uint8_t SW2;          	// Status byte 2
} SC_APDU_RESPONSE;

ODALID_LIB int16_t SAM_Config_Card_Mode(ReaderName *Name, uint8_t Type);
ODALID_LIB int16_t SAM_SelectSlot(ReaderName *Name, uint8_t Slot);
ODALID_LIB int16_t SAM_GetATR(ReaderName *Name, uint8_t *atr, uint16_t *atrlen);
ODALID_LIB int16_t SAM_Transmit(ReaderName *Name, uint8_t *send, uint16_t *len_send, uint8_t *recv, SC_APDU_RESPONSE* apduResponse, uint16_t timeout);

ODALID_LIB int16_t SAM_AV2_GetVersion(ReaderName *Name, uint8_t *pVersion);
ODALID_LIB int16_t SAM_AV2_GetKeyEntry(ReaderName *Name, uint8_t KeyNo);
ODALID_LIB int16_t SAM_AV2_GetKUCEntry(ReaderName *Name, uint8_t RefNoKUC);
ODALID_LIB int16_t SAM_AV2_ChangeKey_PICC(ReaderName *Name, uint8_t KeyCompMode, uint8_t KeyNoOld, uint8_t KeyVKeyOld, uint8_t KeyNoNew, uint8_t KeyVKeyNew, uint8_t *uid);

ODALID_LIB int16_t SAM_Calypso_SelectDiversifer(ReaderName *Name, uint8_t *UID);
ODALID_LIB int16_t SAM_Calypso_GetChallenge(ReaderName *Name, uint8_t *Challenge);
ODALID_LIB int16_t SAM_Calypso_DigestInit(ReaderName *Name, int8_t kif, uint8_t kvc, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t SAM_Calypso_DigestInitOld(ReaderName *Name, uint8_t key, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t SAM_Calypso_DigestUpdate(ReaderName *Name, uint8_t *Data, uint8_t Datalen);
ODALID_LIB int16_t SAM_Calypso_DigestClose(ReaderName *Name, uint8_t *SignHi);
ODALID_LIB int16_t SAM_Calypso_DigestAuthenticate(ReaderName *Name, uint8_t *SignLo);

ODALID_LIB uint8_t ByteToBcd(uint8_t input);
ODALID_LIB uint8_t BcdToByte(uint8_t input);

#define SECURITY_OPEN                           (0)
#define SECURITY_WEP_40                         (1)
#define SECURITY_WEP_104                        (2)
#define SECURITY_WPA_WPA2                       (8)

ODALID_LIB int16_t Wifi_Config(ReaderName *Name, uint8_t SecurityMode, uint8_t SsidLength, uint8_t *SSID, uint8_t SecurityKeyLength, uint8_t *SecurityKey);

#define Inc_Value				TRUE
#define Dec_Value				FALSE

ODALID_LIB int16_t AutoReader_SetRTC(ReaderName *Name, BOOL TimeHost, uint8_t *Time);
ODALID_LIB int16_t AutoReader_DeleteUser(ReaderName *Name, uint8_t *User);
ODALID_LIB int16_t AutoReader_AddUser(ReaderName *Name, uint8_t *User);
ODALID_LIB int16_t AutoReader_ClearFullUser(ReaderName *Name);
ODALID_LIB int16_t AutoReader_LoadKeyMifare(ReaderName *Name, BOOL Auth_Key, uint8_t *key, uint8_t key_index);
ODALID_LIB int16_t AutoReader_AccessMifare(ReaderName *Name, uint8_t Block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t AutoReader_ComptMifare(ReaderName *Name, uint8_t Block, BOOL Auth_Key, uint8_t key_index, BOOL Compt, uint32_t Value);
ODALID_LIB int16_t AutoReader_AfficheValueMifare(ReaderName *Name, uint8_t Block, BOOL Auth_Key, uint8_t key_index);
ODALID_LIB int16_t AutoReader_TempoGache(ReaderName *Name, uint8_t Temps);
ODALID_LIB int16_t AutoReader_BlackList(ReaderName *Name, BOOL BlackList);
ODALID_LIB int16_t AutoReader_SendInfo(ReaderName *Name, BOOL SendInfo, uint8_t *IPServeur, uint16_t Port);
ODALID_LIB int16_t AutoReader_LCD1(ReaderName *Name, BOOL option, uint8_t *LCD);
ODALID_LIB int16_t AutoReader_LCD2A(ReaderName *Name, BOOL option, uint8_t *LCD);
ODALID_LIB int16_t AutoReader_LCD2B(ReaderName *Name, BOOL option, uint8_t *LCD);
ODALID_LIB int16_t AutoReader_LCD2C(ReaderName *Name, BOOL option, uint8_t *LCD);
ODALID_LIB int16_t AutoReader_Download(ReaderName *Name, uint16_t PremierDownload, uint8_t NbreDownload, uint8_t *Data, uint16_t *Datalen);
ODALID_LIB int16_t AutoReader_Download_FULL(ReaderName *Name, BOOL ClearSave, char *FilePath);
ODALID_LIB int16_t AutoReader_ClearSave(ReaderName *Name);
ODALID_LIB int16_t AutoReader_NbreSave(ReaderName *Name, uint16_t *NbreSave);

#if defined (__cplusplus)
}
#endif
