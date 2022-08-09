
//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "DataStore.h"
#include "Platform.h"
#include "Pss21.h"
#include "Crc.h"
#include "HammingCodes.h"


//CDataStore::TBlocksControlData CDataStore::m_xBlocksControlData;
//uint8_t* CDataStore::m_puiIntermediateBuff;
//-----------------------------------------------------------------------------------------------------
CDataStore::CDataStore()
{
//    m_pxStorageDevice = new CEeprom();
    m_puiIntermediateBuff = CPss21::m_auiIntermediateBuff;
    SetFsmState(IDDLE);
    SetSavedFsmState(IDDLE);
}

//-----------------------------------------------------------------------------------------------------
CDataStore::~CDataStore()
{
//    delete m_pxStorageDevice;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CDataStore::Init(void)
{
    // Очистим служебный контекст.
    memset(reinterpret_cast<uint8_t*>(&m_xBlocksControlData),
           0,
           sizeof(m_xBlocksControlData));

    // Установим смещение на закодированные данные.
    m_xBlocksControlData.
    axBlockPositionData[BLOCKS_CONTROL_DATA].uiOffset = BLOCKS_CONTROL_DATA_BEGIN;
    // Установим размер первичных данных.
    m_xBlocksControlData.
    axBlockPositionData[BLOCKS_CONTROL_DATA].uiLength = sizeof(struct TBlocksControlData);
    // Установим размер закодированных данных.
    m_xBlocksControlData.
    axBlockPositionData[BLOCKS_CONTROL_DATA].uiEncodedLength = BLOCKS_CONTROL_DATA_LENGTH;
    // Установим смещение для служебного контекста.
    m_xBlocksControlData.uiFreeSpaceOffset = (BLOCKS_CONTROL_DATA_BEGIN + BLOCKS_CONTROL_DATA_LENGTH);
    // Установим признак - база данных не подтверждена пользователем.
    m_xBlocksControlData.uiCrcOfBlocksCrc = 0;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CDataStore::Check(void)
{
    CPss21::m_xDataStore.Init();

    // Служебный блок повреждён?
    if (!(ReadBlock(reinterpret_cast<uint8_t*>(&m_xBlocksControlData), BLOCKS_CONTROL_DATA)))
    {
        // Блок повреждён.
        return 0;
    }

    enum
    {
        IDDLE = 0,
        BLOCK_CHECK_START,
        BLOCK_WRITE_START,
        BLOCK_WRITE_END_WAITING,
        NEXT_BLOCK,
        BLOCK_ERROR,
        ALL_BLOCKS_CHECKED,
    };

    uint8_t uiBlockCounter = 0;
    uint8_t uiFsmState = BLOCK_CHECK_START;
    uint16_t uiLength;

    CHammingCodes::SetErrorCode(CHammingCodes::NONE_ERROR);

    while (1)
    {
        switch (uiFsmState)
        {
        case BLOCK_CHECK_START:
            // Проверены не все блоки?
            if (uiBlockCounter < MAX_BLOCKS_NUMBER)
            {
                uiLength = ReadBlock(m_puiIntermediateBuff, uiBlockCounter);
                // Блок не повреждён?
                if (uiLength)
                {
                    // Блок восстановлен после обнаружения ошибки?
                    if (CHammingCodes::GetErrorCode() != CHammingCodes::NONE_ERROR)
                    {
                        // Обновим восстановленный блок в хранилище.
                        uiFsmState = BLOCK_WRITE_START;
                    }
                    else
                    {
                        uiFsmState = NEXT_BLOCK;
                    }
                }
                else
                {
                    uiFsmState = BLOCK_ERROR;
                }
            }
            else
            {
                uiFsmState = ALL_BLOCKS_CHECKED;
            }
            break;

        case BLOCK_WRITE_START:
            // Поместим данные в хранилище.
            // Блок БД принят к записи?
            if (Write(m_puiIntermediateBuff, uiLength, uiBlockCounter))
            {
                uiFsmState = BLOCK_WRITE_END_WAITING;
            }
            // При записи блока БД произошла ошибка?
            else if (CPss21::m_xDataStore.GetFsmEvent() == CDataStore::WRITE_ERROR_FSM_EVENT)
            {
                uiFsmState = BLOCK_ERROR;
            }
            break;

        case BLOCK_WRITE_END_WAITING:
            // Блок записан успешно?
            if (CPss21::m_xDataStore.GetFsmEvent() == CDataStore::WRITE_OK_FSM_EVENT)
            {
                uiFsmState = NEXT_BLOCK;
            }
            // При записи блока БД произошла ошибка?
            else if (CPss21::m_xDataStore.GetFsmEvent() == CDataStore::WRITE_ERROR_FSM_EVENT)
            {
                uiFsmState = BLOCK_ERROR;
            }
            break;

        case NEXT_BLOCK:
            uiBlockCounter++;
            uiFsmState = BLOCK_CHECK_START;
            break;

        case ALL_BLOCKS_CHECKED:
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

    // данные не повреждены.
    return 1;
}

//-----------------------------------------------------------------------------------------------------
uint16_t CDataStore::ReadBlock(uint8_t *puiDestination, uint8_t uiBlock)
{
    // Произошёл выход за границы буфера?
    if (uiBlock >= MAX_BLOCKS_NUMBER)
    {
//        CPss21::SetErrorCode(DB_ERROR);
//        // Нет данных.
        return 0;
    }

    uint16_t uiDecodedByteCounter;
    uint16_t uiEncodedLength;
    uint16_t uiSourseOffset;
    uint8_t auiTempArray[256];

    // Блок существует?
    if ((m_xBlocksControlData.
            axBlockPositionData[uiBlock].uiOffset != 0) &&
            (m_xBlocksControlData.
             axBlockPositionData[uiBlock].uiEncodedLength != 0))
    {
        // Получим адрес блока в EEPROM.
        uiSourseOffset = m_xBlocksControlData.
                         axBlockPositionData[uiBlock].uiOffset;
        // Получим размер блока.
        uiEncodedLength = m_xBlocksControlData.
                          axBlockPositionData[uiBlock].uiEncodedLength;
    }
    else
    {
//        CPss21::SetErrorCode(DB_ERROR);
//        // Нет данных.
        return 0;
    }

    // Прочитаем закодированные данные.
    for (uint16_t i = 0; i < uiEncodedLength; i++)
    {
        auiTempArray[i] = CEeprom::ReadByte(uiSourseOffset);
        uiSourseOffset++;
    }

    // Декодируем прочитанные данные.
    uiDecodedByteCounter = CHammingCodes::HammingCodesToBytes(auiTempArray, auiTempArray, uiEncodedLength);
    // Слишком короткий блок?
    // Минимум 3 байта 1 - данные и 2 - Crc.
    if (uiDecodedByteCounter <= CRC_LENGTH)
    {
        CPss21::SetErrorCode(DB_ERROR);
        // Нет данных.
        return 0;
    }

    // Получим длину блока.
    uiDecodedByteCounter -= CRC_LENGTH;
    // Размер блока не совпадает?
    if (uiDecodedByteCounter !=
            m_xBlocksControlData.
            axBlockPositionData[uiBlock].uiLength)
    {
        CPss21::SetErrorCode(DB_ERROR);
        // Нет данных.
        return 0;
    }

    // Получим контрольную сумму блока.
    uint16_t uiCrc = static_cast<uint16_t>(auiTempArray[uiDecodedByteCounter]);
    uiCrc |= (static_cast<uint16_t>(auiTempArray[uiDecodedByteCounter + 1]) << 8);
    // Вычислим контрольную сумму блока.
    uint16_t uiCalculatedCrc = usCrc16(auiTempArray, uiDecodedByteCounter);

    // Блок не повреждён?
    if (uiCrc == uiCalculatedCrc)
    {
        m_auiCurrentBlocksCrc[uiBlock] = uiCrc;
        memcpy(puiDestination, auiTempArray, uiDecodedByteCounter);
        return uiDecodedByteCounter;
    }
    else
    {
        CPss21::SetErrorCode(DB_ERROR);
        // Нет данных.
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------
uint16_t CDataStore::WriteBlock(uint8_t *puiSourse, uint16_t uiLength, uint8_t uiBlock)
{
    // Произошёл выход за границы буфера?
    if (uiBlock >= MAX_BLOCKS_NUMBER)
    {
        // Нет данных.
        return 0;
    }

    uint16_t uiEncodedByteCounter;
    uint8_t auiTempArray[256];
    uint16_t uiDestinationOffset;

    memcpy(auiTempArray, puiSourse, uiLength);
    // Вычислим контрольную сумму поступивших данных.
    uint16_t uiCrc = usCrc16(puiSourse, uiLength);
    auiTempArray[uiLength] = static_cast<uint8_t>(uiCrc);
    auiTempArray[uiLength + 1] = static_cast<uint8_t>(uiCrc >> 8);

    m_xBlocksControlData.
    axBlockPositionData[uiBlock].uiCrc = uiCrc;

    uiEncodedByteCounter = CHammingCodes::BytesToHammingCodes(m_puiIntermediateBuff, auiTempArray, (uiLength + CRC_LENGTH));

    // Данные текущего блока данных - uiBlock сохраняются впервые?
    if (m_xBlocksControlData.
            axBlockPositionData[uiBlock].uiEncodedLength == 0)
    {
        // Добавили новый блок данных.
        // Сохраним смещение на блок.
        m_xBlocksControlData.
        axBlockPositionData[uiBlock].uiOffset = m_xBlocksControlData.uiFreeSpaceOffset;
        // Изменим смещение на свободное место.
        m_xBlocksControlData.uiFreeSpaceOffset += uiEncodedByteCounter;
        // Сохраним размер первичных данных.
        m_xBlocksControlData.
        axBlockPositionData[uiBlock].uiLength = uiLength;
        // Сохраним размер закодированных данных.
        m_xBlocksControlData.
        axBlockPositionData[uiBlock].uiEncodedLength = uiEncodedByteCounter;
    }

//    if (uiBlock != BLOCKS_CONTROL_DATA)
//    {
//        m_xBlocksControlData.
//        axBlockPositionData[uiBlock].uiCrc = uiCrc;
//    }

    CEeprom::WriteInterrupt(m_xBlocksControlData.
                            axBlockPositionData[uiBlock].uiOffset,
                            m_puiIntermediateBuff,
                            uiEncodedByteCounter);

    // Out length.
    return uiEncodedByteCounter;
}

//-----------------------------------------------------------------------------------------------------
bool CDataStore::Write(uint8_t *puiSourse, uint16_t uiLength, uint8_t uiBlock)
{
    if (GetFsmState() == IDDLE)
    {
        if (WriteBlock(puiSourse,
                       uiLength,
                       uiBlock))
        {
            SetFsmEvent(WRITE_IN_PROGRESS_FSM_EVENT);
            SetFsmState(START_WRITE);
            return true;
        }
        else
        {
            SetFsmEvent(WRITE_ERROR_FSM_EVENT);
            return false;
        }
    }
    else
    {
        SetFsmEvent(STORAGE_DEVICE_BUSY_FSM_EVENT);
        return false;
    }
}

//-----------------------------------------------------------------------------------------------------
bool CDataStore::CompareCurrentWithStoredCrc(void)
{
    // Проверим принадлежность всех блоков текущей базе данных.
    // Сравним текущее Crc блока с его Crc сохранённом в служебном блоке в предыдущей сессии записи.
    for (uint16_t i = BLOCKS_CONTROL_DATA_BLOCK_NUMBER;
            i < (MAX_BLOCKS_NUMBER - BLOCKS_CONTROL_DATA_BLOCK_NUMBER);
            i++)
    {
        if (m_auiCurrentBlocksCrc[i] !=
                m_xBlocksControlData.axBlockPositionData[i].uiCrc)
        {
            return false;
        }
    }

    // Все блоки принадлежат текущей базе данных.
    return true;
}

//-----------------------------------------------------------------------------------------------------
// Вызывается только если база данных подтверждена пользователем.
void CDataStore::CrcOfBlocksCrcCreate(void)
{
    // Контрольная сумма вычисленная из массива контрольных сумм блоков, не включая служебный.
    // Сохраняется при первой и последующих записях любых блоков через программатор.
    // Ноль или её не совпадение свидетельствует о том, что база данных создана по умоланию,
    // и не подтверждена пользователем. В этом случае прибор переходит в режим сигнализации об ошибке,
    // ожидая квитирования или записи базы данных.
    uint16_t auiBlocksCrc[MAX_BLOCKS_NUMBER - BLOCKS_CONTROL_DATA_BLOCK_NUMBER];

    // Получим Crc всех блоков, не включая служебный.
    for (uint16_t i = 0;
            i < (MAX_BLOCKS_NUMBER - BLOCKS_CONTROL_DATA_BLOCK_NUMBER);
            i++)
    {
        auiBlocksCrc[i] =
            m_xBlocksControlData.axBlockPositionData[i + BLOCKS_CONTROL_DATA_BLOCK_NUMBER].uiCrc;
    }

    // Сохраним Crc всех блоков, не включая служебный.
    m_xBlocksControlData.uiCrcOfBlocksCrc =
        usCrc16(reinterpret_cast<uint8_t*>(auiBlocksCrc),
                ((MAX_BLOCKS_NUMBER - BLOCKS_CONTROL_DATA_BLOCK_NUMBER) * sizeof(uint16_t)));
}

//-----------------------------------------------------------------------------------------------------
bool CDataStore::CrcOfBlocksCrcCheck(void)
{
    // Контрольная сумма вычисленная из массива контрольных сумм блоков, не включая служебный.
    // Сохраняется при первой и последующих записях любых блоков через программатор.
    // Ноль или её не совпадение свидетельствует о том, что база данных создана по умоланию,
    // и не подтверждена пользователем. В этом случае прибор переходит в режим сигнализации об ошибке,
    // ожидая квитирования или записи базы данных.
    uint16_t auiBlocksCrc[MAX_BLOCKS_NUMBER - BLOCKS_CONTROL_DATA_BLOCK_NUMBER];

    // Получим Crc всех блоков, не включая служебный.
    for (uint16_t i = 0;
            i < (MAX_BLOCKS_NUMBER - BLOCKS_CONTROL_DATA_BLOCK_NUMBER);
            i++)
    {
        auiBlocksCrc[i] =
            m_xBlocksControlData.axBlockPositionData[i + BLOCKS_CONTROL_DATA_BLOCK_NUMBER].uiCrc;
    }

    // База данных подтверждена пользователем?
    if (m_xBlocksControlData.uiCrcOfBlocksCrc ==
            usCrc16(reinterpret_cast<uint8_t*>(auiBlocksCrc),
                    ((MAX_BLOCKS_NUMBER - BLOCKS_CONTROL_DATA_BLOCK_NUMBER) * sizeof(uint16_t))))
    {
        return true;
    }
    else
    {
        return false;
    }
}

//-----------------------------------------------------------------------------------------------------
void CDataStore::Fsm(void)
{
    switch (GetFsmState())
    {
    case IDDLE:
        break;

    case START_WRITE:
        // Установим время ожидания окончания записи.
        GetTimerPointer() -> Set(READY_TO_WRITE_WAITING_TIMEOUT);
        SetFsmState(READY_TO_WRITE_WAITING);
        break;

    case READY_TO_WRITE_WAITING:
        if (CEeprom::IsReadyToWrite())
        {
            // Установим время ожидания окончания записи.
            GetTimerPointer() -> Set(WRITE_END_WAITING_TIMEOUT);
            CEeprom::StartWrite();
            SetFsmState(WRITE_END_WAITING);
        }
        // Время ожидания окончания записи закончилось?
        else if (GetTimerPointer() -> IsOverflow())
        {
            SetFsmEvent(WRITE_ERROR_FSM_EVENT);
            SetFsmState(IDDLE);
        }
        break;

    case WRITE_END_WAITING:
        if (CEeprom::GetBufferIsWrited())
        {
            SetFsmState(START_WRITE_BLOCKS_CONTROL_DATA);
        }
        // Время ожидания окончания записи закончилось?
        else if (GetTimerPointer() -> IsOverflow())
        {
            SetFsmEvent(WRITE_ERROR_FSM_EVENT);
            SetFsmState(IDDLE);
        }
        break;


        // Запись служеьного блока.
    case START_WRITE_BLOCKS_CONTROL_DATA:
        // Данные обновлены.
        // Сохраним изменённый служебный контекст.
        if (WriteBlock(reinterpret_cast<uint8_t*>(&m_xBlocksControlData),
                       sizeof(m_xBlocksControlData),
                       BLOCKS_CONTROL_DATA))
        {
            // Установим время ожидания окончания записи.
            GetTimerPointer() -> Set(READY_TO_WRITE_WAITING_TIMEOUT);
            SetFsmState(READY_TO_WRITE_WAITING_BLOCKS_CONTROL_DATA);
        }
        else
        {
            SetFsmEvent(WRITE_ERROR_FSM_EVENT);
            SetFsmState(IDDLE);
        }
        break;

    case READY_TO_WRITE_WAITING_BLOCKS_CONTROL_DATA:
        if (CEeprom::IsReadyToWrite())
        {
            // Установим время ожидания окончания записи.
            GetTimerPointer() -> Set(WRITE_END_WAITING_TIMEOUT);
            CEeprom::StartWrite();
            SetFsmState(WRITE_END_WAITING_BLOCKS_CONTROL_DATA);
        }
        // Время ожидания окончания записи закончилось?
        else if (GetTimerPointer() -> IsOverflow())
        {
            SetFsmEvent(WRITE_ERROR_FSM_EVENT);
            SetFsmState(IDDLE);
        }
        break;

    case WRITE_END_WAITING_BLOCKS_CONTROL_DATA:
        if (CEeprom::GetBufferIsWrited())
        {
            SetFsmEvent(WRITE_OK_FSM_EVENT);
            SetFsmState(IDDLE);
        }
        // Время ожидания окончания записи закончилось?
        else if (GetTimerPointer() -> IsOverflow())
        {
            SetFsmEvent(WRITE_ERROR_FSM_EVENT);
            SetFsmState(IDDLE);
        }
        break;

    default:
        break;
    }
}

