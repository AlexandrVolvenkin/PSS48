//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
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

//    CDataBase();
//    virtual ~CDataBase();
    static uint8_t Check(void);
    static uint8_t RestoreDefault(void);
    static bool IntegrityCheck(void);
    static void SignatureCreate(void);
    static bool SignatureCheck(void);
    static uint16_t ReadBlock(uint8_t * , uint8_t );
    static uint16_t WriteBlock(uint8_t *puiSource, uint8_t uiBlock);
    static uint16_t GetBlockLength(uint8_t uiBlock);
    static uint8_t GetBlocksNumber(void)
    {
        return TDataBase::BLOCKS_QUANTITY;
    };

protected:
private:

};

//-----------------------------------------------------------------------------------------------------
#endif // CDATABASE_H
