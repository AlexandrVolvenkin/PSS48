//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "ModbusRTU.h"
#include "Crc.h"
#include "DataBase.h"


//-----------------------------------------------------------------------------------------------------
CModbusRTU::CModbusRTU()
{

}

////-----------------------------------------------------------------------------------------------------
//CModbusRTU::CModbusRTU(CUart* pxDevice,
//                       uint32_t uiBaudRate,
//                       char cParity,
//                       uint8_t uiDataBit,
//                       uint8_t uiStopBit,
//                       uint8_t *puiRxBuffer,
//                       uint8_t *puiTxBuffer) :
//    pxDevice(pxDevice),
//    uiBaudRate(uiBaudRate),
//    cParity(cParity),
//    uiDataBit(uiDataBit),
//    uiStopBit(uiStopBit),
//    m_puiRxBuffer(puiRxBuffer),
//    m_puiTxBuffer(puiTxBuffer)
//{
//    SetFsmState(MODBUS_IDDLE);
//}

//-----------------------------------------------------------------------------------------------------
CModbusRTU::~CModbusRTU()
{

}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::Init(CUart* pxDevice,
                      uint32_t uiBaudRate,
                      char cParity,
                      uint8_t uiDataBit,
                      uint8_t uiStopBit,
                      uint8_t *puiRxBuffer,
                      uint8_t *puiTxBuffer,
                      uint8_t *puiCoils,
                      uint8_t *puiDiscreteInputs,
                      uint16_t *pui16HoldingRegisters,
                      uint16_t *pui16InputRegisters,
                      uint16_t uiCoilsNumber,
                      uint16_t uiDiscreteInputsNumber,
                      uint16_t uiHoldingRegistersNumber,
                      uint16_t uiInputRegistersNumber)
{
    m_pxDevice = pxDevice;
    m_uiBaudRate = uiBaudRate;
    m_cParity = cParity;
    m_uiDataBit = uiDataBit;
    m_uiStopBit = uiStopBit;
    m_puiRxBuffer = puiRxBuffer;
    m_puiTxBuffer = puiTxBuffer;
    m_puiCoils = puiCoils;
    m_puiDiscreteInputs = puiDiscreteInputs;
    m_pui16HoldingRegisters = pui16HoldingRegisters;
    m_pui16InputRegisters = pui16InputRegisters;
    m_uiCoilsNumber = uiCoilsNumber;
    m_uiDiscreteInputsNumber = uiDiscreteInputsNumber;
    m_uiHoldingRegistersNumber = uiHoldingRegistersNumber;
    m_uiInputRegistersNumber = uiInputRegistersNumber;

    m_uiGuardTimeout = ((((1000000UL / m_uiBaudRate) * 8UL * 4UL) / 1000UL) + 1);

    memset(m_puiCoils, 0, m_uiCoilsNumber * sizeof(uint8_t));
    memset(m_puiDiscreteInputs, 0, m_uiDiscreteInputsNumber * sizeof(uint8_t));
    memset(m_pui16HoldingRegisters, 0, m_uiHoldingRegistersNumber * sizeof(uint16_t));
    memset(m_pui16InputRegisters, 0, m_uiInputRegistersNumber * sizeof(uint16_t));

    m_pxDevice -> Init(m_uiBaudRate,
                       m_cParity,
                       m_uiDataBit,
                       m_uiStopBit,
                       puiRxBuffer,
                       puiTxBuffer);
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::Reset(void)
{
    m_pxDevice -> Reset();
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::Open(void)
{
    m_pxDevice -> Open();
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::Close(void)
{
    m_pxDevice -> Close();
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::ReceiveEnable(void)
{
    m_pxDevice -> Enable();
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::ReceiveDisable(void)
{
    m_pxDevice -> Disable();
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::TransmitEnable(void)
{
    m_pxDevice -> TransmitEnable();
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::TransmitDisable(void)
{
    m_pxDevice -> TransmitDisable();
}

//-----------------------------------------------------------------------------------------------------
int16_t CModbusRTU::Tail(uint8_t *puiMessage, uint16_t uiLength)
{
    uint16_t uiCrc = usCrc16(puiMessage, uiLength);
    puiMessage[uiLength++] = uiCrc & 0x00FF;
    puiMessage[uiLength++] = uiCrc >> 8;

    return uiLength;
}

/* Builds a RTU request header */
int16_t CModbusRTU::RequestBasis(uint8_t uiSlave,
                                 uint8_t uiFunctionCode,
                                 uint16_t uiAddress,
                                 uint16_t uiBitNumber,
                                 uint8_t *puiRequest)
{
    puiRequest[0] = uiSlave;
    puiRequest[1] = uiFunctionCode;
    puiRequest[2] = (static_cast<uint8_t>(uiAddress >> 8));
    puiRequest[3] = (static_cast<uint8_t>(uiAddress & 0x00ff));
    puiRequest[4] = (static_cast<uint8_t>(uiBitNumber >> 8));
    puiRequest[5] = (static_cast<uint8_t>(uiBitNumber & 0x00ff));

    return _MODBUS_RTU_PRESET_REQ_LENGTH;
}

/* Builds a RTU response header */
int16_t CModbusRTU::ResponseBasis(uint8_t uiSlave, uint8_t uiFunctionCode, uint8_t *puiResponse)
{
    /* In this case, the slave is certainly valid because a check is already
     * done in _modbus_rtu_listen */
    puiResponse[0] = uiSlave;
    puiResponse[1] = uiFunctionCode;

    return _MODBUS_RTU_PRESET_RSP_LENGTH;
}

//-----------------------------------------------------------------------------------------------------
int16_t CModbusRTU::Send(uint8_t *puiMessage, uint16_t uiLength)
{
    return m_pxDevice -> Write(puiMessage, uiLength);
}

//-----------------------------------------------------------------------------------------------------
uint8_t CModbusRTU::MessageIsSended(void)
{
    return m_pxDevice -> FrameIsSended();
}

//-----------------------------------------------------------------------------------------------------
uint8_t CModbusRTU::Select(void)
{
    return m_pxDevice -> ByteIsReceived();
}

//-----------------------------------------------------------------------------------------------------
int16_t CModbusRTU::Receive(uint8_t *puiDestination, uint16_t uiLength)
{
    return m_pxDevice -> Read(puiDestination, uiLength);
}

//-----------------------------------------------------------------------------------------------------
uint8_t CModbusRTU::FrameIsReceived(void)
{
    if ((CPlatform::GetSystemTick() - m_uiLastSystemTime)  >=
            m_uiGuardTimeout)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

//-----------------------------------------------------------------------------------------------------
uint8_t CModbusRTU::ReceiveTimeIsOver(void)
{
    if ((CPlatform::GetSystemTick() - m_uiLastSystemTime)  >=
            m_uiReceiveTimeout)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

//-----------------------------------------------------------------------------------------------------
uint8_t CModbusRTU::ConfirmationReceiveTimeIsOver(void)
{
    if ((CPlatform::GetSystemTick() - m_uiLastSystemTime)  >=
            m_uiConfirmationTimeout)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

//-----------------------------------------------------------------------------------------------------
uint8_t CModbusRTU::TransmitDelayTimeIsOver(void)
{
    if ((CPlatform::GetSystemTick() - m_uiLastSystemTime)  >=
            m_uiTransmitDelayTimeout)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

//-----------------------------------------------------------------------------------------------------
int8_t CModbusRTU::TimeIsOver(uint16_t uiTimeout)
{
    if ((CPlatform::GetSystemTick() - m_uiLastSystemTime)  >=
            uiTimeout)
    {
        return 1;
    }
    else
    {
        return 0;
    }
};

//-----------------------------------------------------------------------------------------------------
uint16_t CModbusRTU::GetFrameLength(void)
{
    return m_pxDevice -> GetFrameLength();
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::GetSystemTime(void)
{
    m_uiLastSystemTime = CPlatform::GetSystemTick();
}

//-----------------------------------------------------------------------------------------------------
int8_t CModbusRTU::FrameCheck(void)
{
    if (m_pxDevice -> GetFrameLength() < _MIN_MESSAGE_LENGTH)
    {
        return 0;
    }

    uint16_t uiCrc = ((static_cast<uint16_t>(m_puiRxBuffer[m_pxDevice -> GetFrameLength() - 1]) << 8) |
                      (static_cast<uint16_t>(m_puiRxBuffer[m_pxDevice -> GetFrameLength() - 2])));

    if (usCrc16(m_puiRxBuffer,
                (m_pxDevice -> GetFrameLength() - _MODBUS_RTU_CHECKSUM_LENGTH)) == uiCrc)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------
int8_t CModbusRTU::FrameCheck(uint8_t *puiSource, uint16_t uiLength)
{
    if (uiLength < _MIN_MESSAGE_LENGTH)
    {
        return 0;
    }

    uint16_t uiCrc = ((static_cast<uint16_t>(puiSource[uiLength - 1]) << 8) |
                      (static_cast<uint16_t>(puiSource[uiLength - 2])));
    uint16_t uiCrcTemp = usCrc16(puiSource,
                                 (uiLength - _MODBUS_RTU_CHECKSUM_LENGTH));
    if (usCrc16(puiSource,
                (uiLength - _MODBUS_RTU_CHECKSUM_LENGTH)) == uiCrc)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------
void CModbusRTU::Fsm(void)
{
    int16_t iReceivedCounter;

    switch (GetFsmState())
    {
    case IDDLE:
        break;

    case START_REQUEST:
        GetSystemTime();
        Reset();
        m_uiMessageLength = 0;
//        Open();
        ReceiveEnable();
        SetFsmState(WAITING_MESSAGE_REQUEST);
        break;

    case WAITING_MESSAGE_REQUEST:
        if (Select())
        {
            iReceivedCounter = Receive(m_puiRxBuffer + m_uiMessageLength, MODBUS_RTU_MAX_ADU_LENGTH - m_uiMessageLength);

            if (iReceivedCounter > 0)
            {
                m_uiMessageLength += iReceivedCounter;
                GetSystemTime();
                SetFsmState(RECEIVE_MESSAGE_REQUEST);
            }
            else if (iReceivedCounter == -1)
            {
                SetFsmState(START_REQUEST);
            }
        }

        if (TimeIsOver(m_uiReceiveTimeout))
        {
            SetFsmState(START_REQUEST);
        }

        break;

    case RECEIVE_MESSAGE_REQUEST:
        if (Select())
        {
            iReceivedCounter = Receive(m_puiRxBuffer + m_uiMessageLength, MODBUS_RTU_MAX_ADU_LENGTH - m_uiMessageLength);

            if (iReceivedCounter > 0)
            {
                m_uiMessageLength += iReceivedCounter;
                GetSystemTime();
            }
            else if (iReceivedCounter == -1)
            {
                SetFsmState(START_REQUEST);
            }
        }

        if (TimeIsOver(m_uiGuardTimeout))
        {
            if (FrameCheck(m_puiRxBuffer, m_uiMessageLength))
            {
                SetFsmState(REPLY_REQUEST);
            }
            else
            {
                SetFsmState(START_REQUEST);
            }
        }

        break;

    case REPLY_REQUEST:
        if (Reply(m_puiRxBuffer, m_puiTxBuffer, m_uiMessageLength))
        {
            CPlatform::TxLedOn();
            SetFsmState(FRAME_TRANSMIT_CONFIRMATION);
        }
        else
        {
            CPlatform::TxLedOff();
            SetFsmState(START_REQUEST);
        }
        break;

    case FRAME_TRANSMIT_CONFIRMATION:
        GetSystemTime();
        Reset();
        ReceiveDisable();
        SetFsmState(WAITING_FRAME_TRANSMIT_CONFIRMATION);
        break;

    case WAITING_FRAME_TRANSMIT_CONFIRMATION:
        if (TimeIsOver(m_uiTransmitDelayTimeout))
        {
            SendMessage(m_puiTxBuffer, m_uiMessageLength);
            TransmitEnable();
            SetFsmState(END_WAITING_FRAME_TRANSMIT_CONFIRMATION);
        }
        break;

    case END_WAITING_FRAME_TRANSMIT_CONFIRMATION:
        if (MessageIsSended())
        {
            TransmitDisable();
            CPlatform::TxLedOff();
            SetFsmState(START_REQUEST);
        }

        break;

    case STOP_REQUEST:
        ReceiveDisable();
//        Close();
        SetFsmState(IDDLE);
        break;

//-----------------------------------------------------------------------------------------------------
// ModbusMaster
    case START_CONFIRMATION:
        GetSystemTime();
        Reset();
        m_uiMessageLength = 0;
//        Open();
        ReceiveEnable();
        SetFsmState(WAITING_MESSAGE_CONFIRMATION);
        break;

    case WAITING_MESSAGE_CONFIRMATION:
        if (Select())
        {
            iReceivedCounter = Receive(m_puiRxBuffer + m_uiMessageLength, MODBUS_RTU_MAX_ADU_LENGTH - m_uiMessageLength);

            if (iReceivedCounter > 0)
            {
                GetSystemTime();
                m_uiMessageLength += iReceivedCounter;
                SetFsmState(RECEIVE_MESSAGE_CONFIRMATION);
            }
            else if (iReceivedCounter == -1)
            {
                SetFsmState(STOP_CONFIRMATION);
            }
        }

        if (TimeIsOver(m_uiConfirmationTimeout))
        {
            SetFsmState(STOP_CONFIRMATION);
        }

        break;

    case RECEIVE_MESSAGE_CONFIRMATION:
        if (Select())
        {
            iReceivedCounter = Receive(m_puiRxBuffer + m_uiMessageLength, MODBUS_RTU_MAX_ADU_LENGTH - m_uiMessageLength);

            if (iReceivedCounter > 0)
            {
                GetSystemTime();
                m_uiMessageLength += iReceivedCounter;
            }
            else if (iReceivedCounter == -1)
            {
                SetFsmState(STOP_CONFIRMATION);
            }
        }

        if (TimeIsOver(m_uiGuardTimeout))
        {
            if (FrameCheck(m_puiRxBuffer, m_uiMessageLength))
            {
                SetFsmState(REPLY_CONFIRMATION);
            }
            else
            {
                SetFsmState(STOP_CONFIRMATION);
            }
        }

        break;

    case REPLY_CONFIRMATION:
        if (ReceiveMessage(m_puiRxBuffer, m_uiMessageLength))
        {
            SetFsmState(STOP_CONFIRMATION);
        }
        else
        {
            SetFsmState(STOP_CONFIRMATION);
        }
        break;

    case FRAME_TRANSMIT_REQUEST:
        GetSystemTime();
        Reset();
        CPlatform::TxLedOn();
        SetFsmState(WAITING_FRAME_TRANSMIT_REQUEST);
        break;

    case WAITING_FRAME_TRANSMIT_REQUEST:
        if (TimeIsOver(m_uiTransmitDelayTimeout))
        {
            SendMessage(m_puiTxBuffer, m_uiMessageLength);
            TransmitEnable();
            SetFsmState(END_WAITING_FRAME_TRANSMIT_REQUEST);
        }
        break;

    case END_WAITING_FRAME_TRANSMIT_REQUEST:
        if (MessageIsSended())
        {
            TransmitDisable();
            CPlatform::TxLedOff();
            SetFsmState(START_CONFIRMATION);
        }

        break;

    case STOP_CONFIRMATION:
        ReceiveDisable();
//        Close();
        SetFsmState(IDDLE);
        break;

    default:
        break;
    }
}
//-----------------------------------------------------------------------------------------------------





