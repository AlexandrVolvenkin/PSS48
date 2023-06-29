//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include <cstddef>

#include "Platform.h"
#include "Pss21.h"
#include "Crc.h"


// ATMega128a
//-----------------------------------------------------------------------------------------------------
CUart::CUart()
{

}

//-----------------------------------------------------------------------------------------------------
CUart::CUart(volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
             volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
             volatile uint8_t *ucsrc, volatile uint8_t *udr,
             volatile uint8_t *rs485DirectionPort, volatile uint8_t rs485DirectionPin,
             volatile uint8_t *rs485OutputPort, volatile uint8_t rs485OutputPin) :
    m_UBRRH(ubrrh), m_UBRRL(ubrrl), m_UCSRA(ucsra),
    m_UCSRB(ucsrb), m_UCSRC(ucsrc), m_UDR(udr),
    m_rs485DirectionPort(rs485DirectionPort), m_rs485DirectionPin(rs485DirectionPin), m_rs485OutputPort(rs485OutputPort), m_rs485OutputPin(rs485OutputPin)
{
    if (m_rs485DirectionPort)
    {
        uint8_t uiData = m_rs485DirectionPin;
        *m_rs485DirectionPort |= _BV(uiData);
        uiData = m_rs485OutputPin;
        *m_rs485OutputPort &= ~(_BV(uiData));
    }
}

//-----------------------------------------------------------------------------------------------------
CUart::~CUart()
{

}

//-----------------------------------------------------------------------------------------------------
void CUart::Init(uint32_t ulBaudRate,
                 uint8_t ucParity,
                 uint8_t uiDataBits,
                 uint8_t ucStopBit,
                 uint8_t *puiRxBuffer,
                 uint8_t *puiTxBuffer)
{
//    m_puiRxBuffer = puiRxBuffer;
//    m_puiTxBuffer = puiTxBuffer;

    /* Set the baud rate */
    uint16_t uiBaudRateTemp = static_cast<uint16_t>((F_CPU / (ulBaudRate * 16UL) - 1));
//    uint16_t uiBaudRateTemp = static_cast<uint16_t>(CPss21::m_xModbusSettings.BaudRate);//(F_CPU / (ulBaudRate * 16UL) - 1);//
    *m_UBRRL = static_cast<uint8_t>(uiBaudRateTemp);
    *m_UBRRH = static_cast<uint8_t>(uiBaudRateTemp >> 8);

    *m_UCSRC = (CPss21::m_xModbusSettings.LinkParam &	// 2 стоп-бита, 8 бит данных
                (BIT(UPM11)|BIT(UPM10)|BIT(USBS1))) |
               (BIT(UCSZ11)|BIT(UCSZ10));

//    /* Set data bits (7, 8 bits) */
//    switch (uiDataBits)
//    {
//    case 8:
//        *m_UCSRC |= (1 << UCSZ00) | (1 << UCSZ01);
//        break;
//    case 7:
//        *m_UCSRC |= (1 << UCSZ01);
//        break;
//    }
//
//    /* Set parity */
//    if (ucParity == 'N')
//    {
//        /* None */
//    }
//    else if (ucParity == 'E')
//    {
//        /* Even */
//        *m_UCSRC |= (1 << UPM01);
//    }
//    else
//    {
//        /* Odd */
//        *m_UCSRC |= (1 << UPM01) | (1 << UPM00);
//    }
//
//    /* Stop bit (1 or 2) */
//    if (ucStopBit == 1)
//    {
//        *m_UCSRC &= ~(1 << USBS0);
//    }
//    else if (ucStopBit == 2) /* 2 */
//    {
//        *m_UCSRC |= (1 << USBS0);
//    }
}

//-----------------------------------------------------------------------------------------------------
void CUart::Reset(void)
{
    m_nuiRxBuffByteCounter = 0;
    m_bfByteIsReceived = 0;
    m_bfFrameIsSended = 0;
    m_bfRxBuffOverflow = 0;
}

//-----------------------------------------------------------------------------------------------------
void CUart::Open(void)
{
    *m_UCSRA |= (1 << RXC0) | (1 << TXC0);
    *m_UCSRB |= (1 << RXEN0) | (1 << TXEN0);
}

//-----------------------------------------------------------------------------------------------------
void CUart::Close(void)
{
    *m_UCSRB &= ~((1 << RXEN0) | (1 << RXCIE0));
    *m_UCSRB &= ~((1 << TXEN0) | (1 << TXCIE0));
    *m_UCSRB &= ~((1 << UDRIE0));
}

//-----------------------------------------------------------------------------------------------------
void CUart::Enable(void)
{
    *m_UCSRA |= (1 << RXC0);
    *m_UCSRB |= (1 << RXEN0) | (1 << RXCIE0);
}

//-----------------------------------------------------------------------------------------------------
void CUart::Disable(void)
{
    *m_UCSRB &= ~((1 << RXEN0) | (1 << RXCIE0));
}

//-----------------------------------------------------------------------------------------------------
void CUart::Rs485RtsOn(void)
{
    uint8_t uiData = m_rs485OutputPin;
    *m_rs485OutputPort |= (1 << uiData);
}

//-----------------------------------------------------------------------------------------------------
void CUart::Rs485RtsOff(void)
{
    uint8_t uiData = m_rs485OutputPin;
    *m_rs485OutputPort &= ~(1 << uiData);
}

//-----------------------------------------------------------------------------------------------------
void CUart::TransmitEnable(void)
{
    if (m_rs485DirectionPort)
    {
        Rs485RtsOn();
    }

    *m_UCSRA |= (1 << TXC0) | (1 << UDRE0);
    *m_UCSRB |= (1 << TXEN0) | (1 << UDRIE0);

}

//-----------------------------------------------------------------------------------------------------
void CUart::TransmitDisable(void)
{
    *m_UCSRB &= ~((1 << TXEN0) | (1 << TXCIE0) | (1 << UDRIE0));

    if (m_rs485DirectionPort)
    {
        Rs485RtsOff();
    }
}

//-----------------------------------------------------------------------------------------------------
int16_t CUart::Write(uint8_t *puiSource, uint16_t uiLength)
{
    m_puiTxBuffer = (uint8_t*)puiSource;
    m_nuiTxBuffByteCounter = uiLength;

    return 1;
}

//-----------------------------------------------------------------------------------------------------
int16_t CUart::Read(uint8_t *puiDestination, uint16_t uiLength)
{
    m_bfByteIsReceived = 0;

    if (m_bfRxBuffOverflow)
    {
        return -1;
    }

    if (uiLength <= m_nuiRxBuffByteCounter)
    {
        return -1;
    }
    else if (m_nuiRxBuffByteCounter)
    {
        CPlatform::InterruptDisable();

        for (int16_t i = 0; i < m_nuiRxBuffByteCounter; i++)
        {
            puiDestination[i] = m_auiIntermediateBuff[i];
        }

        uint8_t uiCounter = m_nuiRxBuffByteCounter;
        m_nuiRxBuffByteCounter = 0;

        CPlatform::InterruptEnable();

        return uiCounter;
    }
    else if (0 == m_nuiRxBuffByteCounter)
    {
        return 0;
    }
    return 0;
}

//-----------------------------------------------------------------------------------------------------
void CUart::UdreInterruptHandler(void)
{
    if (m_nuiTxBuffByteCounter == 0)
    {
        *m_UCSRB &= ~((1 << UDRIE0));
        *m_UCSRA |= (1 << TXC0);
        *m_UCSRB |= (1 << TXCIE0);
        return;
    }
    *m_UDR = *m_puiTxBuffer++;
    m_nuiTxBuffByteCounter--;
}

//-----------------------------------------------------------------------------------------------------
void CUart::TxcInterruptHandler(void)
{
    *m_UCSRB &= ~((1 << TXCIE0));
    m_bfFrameIsSended = 1;
    return;
}

//-----------------------------------------------------------------------------------------------------
void CUart::RecvInterruptHandler(void)
{
    // промежуточный буфер приёма переполнен?
    if (m_nuiRxBuffByteCounter >=
            UART_INTERMEDIATE_BUFF_LENGTH)
    {
        m_bfRxBuffOverflow = 1;
        m_bfByteIsReceived = 1;
    }
    else
    {
        m_auiIntermediateBuff[m_nuiRxBuffByteCounter++] = *m_UDR;
        m_bfByteIsReceived = 1;
    }
}

////-----------------------------------------------------------------------------------------------------
//// Прерывание по пустому регистру данных UDR
//#pragma vector = USART0_UDRE_vect
//__interrupt void SIG_UART0_DATA(void)
//{
//    CPlatform::m_pxUart0 -> UdreInterruptHandler();
//}
//
////-----------------------------------------------------------------------------------------------------
//// Прерывание по завершению передачи UART
//#pragma vector = USART0_TX_vect
//__interrupt void SIG_UART0_TXC(void)
//{
//    CPlatform::m_pxUart0 -> TxcInterruptHandler();
//}
//
////-----------------------------------------------------------------------------------------------------
//// Прерывание по завершению приема UART
//#pragma vector = USART0_RX_vect
//__interrupt void SIG_UART0_RECV(void)
//{
//    CPlatform::m_pxUart0 -> RecvInterruptHandler();
//}

//-----------------------------------------------------------------------------------------------------
// Прерывание по пустому регистру данных UDR
#pragma vector = USART1_UDRE_vect
__interrupt void SIG_UART1_DATA(void)
{
    CPlatform::m_pxUart1 -> UdreInterruptHandler();
}

//-----------------------------------------------------------------------------------------------------
// Прерывание по завершению передачи UART
#pragma vector = USART1_TX_vect
__interrupt void SIG_UART1_TXC(void)
{
    CPlatform::m_pxUart1 -> TxcInterruptHandler();
}

//-----------------------------------------------------------------------------------------------------
// Прерывание по завершению приема UART
#pragma vector = USART1_RX_vect
__interrupt void SIG_UART1_RECV(void)
{
    CPlatform::m_pxUart1 -> RecvInterruptHandler();
}

//-----------------------------------------------------------------------------------------------------



//----------------------------------------- EEPROM ----------------------------------------------------------------
uint8_t* CEeprom::m_puiBuffer;
uint16_t CEeprom::m_uiAddress;
uint16_t CEeprom::m_nuiBufferByteCounter;
uint16_t CEeprom::m_uiLength;
bool CEeprom::m_bBufferIsWrited;

//-----------------------------------------------------------------------------------------------------
CEeprom::CEeprom()
{

}

//-----------------------------------------------------------------------------------------------------
CEeprom::~CEeprom()
{

}

//-----------------------------------------------------------------------------------------------------
uint8_t CEeprom::Read(uint8_t *puiDestination, uint16_t uiSource, uint16_t uiLength)
{
    while (uiLength != 0)
    {
        *puiDestination++ = ReadByte(uiSource++);
        uiLength--;
    }
    return 1;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CEeprom::Write(uint16_t uiDestination, uint8_t *puiSource, uint16_t uiLength)
{
    while (uiLength != 0)
    {
        WriteByte((uiDestination++), (*puiSource++));
        uiLength--;
    }
    return 1;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CEeprom::ReadByte(uint16_t uiSource)
{
    __watchdog_reset();
    while (BitIsSet(EECR, EEWE))
    {
        __watchdog_reset();
    }
    __disable_interrupt();
    EEAR = uiSource;
    SetBit(EECR, EERE);
    __enable_interrupt();
    return EEDR;
}

//-----------------------------------------------------------------------------------------------------
void CEeprom::WriteByte(uint16_t uiDestination, uint8_t uiData)
{
    if (ReadByte(uiDestination) != uiData)
    {
        __watchdog_reset();
        while (BitIsSet(EECR, EEWE))
        {
            __watchdog_reset();
        }
        __disable_interrupt();
        EEAR = uiDestination;
        EEDR = uiData;
        EECR |= (1<<EEMWE);
        EECR |= (1<<EEWE);
        __enable_interrupt();
    }
}

//-----------------------------------------------------------------------------------------------------
void CEeprom::WriteInterrupt(uint16_t uiDestination, uint8_t *puiSource, uint16_t uiLength)
{
    SetAddress(uiDestination);
    SetBufferPointer(puiSource);
    SetLength(uiLength);
    SetBufferByteCounter(0);
}

//-----------------------------------------------------------------------------------------------------
// Прерывание по завершению записи.
void CEeprom::ReadyInterruptHandler(void)
{
    if (GetBufferByteCounter() < GetLength())
    {
        EEAR = GetAddress();
        SetAddress(GetAddress() + 1);
        EECR |= BIT(EERE);

        if (EEDR != GetBufferPointer()[GetBufferByteCounter()])
        {
            EEDR = GetBufferPointer()[GetBufferByteCounter()];
            EECR |= BIT(EEMWE);
            EECR |= BIT(EEWE);
        }

        SetBufferByteCounter(GetBufferByteCounter() + 1);
    }
    else
    {
        ReadyInterruptDisaable();
        EEAR   = 0x0000;			// Обнуляем для безопасности
        SetBufferIsWrited(true);
    }
}

//-----------------------------------------------------------------------------------------------------
// Прерывание по завершению записи.
#pragma vector = EE_READY_vect
__interrupt void EEPROM_EE_READY(void)
{
    CEeprom::ReadyInterruptHandler();
}

//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
// Основной блок БД прибора
TDataBase __flash CFlash::xMainDataBase =
{
    {
        2,1,48,false,false,false,0,0,{ 0,0,0,0,0,0,0,0,0,0,0,0,0 }
    },0x0A6F,

//    {
//        2,1,48,false,false,0,{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
//    },0x0A6F,

    {
        1,47,BIT(USBS1),0x73,BIT(CS02)|BIT(CS01),0x00,0x00
    },0x1B17,

    {
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
    },0xF0BE,

    {
        0, 1, 2, 3, 4, 5, 6, 7,
        8, 9, 10, 11, 12, 13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23,
        24, 25, 26, 27, 28, 29, 30, 31,
        32, 33, 34, 35, 36, 37, 38, 39,
        40, 41, 42, 43, 44, 45, 46, 47,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
        0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF
    },0x5AF9,

    {
        0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
        0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
        0x03,0x03,0x03,0x03,0x03,0x03,0x03,0x03,
        0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
        0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
        0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
        0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02,
        0x02,0x02,0x02,0x02,0x02,0x02,0x02,0x02
    },0x4139,

    {
        { 0x3E,0x3E,0x3E,0x3E,0x3C,0x3C,0x3C,0x3C },
        { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF },
        { 0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF }
    },0x6F4B,

    {
        0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
        0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
    },0xE899,

    {
        1,
        {
            {
                1,0x02,0x0010,0x20
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            }
        }
    },0xE223,

    {
        1,
        {
            {
                1,0x05,0x0000,0xFF
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            }
        }
    },0x9C7B,

    {
        1,
        {
            {
                1,0x05,0x0001,0xFF
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            },
            {
                0,0,0,0
            }
        }
    },0x6CFB,

    false, {0,0,0,0,0,0,0},0x0B40,
};

//-----------------------------------------------------------------------------------------------------
TDataBaseBlockPositionData __flash CFlash::axDataBaseBlocksPositionData[] =
{
    { 0, sizeof(xMainDataBase.DevConfig),	  offsetof(TDataBase,DevConfig)	 	},
    { 1, sizeof(xMainDataBase.MBSet),	  offsetof(TDataBase,MBSet)	 	},
    { 2, sizeof(xMainDataBase.ActivityLevel),	  offsetof(TDataBase,ActivityLevel)		},
    { 3, sizeof(xMainDataBase.AlarmWindowIndex),	  offsetof(TDataBase,AlarmWindowIndex)	 	},
    { 4, sizeof(xMainDataBase.AlarmType), offsetof(TDataBase,AlarmType) 	},
    { 5, sizeof(xMainDataBase.OutConfig),	  offsetof(TDataBase,OutConfig)  	},
    { 6, sizeof(xMainDataBase.Relay),	  offsetof(TDataBase,Relay)       	},
    { 7, sizeof(xMainDataBase.InputList),	  offsetof(TDataBase,InputList)  	},
    { 8, sizeof(xMainDataBase.ReceiptList), offsetof(TDataBase,ReceiptList)	},
    { 9, sizeof(xMainDataBase.UnsetList),	  offsetof(TDataBase,UnsetList)  	},
    { 10, sizeof(xMainDataBase.DeviceState),	  offsetof(TDataBase,DeviceState)  	}
};

//----------------------------------------- Flash ----------------------------------------------------------------
//CFlash::CFlash()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//CFlash::~CFlash()
//{
//
//}

//-----------------------------------------------------------------------------------------------------
uint8_t CFlash::Read(uint8_t *puiDestination, uint8_t __farflash *uiSource, uint16_t uiLength)
{
    // Скопируем данные из флеш в буфер Ram.
    for (uint16_t i = 0; i < uiLength; i++)
    {
        puiDestination[i] = uiSource[i];
    }
    return 1;
}

//-----------------------------------------------------------------------------------------------------
uint16_t CFlash::ReadBlock(uint8_t *puiDestination, uint8_t uiBlock)
{
    // Прочитаем блок из флеш вместе с Crc.
    Read(puiDestination,
         GetBlockPointer(uiBlock),
         (GetBlockLength(uiBlock) + CRC_LENGTH));

    // Получим контрольную сумму блока во флеш.
    uint16_t uiCrc = static_cast<uint16_t>(puiDestination[GetBlockLength(uiBlock)]);
    uiCrc |= (static_cast<uint16_t>(puiDestination[GetBlockLength(uiBlock) + 1]) << 8);
    // Вычислим контрольную сумму блока.
    // Блок не повреждён?
    if (uiCrc == usCrc16(puiDestination, GetBlockLength(uiBlock)))
    {
        return GetBlockLength(uiBlock);
    }
    else
    {
        CPss21::SetErrorCode(DB_ERROR);
        // Нет данных.
        return 0;
    }
}

//-----------------------------------------------------------------------------------------------------








//----------------------------------------- CSpi ----------------------------------------------------------------
CSpi::CSpi()
{

}

//-----------------------------------------------------------------------------------------------------
CSpi::~CSpi()
{

}

//-----------------------------------------------------------------------------------------------------
void CSpi::Init(void)
{
    // Master mode.
//    SPCR = (BIT(MSTR) | BIT(SPR1));		// master,  115200.
    SPCR = (BIT(MSTR) | BIT(SPR1) | BIT(SPR0));		// master,  57600.

    DDRB |= (Bit(MOSI) | Bit(SCK));
    PORTB |= (Bit(MOSI) | Bit(SCK));
};

//-----------------------------------------------------------------------------------------------------
void CSpi::Enable(void)
{
    // разрешим SPI.
    SPCR  |= BIT(SPE);
}

//-----------------------------------------------------------------------------------------------------
void CSpi::Disable(void)
{
    SPCR &= ~BIT(SPE);
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpi::Exchange(uint8_t uiData)
{
    SPDR = uiData;

    uint8_t uiGuardCounter = 0;

    while(!(SPSR & BIT(SPIF)))		// Ожидание конца передачи
    {
        CPlatform::WatchdogReset();

        if (uiGuardCounter < 200)
        {
            uiGuardCounter++;
        }
        else
        {
            return  SPDR;
        }
    };

    delay_us(100);

    return  SPDR;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpi::Exchange(uint8_t *puiDestination, uint8_t *pucSource, uint16_t uiLength)
{
    if (uiLength > BUFFER_LENGTH)
    {
        return 0;
    }

    for (uint16_t i = 0; i < uiLength; i++)
    {
        puiDestination[i] = Exchange(pucSource[i]);
    }
    return 1;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpi::Read(uint8_t *puiDestination, uint16_t uiLength)
{

    return 1;
}
//-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
// delay
void delay_ms(uint16_t millisecs)
{
    while(millisecs--)
    {
        delay_us(1000);
    }
}
void delay_s(uint16_t secs)
{
    while(secs--)
    {
        __delay_cycles(F_CPU);
    }
}
void delay_mins(uint16_t minutes)
{
    while(minutes--)
    {
        __delay_cycles(60*F_CPU);
    }
}

//-----------------------------------------------------------------------------------------------------
uint16_t CPlatform::m_uiSystemTick;
uint8_t CPlatform::m_uiWatchDogStepID;
//CUart* CPlatform::m_pxUart0;
CUart* CPlatform::m_pxUart1;

//-----------------------------------------------------------------------------------------------------
CPlatform::CPlatform()
{

}

//-----------------------------------------------------------------------------------------------------
CPlatform::~CPlatform()
{

}

//-----------------------------------------------------------------------------------------------------
void CPlatform::Init(void)
{
    SystemTickInit();
    StatusLedSetPinOutput();
    TxLedSetPinOutput();
    TxLedOff();
    KeyOneSetPinInput();
    KeyTwoSetPinInput();
    KeyThreeSetPinInput();
    ExternalKeySetPinInput();
    CPlatform::InterruptEnable();
}

// Сирена
//-----------------------------------------------------------------------------------------------------
void CPlatform::BuzzerTimerFrequencySet(uint16_t uiFrequency)
{
    unsigned short usCompareMatch;

    // half-period time.
    usCompareMatch = ((F_CPU / (2UL * uiFrequency)) - 1UL);
    // Срабатывает по Top совпадению значения в ICR3.
    // Если Top по совпадению значения в OCR3A, то нельзя использовать COM3A вывод.
    ICR3 = usCompareMatch * 2;
    OCR3A = usCompareMatch;
    OCR3B = usCompareMatch;

    // Fast PWM Mode Top OCRn, prescaller - 1,
    // Clear OC3B on compare match (set output to low level).
    // Set OC3A on compare match (set output to high level).
    TCCR3A = (1 << COM3B1) | (1 << COM3A1) | (1 << COM3A0) | (1 << WGM31);
    TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS30);
};

//-----------------------------------------------------------------------------------------------------
void CPlatform::BuzzerTimerStop(void)
{
    // timer off.
    TCCR3A &= ~((1 << COM3B1) | (1 << COM3A1) | (1 << COM3A0) | (1 << WGM31));
    TCCR3B &= ~((1 << WGM33) | (1 << WGM32) | (1 << CS30));
};

//-----------------------------------------------------------------------------------------------------
void CPlatform::SystemTickInit(void)
{
#define MAIN_TIMER_TICK_RATE_HZ 1000

//#define TIMER1_INTERRUPT
#define TIMER2_INTERRUPT


#ifdef TIMER2_INTERRUPT
    /* Hardware constants for timer 2. */
#define portCLEAR_COUNTER_ON_MATCH              ( ( unsigned char ) _BV(WGM21) )
#define portPRESCALE_64                         ( ( unsigned char ) (_BV(CS21) | _BV(CS20)) )
#define portCLOCK_PRESCALER                     ( ( unsigned long ) 64 )
#define portCOMPARE_MATCH_A_INTERRUPT_ENABLE    ( ( unsigned char ) _BV(OCIE2) )
#endif //TIMER2_INTERRUPT

#ifdef TIMER1_INTERRUPT
    /* Hardware constants for timer 1. */
#define portCLEAR_COUNTER_ON_MATCH              ( ( unsigned char ) _BV(WGM12) )
#define portPRESCALE_64                         ( ( unsigned char ) (_BV(CS11) | _BV(CS10)) )
#define portCLOCK_PRESCALER                     ( ( unsigned long ) 64 )
#define portCOMPARE_MATCH_A_INTERRUPT_ENABLE    ( ( unsigned char ) _BV(OCIE1A) )
#endif //TIMER1_INTERRUPT

#ifdef TIMER2_INTERRUPT

    /*
     * Setup timer 2 compare match A to generate a tick interrupt.
     */
//  TMR2 mega128a
    unsigned long ulCompareMatch;
    unsigned char ucLowByte;

    /* Using 16bit timer 1 to generate the tick.  Correct fuses must be
    selected for the configCPU_CLOCK_HZ clock. */

//ulCompareMatch  = (configCPU_CLOCK_HZ / prescaller) / period

    ulCompareMatch = F_CPU / MAIN_TIMER_TICK_RATE_HZ;

    /* We only have 16 bits so have to scale to get our required tick rate. */
    ulCompareMatch /= portCLOCK_PRESCALER;

    /* Adjust for correct value. */
    ulCompareMatch -= ( unsigned long ) 1;

    /* Setup compare match value for compare match A.  Interrupts are disabled
    before this is called so we need not worry here. */
    OCR2 = ulCompareMatch;

    /* Setup clock Source and compare match behaviour. */
    ucLowByte = portCLEAR_COUNTER_ON_MATCH | portPRESCALE_64;
    TCCR2 = ucLowByte;

    /* Enable the interrupt - this is okay as interrupt are currently globally
    disabled. */
    ucLowByte = TIMSK;
    ucLowByte |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
    TIMSK = ucLowByte;

#endif //TIMER2_INTERRUPT

#ifdef TIMER1_INTERRUPT

// mega128a
    unsigned long ulCompareMatch;
    unsigned char ucLowByte;

    /* Using 16bit timer 1 to generate the tick.  Correct fuses must be
    selected for the configCPU_CLOCK_HZ clock. */

    ulCompareMatch = CPlatform::F_CPU / MAIN_TIMER_TICK_RATE_HZ;

    /* We only have 16 bits so have to scale to get our required tick rate. */
    ulCompareMatch /= portCLOCK_PRESCALER;

    /* Adjust for correct value. */
    ulCompareMatch -= ( unsigned long ) 1;

    /* Setup compare match value for compare match A.  Interrupts are disabled
    before this is called so we need not worry here. */
    OCR1A = ulCompareMatch;

    /* Setup clock Source and compare match behaviour. */
    TCCR1A &= ~(_BV(WGM11) | _BV(WGM10));
    ucLowByte = portCLEAR_COUNTER_ON_MATCH | portPRESCALE_64;
    TCCR1B = ucLowByte;

    /* Enable the interrupt - this is okay as interrupt are currently globally
    disabled. */
    ucLowByte = TIMSK;
    ucLowByte |= portCOMPARE_MATCH_A_INTERRUPT_ENABLE;
    TIMSK = ucLowByte;

#endif //TIMER1_INTERRUPT

}

//-----------------------------------------------------------------------------------------------------
#ifdef TIMER1_INTERRUPT
// Прерывание TIMER1_COMPA_vect
__interrupt void SystemTickInterrupt(void)
{
    CPlatform::IncrementSystemTick();
}
#endif //TIMER1_INTERRUPT
//-----------------------------------------------------------------------------------------------------
#ifdef TIMER2_INTERRUPT
// Прерывание TIMER2_COMP_vect
#pragma vector = TIMER2_COMP_vect	// Прерывание по совпадению TMR2 с OCR2
__interrupt void SystemTickInterrupt(void)
{
    CPlatform::IncrementSystemTick();
}
#endif //TIMER2_INTERRUPT



