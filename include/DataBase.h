//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CDATABASE_H
#define CDATABASE_H

#include <stdint.h>
#include "DataStore.h"

//-----------------------------------------------------------------------------------------------------
class CDataBase
{
public:

    CDataBase();
    virtual ~CDataBase();
    static uint8_t Check(void);
    static uint8_t RestoreDefault(void);
    static bool IntegrityCheck(void);
    static bool UserConfirmationCheck(void);
    static uint16_t Read(uint8_t * , uint8_t );
    static uint16_t Write(uint8_t *puiSourse, uint16_t uiLength, uint8_t uiBlock);
    static void SetStatus(uint8_t uiData)
    {
        m_uiStatus = uiData;
    };
    static uint8_t GetStatus(void)
    {
        return m_uiStatus;
    };
    static uint8_t GetBlockLength(uint8_t uiBlock);
    static uint16_t GetBlockOffset(uint8_t uiBlock);

protected:
private:

    static __flash TDataBaseBlockPositionData  axDataBaseBlocksPositionData[];
    static uint8_t m_uiStatus;
    static TDataBase __farflash *m_pxDataBase;
    static struct TDataBaseBlockPositionData __farflash *m_pxDataBaseBlocksPositionData;

};

//-----------------------------------------------------------------------------------------------------
#endif // CDATABASE_H
