//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
// SerialMT - serial multi trans.
//-----------------------------------------------------------------------------------------------------
#ifndef SERIALMT_H_INCLUDED
#define SERIALMT_H_INCLUDED

//-----------------------------------------------------------------------------------------------------
// SerialMT - serial multi trans.

//-----------------------------------------------------------------------------------------------------
#include <stdint.h>

//-----------------------------------------------------------------------------------------------------
class CSerialMT
{
public:
    // ‘ормат кадра SerialMT: вложенные сообщени€ следующие друг за другом, Crc.
    // ‘ормат вложенного сообщени€ SerialMT:
    // «аголовок - адрес, код функции, количество байт в сообщении не включа€ заголовок. ƒанные.

    enum
    {
        IDDLE = 0,
        START,
        WAITING_MESSAGE,
        RECEIVE_MESSAGE,
        RECEIVE_CONFIRMATION,
        REPLY,
        FRAME_TRANSMIT,
        FRAME_TRANSMIT_END_WAITING,
        RESTART,
        DATA_EXCHANGE_END_WAITING,
        CONTINUOUS_MEASURE,
    };

    typedef enum
    {
        // длина заголовка вложенного сообщени€.
        HEADER_LENGTH = 3,
        CRC_LENGTH = 2,
        TAIL_LENGTH = CRC_LENGTH,
        // максимальна€ длина общего сообщени€.
        MESSAGE_BAG_MAX_LENGTH = (256 - (HEADER_LENGTH + TAIL_LENGTH)),
        MIN_MESSAGE_LENGTH = 4,
    };

    struct TMessageContext
    {
        uint8_t uiAddress;
        uint8_t uiFunctionCode;
        uint8_t *puiMessage;
        uint8_t uiLength;
    };

//-----------------------------------------------------------------------------------------------------
    void Init(void);
    uint8_t InsertMessage(TMessageContext &xMessageContext);
    uint8_t SendMessage(void);
    int16_t Reply(uint8_t * , uint8_t * , uint16_t );

//-----------------------------------------------------------------------------------------------------
//    uint8_t m_uiFlowControl;
    uint16_t m_uiLastSystemTime;
    uint16_t m_uiMessageLength;
    uint16_t m_uiMaxMessageLength;
    uint8_t *m_puiCurrentMessage;
    uint8_t *m_puiRxBuffer;
    uint8_t *m_puiTxBuffer;
};

//-----------------------------------------------------------------------------------------------------

#endif // SERIALMT_H_INCLUDED
