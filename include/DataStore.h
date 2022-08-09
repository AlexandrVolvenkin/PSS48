//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
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
class CDataStore : public CDfa
{
public:

    enum
    {
        EEPROM_CONTEXT_BEGIN = 0,
        // Нулевой байт может быть стёрт при сбое питания.
        BLOCKS_CONTROL_DATA_BEGIN = 16,
        BLOCKS_CONTROL_DATA_BLOCK_NUMBER = 1,
        MAX_BLOCKS_NUMBER = (TDataBase::BLOCKS_QUANTITY + BLOCKS_CONTROL_DATA_BLOCK_NUMBER),
        // Сохраняемый буфер должен быть на CRC_LENGTH больше.
        CRC_LENGTH = 2,
        // Контрольная сумма в коде Хемминга занимает 3 байта.
        CRC_LENGTH_3 = 3,
        // Количество байт служебного контекста
        // должно быть известно заранее.
        // Так как по нему извлекаются начальные данные.
        // Используется самовосстанавливающийся код Хемминга(8,4).
        // Коэффициент - 1.5: один байт преобразуется в кодовое слово 12 бит,
        // из двух байт полезных данных получается три байта кодированных.
        // (((sizeof(struct TBlocksControlData)) * 1.5) = 57)
//        BLOCKS_CONTROL_DATA_LENGTH = 75,//57,//((sizeof(struct TBlocksControlData)) * 1.5),
        BLOCKS_CONTROL_DATA_LENGTH = 153,//114,//78,//57,//(((sizeof(struct TBlocksControlData) + CRC_LENGTH) * 1.5)),
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
        // Ноль или её не совпадение свидетельствует о том, что база данных создана по умоланию,
        // и не подтверждена пользователем. В этом случае прибор переходит в режим сигнализации об ошибке,
        // ожидая квитирования или записи базы данных.
        uint16_t uiCrcOfBlocksCrc;
        uint16_t uiFreeSpaceOffset;
        TBlockPositionData axBlockPositionData[MAX_BLOCKS_NUMBER];
    };

//    enum
//    {
//        // Количество байт служебного контекста
//        // должно быть известно заранее.
//        // Так как по нему извлекаются начальные данные.
//        // Используется самовосстанавливающийся код Хемминга(8,4).
//        // Коэффициент - 1.5: один байт преобразуется в кодовое слово 12 бит,
//        // из двух байт полезных данных получается три байта кодированных.
//        // (((sizeof(struct TBlocksControlData)) * 1.5) = 57)
////        BLOCKS_CONTROL_DATA_LENGTH = 75,//57,//((sizeof(struct TBlocksControlData)) * 1.5),
//        BLOCKS_CONTROL_DATA_LENGTH = (((sizeof(struct TBlocksControlData)) * 1.5) + CRC_LENGTH_3),//78,//57,//
//    };

    CDataStore();
    virtual ~CDataStore();
    void Init(void);
    uint8_t Check(void);
    uint16_t ReadBlock(uint8_t * , uint8_t );
    uint16_t WriteBlock(uint8_t * , uint16_t , uint8_t );
    bool Write(uint8_t *puiSourse, uint16_t uiLength, uint8_t uiBlock);
    bool CompareCurrentWithStoredCrc(void);
    void CrcOfBlocksCrcCreate(void);
    bool CrcOfBlocksCrcCheck(void);
    void Fsm(void);

    CTimer* GetTimerPointer(void)
    {
        return &m_xTimer;
    };

protected:
private:
    // Служебные данные системы хранения.
    TBlocksControlData m_xBlocksControlData;
    // Массив контрольных сумм блоков.
    uint16_t m_auiBlocksCurrentCrc[MAX_BLOCKS_NUMBER];
    uint8_t* m_puiIntermediateBuff;
    CTimer m_xTimer;
};

//-----------------------------------------------------------------------------------------------------
#endif // CDATASTORE_H
