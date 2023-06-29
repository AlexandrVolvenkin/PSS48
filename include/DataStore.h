//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CDATASTORE_H
#define CDATASTORE_H

#include <stdint.h>
#include "Platform.h"
#include "DataTypes.h"
#include "Dfa.h"
#include "Timer.h"

//-----------------------------------------------------------------------------------------------------
class CDataStore// : public CDfa
{
public:
//    CDataStore();
//    virtual ~CDataStore();
    static void Init(void);
    static uint16_t ReadBlock(uint8_t * , uint8_t );
    static bool WriteBlock(uint8_t * , uint16_t , uint8_t );
    static uint16_t Write(uint8_t *puiSource, uint16_t uiLength, uint8_t uiBlock);
    static uint8_t Check(void);
    static bool CompareCurrentWithStoredCrc(void);
    static void CrcOfBlocksCrcCreate(void);
    static bool CrcOfBlocksCrcCheck(void);
    static void Fsm(void);
    static uint16_t ReadBlockFlash(uint8_t *puiDestination, uint8_t uiBlock);

    static uint8_t GetBlockLength(uint8_t uiBlock)
    {
        return m_xBlocksControlData.
               axBlockPositionData[uiBlock].uiLength;
    };

    static uint8_t GetFsmEvent(void)
    {
        return m_uiFsmEvent;
    };

    enum
    {
        // Нулевой байт может быть стёрт при сбое питания.
        BLOCKS_CONTROL_DATA_BEGIN = 16,
        BLOCKS_CONTROL_DATA_BLOCK_NUMBER = 1,
        MAX_BLOCKS_NUMBER = (TDataBase::BLOCKS_QUANTITY + BLOCKS_CONTROL_DATA_BLOCK_NUMBER),
        // Сохраняемый буфер должен быть на CRC_LENGTH больше.
        CRC_LENGTH = 2,
    };

    enum
    {
        BLOCKS_CONTROL_DATA = 0,
        READY_TO_WRITE_WAITING_TIMEOUT = 200,
        WRITE_END_WAITING_TIMEOUT = 10000,
    };

    enum
    {
        IDDLE = 0,
        START_WRITE,
        READY_TO_WRITE_WAITING,
        WRITE_END_WAITING,

        START_WRITE_BLOCKS_CONTROL_DATA,
        READY_TO_WRITE_WAITING_BLOCKS_CONTROL_DATA,
        WRITE_END_WAITING_BLOCKS_CONTROL_DATA,
    };

    enum
    {
        NO_EVENT_FSM_EVENT = 0,
        WRITE_IN_PROGRESS_FSM_EVENT,
        STORAGE_DEVICE_BUSY_FSM_EVENT,
        WRITE_OK_FSM_EVENT,
        WRITE_ERROR_FSM_EVENT,
    };

protected:
private:
    static CTimer* GetTimerPointer(void)
    {
        return &m_xTimer;
    };

    static void SetFsmState(uint8_t uiData)
    {
        m_uiFsmState = uiData;
    };
    static uint8_t GetFsmState(void)
    {
        return m_uiFsmState;
    };

    static void SetFsmEvent(uint8_t uiData)
    {
        m_uiFsmEvent = uiData;
    };

    struct TBlockPositionData
    {
        uint16_t uiOffset;
        uint16_t uiLength;
        uint16_t uiEncodedLength;
        uint16_t uiCrc;
    };

    struct TBlocksControlData
    {
        // Контрольная сумма вычисленная из массива контрольных сумм блоков, не включая служебный.
        // Сохраняется при первой и последующих записях любых блоков через программатор.
        // Ноль или её несовпадение свидетельствует о том, что база данных создана по умоланию,
        // и не подтверждена пользователем. В этом случае прибор переходит в режим сигнализации об ошибке,
        // ожидая квитирования или записи базы данных.
        uint16_t uiCrcOfBlocksCrc;
        uint16_t uiFreeSpaceOffset;
        TBlockPositionData axBlockPositionData[MAX_BLOCKS_NUMBER];
    };

    // Служебные данные системы хранения.
    static TBlocksControlData m_xBlocksControlData;
    // Массив контрольных сумм блоков.
    static uint16_t m_auiBlocksCurrentCrc[MAX_BLOCKS_NUMBER];
    static uint8_t* m_puiIntermediateBuff;
    static CTimer m_xTimer;
    static uint8_t m_uiFsmState;
    static uint8_t m_uiFsmEvent;
};

//-----------------------------------------------------------------------------------------------------
#endif // CDATASTORE_H
