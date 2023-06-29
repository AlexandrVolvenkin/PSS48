//-------------------------------------------------------------------------------------------------
// ModbusMT - modbus multi trans.
//-------------------------------------------------------------------------------------------------
#ifndef MODBUSMT_H_INCLUDED
#define MODBUSMT_H_INCLUDED


#include <stdint.h>
#include "SerialMT.h"
#include "SpiMT.h"
#include "ATmega128platform.h"
#include "modbus.h"
#include "modbus-rtu.h"

//-------------------------------------------------------------------------------------------------
class CModbusMT
{
public:
    typedef enum
    {
        // максимальная длина сообщения.
        MESSAGE_BAG_MAX_LENGTH = 256,
        // код команды - обмен данными.
        DATA_EXCHANGE_COMMAND = 0x42,
        // 0 - смещение на команду в массиве RX SPI_MT.
        COMMAND_BYTE_OFFSET = 0,
        // 1 - смещение на размер сообщения в массиве RX SPI_MT.
        DATA_LENGTH_BYTE_OFFSET = 1,
        // 2 - смещение на данные в массиве RX SPI_MT.
        DATA_BYTE_OFFSET = 2,
        // длина заголовка сообщения.
        HEADER_LENGTH = 2,
        // длина контрольной суммы.
        CRC_LENGTH = 2
    };

//-------------------------------------------------------------------------------------------------
public:
    static uint8_t fui8DataExchangeIsOccurred;
//    static uint8_t aui8ReceiveMessageBuff[CModbusMT::MESSAGE_BAG_MAX_LENGTH];
//    static uint8_t aui8TransmitMessageBuff[CModbusMT::MESSAGE_BAG_MAX_LENGTH];
//    static uint16_t nui8BuffByteCounter;
    static uint16_t nui16RxFrameLength;
    static uint16_t nui16TxFrameLength;

    static int16_t DataReceive(CSerialMT::TSerialMTData *pxData);
    static int16_t DataTransmit(CSerialMT::TSerialMTData *pxData);
    static int16_t DataExchange(modbus_mapping_t *pxModbusMapping);

    static uint8_t* GetModbusRxBuff(void)
    {
        // вернём указатель на буфер приёма.
        return CSpiMT::aui8ReceiveMessageBuff;
    }
    static uint8_t* GetModbusTxBuff(void)
    {
        // вернём указатель на буфер передачи.
        return CSpiMT::aui8TransmitMessageBuff;
    }
    static void DataExchangeFlagSet(void)
    {
        // установим флаг - произошел обмен данными по Modbus.
        CModbusMT::fui8DataExchangeIsOccurred = 1;
    }
    static void DataExchangeFlagReset(void)
    {
        // сбросим флаг - произошел обмен данными по Modbus.
        CModbusMT::fui8DataExchangeIsOccurred = 0;
    }
    static int8_t DataExchangeIsOccurred(void)
    {
        // произошел обмен данными по Modbus?
        return CModbusMT::fui8DataExchangeIsOccurred;
    }

private:
};


#endif // MODBUSMT_H_INCLUDED
