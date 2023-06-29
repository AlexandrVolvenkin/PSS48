//-------------------------------------------------------------------------------------------------
// ModbusMT - modbus multi trans.
//-------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "ModbusMT.h"
#include "SerialMT.h"
#include "Crc.h"
#include "MindPasConfig.h"

//-------------------------------------------------------------------------------------------------
//uint8_t CModbusMT::aui8ReceiveMessageBuff[CModbusMT::MESSAGE_BAG_MAX_LENGTH];
//uint8_t CModbusMT::aui8TransmitMessageBuff[CModbusMT::MESSAGE_BAG_MAX_LENGTH];
//uint16_t CModbusMT::nui8BuffByteCounter;
uint16_t CModbusMT::nui16RxFrameLength;
uint16_t CModbusMT::nui16TxFrameLength;
uint8_t CModbusMT::fui8DataExchangeIsOccurred;

//-------------------------------------------------------------------------------------------------
int16_t CModbusMT::DataReceive(CSerialMT::TSerialMTData *pxData)
{
    // длина сообщения слишком мала?
    if (CModbusMT::nui16RxFrameLength <=
            (CModbusMT::HEADER_LENGTH))
    {
        return -1;
    }
    // получим указатель на принятое общее сообщение в кадре ModbusMT.
    pxData -> pui8DataPointer = CModbusMT::GetModbusRxBuff();
    // получим длину принятого общего сообщения в кадре ModbusMT.
    pxData -> i16Length = CModbusMT::nui16RxFrameLength;
}

//-------------------------------------------------------------------------------------------------
int16_t CModbusMT::DataTransmit(CSerialMT::TSerialMTData *pxData)
{
    // длина сообщения слишком мала?
    if ((pxData -> i16Length) <=
            CModbusMT::HEADER_LENGTH)
    {
        return -1;
    }
    // передадим размер созданного сообщение SerialMT в функию отправки данных по Modbus.
    CModbusMT::nui16TxFrameLength = pxData -> i16Length;

    return 0;
}

//-------------------------------------------------------------------------------------------------
int16_t CModbusMT::DataExchange(modbus_mapping_t *pxModbusMapping)
{
    // получим длину принятого общего сообщения в кадре ModbusMT.
    CModbusMT::nui16RxFrameLength = pxModbusMapping -> current_message_nb_common;
    // получим указатель на созданное общее сообщение SerialMT.
    (pxModbusMapping -> buffer_pointer) = CModbusMT::GetModbusTxBuff();
    // передадим размер созданного сообщение SerialMT в функию отправки данных по Modbus.
    pxModbusMapping -> current_message_nb_common = CModbusMT::nui16TxFrameLength;

    // установим флаг - произошел обмен данными по Modbus.
    CModbusMT::DataExchangeFlagSet();
    nui8FrameCounter++; // modbus mind.
}

//-----------------------------------------------------------------------------------------------------
