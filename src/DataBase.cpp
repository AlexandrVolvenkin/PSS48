//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
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
    uint8_t __farflash *puiDataBase;

    CPss21::m_xDataStore.Init();

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
            if (uiBlockCounter < TDataBase::BLOCKS_QUANTITY)
            {
                // Скопируем данные из флеш во временный буфер,
                uint16_t uiLength = CPss21::m_xDataStore.ReadBlockFlash(CPss21::m_auiIntermediateBuff, uiBlockCounter);

                // Поместим данные в хранилище.
                // Блок БД принят к записи?
                if (Write(CPss21::m_auiIntermediateBuff, uiLength, uiBlockCounter))
                {
                    uiFsmState = BLOCK_WRITE_END_WAITING;
                }
                // При записи блока БД произошла ошибка?
                else if (CPss21::m_xDataStore.GetFsmEvent() == CDataStore::WRITE_ERROR_FSM_EVENT)
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
            if (CPss21::m_xDataStore.GetFsmEvent() == CDataStore::WRITE_OK_FSM_EVENT)
            {
                uiBlockCounter++;
                uiFsmState = BLOCK_WRITE_START;
            }
            // При записи блока БД произошла ошибка?
            else if (CPss21::m_xDataStore.GetFsmEvent() == CDataStore::WRITE_ERROR_FSM_EVENT)
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

        CPss21::m_xDataStore.Fsm();

        delay_ms(10);

        CPlatform::WatchdogReset();
    }
}

//-----------------------------------------------------------------------------------------------------
bool CDataBase::IntegrityCheck(void)
{
    // Все блоки принадлежат текущей базе данных?
    return CPss21::m_xDataStore.CompareCurrentWithStoredCrc();
}

//-----------------------------------------------------------------------------------------------------
void CDataBase::SignatureCreate(void)
{
    // Создадим Crc из Crc всех блоков.
    CPss21::m_xDataStore.CrcOfBlocksCrcCreate();
}

//-----------------------------------------------------------------------------------------------------
bool CDataBase::SignatureCheck(void)
{
    // Crc из Crc всех блоков совпадает?
    return CPss21::m_xDataStore.CrcOfBlocksCrcCheck();
}

//-----------------------------------------------------------------------------------------------------
uint8_t CDataBase::Check(void)
{
//    m_pxDataBase = &xMainDataBase;
//    m_pxDataBaseBlocksPositionData = axDataBaseBlocksPositionData;

    CPss21::SetErrorCode(NO_ERROR);
    // Блоки базы данных не повреждены?
    if (CPss21::m_xDataStore.Check())
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
uint16_t CDataBase::Read(uint8_t *puiDestination, uint8_t uiBlock)
{
    return CPss21::m_xDataStore.ReadBlock(puiDestination,
                                          uiBlock + (CDataStore::BLOCKS_CONTROL_DATA_BLOCK_NUMBER));
}

//-----------------------------------------------------------------------------------------------------
uint16_t CDataBase::Write(uint8_t *puiSourse, uint16_t uiLength, uint8_t uiBlock)
{
    return CPss21::m_xDataStore.Write(puiSourse,
                                      uiLength,
                                      uiBlock + (CDataStore::BLOCKS_CONTROL_DATA_BLOCK_NUMBER));
}

//-----------------------------------------------------------------------------------------------------
uint16_t CDataBase::GetBlockLength(uint8_t uiBlock)
{
    return CPss21::m_xDataStore.GetBlockLength(uiBlock + CDataStore::BLOCKS_CONTROL_DATA_BLOCK_NUMBER);
}

//-----------------------------------------------------------------------------------------------------
