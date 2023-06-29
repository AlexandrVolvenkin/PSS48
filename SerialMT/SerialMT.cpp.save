//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
// SerialMT - serial multi trans.
//-----------------------------------------------------------------------------------------------------
#include <cstring>

#include "SerialMT.h"
#include "Crc.h"


//-----------------------------------------------------------------------------------------------------
void CSerialMT::Init(void)
{

}

//-----------------------------------------------------------------------------------------------------
uint8_t CSerialMT::InsertMessage(TMessageContext &xMessageContext)
{
    // Отправляем первое сообщение?
    if (1)
    {
        m_uiMessageLength = 0;
        m_puiCurrentMessage = m_puiTxBuffer;
    }

    // Для сообщения есть место?
    if ((m_uiMessageLength + xMessageContext.uiLength) <= MESSAGE_BAG_MAX_LENGTH)
    {
        m_puiCurrentMessage[m_uiMessageLength++] = xMessageContext.uiAddress;
        m_puiCurrentMessage[m_uiMessageLength++] = xMessageContext.uiFunctionCode;
        m_puiCurrentMessage[m_uiMessageLength++] = xMessageContext.uiLength;
        memcpy(&m_puiCurrentMessage[m_uiMessageLength],
               xMessageContext.puiMessage,
               xMessageContext.uiLength);
        m_uiMessageLength += xMessageContext.uiLength;
        return 1;
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSerialMT::SendMessage(void)
{

    if (0)
    {

        return 1;
    }
    else
    {
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------
int16_t CSerialMT::Reply(uint8_t *puiRequest, uint8_t *puiResponse, uint16_t uiFrameLength)
{
    uint16_t uiOffset = HEADER_LENGTH;
    int8_t uiSlave = puiRequest[uiOffset - 1];
    int8_t uiFunctionCode = puiRequest[uiOffset];
    uint16_t uiLength = uiFrameLength;

    switch (uiFunctionCode)
    {
    case 1:
        break;

    case 2:
        break;

    default:
        break;
    }

}

