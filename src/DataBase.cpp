//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "DataBase.h"
#include "Platform.h"
#include "Pss21.h"
#include "DataStore.h"
#include <cstddef>


////-----------------------------------------------------------------------------------------------------
//CDataBase::CDataBase()
//{
////    m_pxDataStore = new CDataStore();
//}
//
////-----------------------------------------------------------------------------------------------------
//CDataBase::~CDataBase()
//{
////    delete m_pxDataStore;
//}

//-----------------------------------------------------------------------------------------------------
uint8_t CDataBase::RestoreDefault(void)
{
    // Восстановим БД по умолчанию.
    CDataStore::Init();

    enum
    {
        IDDLE = 0,
        BLOCK_WRITE_START,
        BLOCK_WRITE_END_WAITING,
        BLOCK_ERROR,
        ALL_BLOCKS_WRITED,
    };

    uint8_t uiBlockCounter = 0;
    uint8_t uiFsmState = BLOCK_WRITE_START;

    while (1)
    {
        switch (uiFsmState)
        {
        case BLOCK_WRITE_START:
            // Записаны не все блоки?
            if (uiBlockCounter < GetBlocksNumber())
            {
                // Скопируем данные из флеш во временный буфер,
                uint16_t uiLength = CDataStore::ReadBlockFlash(CPss21::m_auiIntermediateBuff, uiBlockCounter);
                // Блок не повреждён?
                if (uiLength)
                {
                    // Поместим данные в хранилище.
                    // Блок БД принят к записи?
                    if (CDataStore::WriteBlock(CPss21::m_auiIntermediateBuff,
                                               uiLength,
                                               uiBlockCounter + CDataStore::BLOCKS_CONTROL_DATA_BLOCK_NUMBER))
                    {
                        uiFsmState = BLOCK_WRITE_END_WAITING;
                    }
                    // При записи блока БД произошла ошибка?
                    else if (CDataStore::GetFsmEvent() == CDataStore::WRITE_ERROR_FSM_EVENT)
                    {
                        uiFsmState = BLOCK_ERROR;
                    }
                }
                else
                {
                    uiFsmState = BLOCK_ERROR;
                }
            }
            else
            {
                uiFsmState = ALL_BLOCKS_WRITED;
            }

            break;

        case BLOCK_WRITE_END_WAITING:
            // Блок записан успешно?
            if (CDataStore::GetFsmEvent() == CDataStore::WRITE_OK_FSM_EVENT)
            {
                uiBlockCounter++;
                uiFsmState = BLOCK_WRITE_START;
            }
            // При записи блока БД произошла ошибка?
            else if (CDataStore::GetFsmEvent() == CDataStore::WRITE_ERROR_FSM_EVENT)
            {
                uiFsmState = BLOCK_ERROR;
            }
            break;

        case ALL_BLOCKS_WRITED:
            return 1;
            break;

        case BLOCK_ERROR:
            return 0;
            break;

        default:
            break;
        }

        CDataStore::Fsm();

        delay_ms(10);

        CPlatform::WatchdogReset();
    }
}

//-----------------------------------------------------------------------------------------------------
bool CDataBase::IntegrityCheck(void)
{
    // Crc блока совпадает с его Crc сохранённом в служебном блоке?
    return CDataStore::CompareCurrentWithStoredCrc();
}

//-----------------------------------------------------------------------------------------------------
void CDataBase::SignatureCreate(void)
{
    // Создадим Crc из Crc всех блоков.
    CDataStore::CrcOfBlocksCrcCreate();
}

//-----------------------------------------------------------------------------------------------------
bool CDataBase::SignatureCheck(void)
{
    // Crc из Crc всех блоков совпадает?
    return CDataStore::CrcOfBlocksCrcCheck();
}

//-----------------------------------------------------------------------------------------------------
uint8_t CDataBase::Check(void)
{
    CPss21::SetErrorCode(NO_ERROR);
    // Блоки базы данных не повреждены?
    if (CDataStore::Check())
    {
        // Все блоки принадлежат текущей базе данных?
        if (IntegrityCheck())
        {
            // База данных подтверждена пользователем?
            if (SignatureCheck())
            {
                return 1;
            }
            else
            {
                CPss21::SetErrorCode(DB_ERROR);
                return 0;
            }
        }
        else
        {
            CPss21::SetErrorCode(DB_ERROR);
            // Восстановим БД по умолчанию.
            // БД по умолчанию восстановлена успешно?
            RestoreDefault();
            return 0;
        }
    }
    else
    {
        CPss21::SetErrorCode(DB_ERROR);
        // Восстановим БД по умолчанию.
        // БД по умолчанию восстановлена успешно?
        RestoreDefault();
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------
uint16_t CDataBase::ReadBlock(uint8_t *puiDestination, uint8_t uiBlock)
{
    return CDataStore::ReadBlock(puiDestination,
                                 uiBlock + (CDataStore::BLOCKS_CONTROL_DATA_BLOCK_NUMBER));
}

//-----------------------------------------------------------------------------------------------------
uint16_t CDataBase::WriteBlock(uint8_t *puiSource, uint8_t uiBlock)
{
    return CDataStore::WriteBlock(puiSource,
                                  GetBlockLength(uiBlock),
                                  uiBlock + (CDataStore::BLOCKS_CONTROL_DATA_BLOCK_NUMBER));
}

//-----------------------------------------------------------------------------------------------------
uint16_t CDataBase::GetBlockLength(uint8_t uiBlock)
{
    // Блок существует?
    if (uiBlock < GetBlocksNumber())
    {
        return CDataStore::GetBlockLength(uiBlock + CDataStore::BLOCKS_CONTROL_DATA_BLOCK_NUMBER);
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------
