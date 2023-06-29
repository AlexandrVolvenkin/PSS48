//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef PLATFORM_H
#define PLATFORM_H

// ATMega128a
//-----------------------------------------------------------------------------------------------------
#include <intrinsics.h>
#include <stdint.h>
#include <pgmspace.h>
#include <ioavr.h>
//#include  <iom128a.h>
#include <inavr.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <yfuns.h>

#include "DataTypes.h"

//-----------------------------------------------------------------------------------------------------
#define F_CPU 7372800UL

#define delay_us(usecs) __delay_cycles((F_CPU/1000000)  *(usecs))

#define _delay_us delay_us
#define _delay_ms delay_ms;
#define usleep delay_us

void delay_ms(uint16_t millisecs);
void delay_s(uint16_t secs);
void delay_mins(uint16_t minutes);

//-----------------------------------------------------------------------------------------------------
// GPIO
#define   SetPinOut(reg, bit)          reg |= (1<<bit)
#define   SetPinIn(reg, bit)          reg &= (~(1<<bit))
#define   SetBit(reg, bit)          reg |= (1<<bit)
#define   ClearBit(reg, bit)       reg &= (~(1<<bit))
#define   InvBit(reg, bit)          reg ^= (1<<bit)
#define   BitIsSet(reg, bit)       ((reg & (1<<bit)) != 0)
#define   BitIsClear(reg, bit)    ((reg & (1<<bit)) == 0)

#define  SET_BIT(reg, bit)  SetBit(reg, bit)
#define  CLEAR_BIT(reg, bit)  ClearBit(reg, bit)
#define  SET_GPIO_PIN_OUTPUT(reg, bit)  SetPinOut(reg, bit)
#define  SET_GPIO_PIN_INPUT(reg, bit)  SetPinIn(reg, bit)
#define  SET_GPIO_PIN(reg, bit)  SetBit(reg, bit)
#define  CLEAR_GPIO_PIN(reg, bit)  ClearBit(reg, bit)
#define  BIT_IS_SET(reg, bit)       ((reg & (1<<bit)) != 0)
#define  BIT_IS_CLEAR(reg, bit)    ((reg & (1<<bit)) == 0)

#define	OUT_BYTE(addr, data)	addr = (data)
#define	IN_BYTE(addr)			(addr)

#define CheckBit(Address,Bit) (Address & (1<<Bit))
#define   Bit(bit)          (1<<bit)
#define   _Bit(bit)       (~(1<<bit))
#define   BIT(bit)          (1<<bit)
#define   _BIT(bit)       (~(1<<bit))
#define   _BV(bit)          (1<<bit)

#define RTS_LED_PIN_PORT  PORTD1
#define RTS_LED_PIN_DIRECTION  DDRD
#define RTS_LED_PIN  PORTD1

//---------------------------------------- UART -------------------------------------------------------------------------------
class CUart
{
public:
    enum
    {
        UART_MAX_BUFF_LENGTH = 256,
        UART_INTERMEDIATE_BUFF_LENGTH = 16
    };

    CUart();
    CUart(volatile uint8_t * , volatile uint8_t * ,
          volatile uint8_t * , volatile uint8_t * ,
          volatile uint8_t * , volatile uint8_t * ,
          volatile uint8_t * , volatile uint8_t ,
          volatile uint8_t * , volatile uint8_t );
    virtual ~CUart();

//-----------------------------------------------------------------------------------------------------
    void UdreInterruptHandler(void);
    void TxcInterruptHandler(void);
    void RecvInterruptHandler(void);
    void Init(uint32_t ,
              uint8_t ,
              uint8_t ,
              uint8_t  ,
              uint8_t *,
              uint8_t *);
    void Reset(void);
    void Open(void);
    void Close(void);
    void Enable(void);
    void Disable(void);
    void TransmitEnable(void);
    void TransmitDisable(void);
    void Rs485RtsOn(void);
    void Rs485RtsOff(void);
    int16_t Write(uint8_t * , uint16_t );
    int16_t Read(uint8_t * , uint16_t );
    uint8_t ByteIsReceived(void)
    {
        return m_bfByteIsReceived;
    }
    uint8_t FrameIsSended(void)
    {
        return m_bfFrameIsSended;
    };
    uint16_t GetFrameLength(void)
    {
        return m_nuiRxBuffByteCounter;
    };

//-----------------------------------------------------------------------------------------------------
private:
    volatile uint8_t* m_UBRRH;
    volatile uint8_t* m_UBRRL;
    volatile uint8_t* m_UCSRA;
    volatile uint8_t* m_UCSRB;
    volatile uint8_t* m_UCSRC;
    volatile uint8_t* m_UDR;
    volatile uint8_t* m_rs485DirectionPort;
    volatile uint8_t m_rs485DirectionPin;
    volatile uint8_t* m_rs485OutputPort;
    volatile uint8_t m_rs485OutputPin;

    uint8_t* m_puiTxBuffer;
    uint16_t m_nuiTxBuffByteCounter;
    uint8_t* m_puiRxBuffer;
    uint16_t m_nuiRxBuffByteCounter;
    uint8_t m_auiIntermediateBuff[UART_INTERMEDIATE_BUFF_LENGTH];
    bool m_bfByteIsReceived;
    bool m_bfFrameIsSended;
    bool m_bfRxBuffOverflow;

//protected:

};
//-----------------------------------------------------------------------------------------------------






////-----------------------------------------------------------------------------------------------------
//class CStorageDevice
//{
//public:
////    CStorageDevice();
////    virtual ~CStorageDevice();
//    virtual uint8_t Read(uint8_t * , uint16_t , uint16_t ) = 0;
//    virtual uint8_t Write(uint16_t , uint8_t * , uint16_t ) = 0;
//    virtual uint8_t ReadByte(uint16_t ) = 0;
//    virtual void WriteByte(uint16_t , uint8_t ) = 0;
//    virtual void ReadyInterruptHandler(void) = 0;
//    virtual void ReadyInterruptEnable(void) = 0;
//    virtual void ReadyInterruptDisaable(void) = 0;
//
//
//    virtual uint8_t* GetBufferPointer(void)
//    {
//        return m_puiBuffer;
//    };
//    virtual void SetBufferByteCounter(uint16_t nuiBufferByteCounter)
//    {
//        m_nuiBufferByteCounter = nuiBufferByteCounter;
//    };
//    virtual uint16_t GetBufferByteCounter(void)
//    {
//        return m_nuiBufferByteCounter;
//    };
//
//    virtual void SetLength(uint16_t uiLength)
//    {
//        m_uiLength = uiLength;
//    };
//    virtual uint16_t GetLength(void)
//    {
//        return m_uiLength;
//    };
//
//    virtual void SetBufferIsWrited(bool bBufferIsWrited)
//    {
//        m_bBufferIsWrited = bBufferIsWrited;
//    };
//    virtual bool GetBufferIsWrited(void)
//    {
//        return m_bBufferIsWrited;
//    };
//
//    virtual void StartWrite(void)
//    {
//        SetBufferIsWrited(false);
//        ReadyInterruptEnable();
//    };
//
////    virtual uint8_t* GetBufferPointer(void) = 0;
////    virtual void SetBufferByteCounter(uint16_t nuiBufferByteCounter) = 0;
////    virtual uint16_t GetBufferByteCounter(void) = 0;
////    virtual void SetLength(uint16_t uiLength) = 0;
////    virtual uint16_t GetLength(void) = 0;
////    virtual void SetBufferIsWrited(bool bBufferIsWrited) = 0;
////    virtual bool GetBufferIsWrited(void) = 0;
//    virtual bool IsReadyToWrite(void) = 0;
//
//private:
//    uint8_t* m_puiBuffer;
//    static uint16_t m_uiAddress;
//    uint16_t m_nuiBufferByteCounter;
//    uint16_t m_uiLength;
//    bool m_bBufferIsWrited;
//};
////-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
class CEeprom
{
public:
    CEeprom();
    virtual ~CEeprom();
    static uint8_t Read(uint8_t * , uint16_t , uint16_t );
    static uint8_t Write(uint16_t , uint8_t * , uint16_t );
    static void WriteInterrupt(uint16_t , uint8_t * , uint16_t );
    static uint8_t ReadByte(uint16_t );
    static void WriteByte(uint16_t , uint8_t );
    static void ReadyInterruptHandler(void);

    static void ReadyInterruptEnable(void)
    {
        EECR |= (1 << EERIE);
    };
    static void ReadyInterruptDisaable(void)
    {
        EECR &= ~(1 << EERIE);
    };

    static bool IsReadyToWrite(void)
    {
        if (BitIsSet(EECR, EEWE))
        {
            return false;
        }
        else
        {
            return true;
        }
    };

    static uint8_t* GetBufferPointer(void)
    {
        return m_puiBuffer;
    };
    static void  SetBufferPointer(uint8_t* puiBuffer)
    {
        m_puiBuffer = puiBuffer;
    };

    static void SetAddress(uint16_t uiAddress)
    {
        m_uiAddress = uiAddress;
    };
    static uint16_t GetAddress(void)
    {
        return m_uiAddress;
    };

    static void SetBufferByteCounter(uint16_t nuiBufferByteCounter)
    {
        m_nuiBufferByteCounter = nuiBufferByteCounter;
    };
    static uint16_t GetBufferByteCounter(void)
    {
        return m_nuiBufferByteCounter;
    };

    static void SetLength(uint16_t uiLength)
    {
        m_uiLength = uiLength;
    };
    static uint16_t GetLength(void)
    {
        return m_uiLength;
    };

    static void SetBufferIsWrited(bool bBufferIsWrited)
    {
        m_bBufferIsWrited = bBufferIsWrited;
    };
    static bool GetBufferIsWrited(void)
    {
        return m_bBufferIsWrited;
    };

    static void StartWrite(void)
    {
        SetBufferIsWrited(false);
        ReadyInterruptEnable();
    };

private:
    static uint8_t* m_puiBuffer;
    static uint16_t m_uiAddress;
    static uint16_t m_nuiBufferByteCounter;
    static uint16_t m_uiLength;
    static bool m_bBufferIsWrited;
};

//-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
class CFlash
{
public:

    enum
    {
        // Сохраняемый буфер должен быть на CRC_LENGTH больше.
        CRC_LENGTH = 2,
    };

//    CFlash();
//    virtual ~CFlash();
    static uint8_t Read(uint8_t *puiDestination, uint8_t __farflash *uiSourse, uint16_t uiLength);
    static uint16_t ReadBlock(uint8_t *puiDestination, uint8_t uiBlock);

    static uint16_t GetBlockLength(uint8_t uiBlock)
    {
        return axDataBaseBlocksPositionData[uiBlock].Size;
    };

    static uint16_t GetBlockOffset(uint8_t uiBlock)
    {
        return axDataBaseBlocksPositionData[uiBlock].Offset;
    };

    // Получим указатель на блок БД во флеш.
    static uint8_t __farflash* GetBlockPointer(uint8_t uiBlock)
    {
        return &(reinterpret_cast<__farflash uint8_t*>(&xMainDataBase)[GetBlockOffset(uiBlock)]);
    };

private:
    static __flash TDataBase CFlash::xMainDataBase;
    static __flash TDataBaseBlockPositionData CFlash::axDataBaseBlocksPositionData[];
};

//-----------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------------
enum
{
    SS5 = 0,     // PD0 - Вход прерывания от Master
    SCK = 1,     // PB1 - Вход для синхроимпульсов
    MOSI = 2,    // PB2 - Вход SPI
    MISO = 3    // PB3 - Выход SPI
};

class CSpi
{
public:
    CSpi();
    virtual ~CSpi();

    static void Init(void);
    static void Enable(void);
    static void Disable(void);
    static uint8_t Exchange(uint8_t );
    static uint8_t Exchange(uint8_t * , uint8_t * , uint16_t );
    static uint8_t Read(uint8_t * , uint16_t );
    static uint8_t Write(uint8_t * , uint16_t );

    static const uint8_t BUFFER_LENGTH = 64;
private:

};
//-----------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------------
class CPlatform
{
public:
    CPlatform();
    virtual ~CPlatform();

//-----------------------------------------------------------------------------------------------------
    static void WatchdogReset(void)
    {
        __watchdog_reset();
    }

//-----------------------------------------------------------------------------------------------------
    static void WatchdogEnable(void)
    {
        enum
        {
            WDTO_15MS = 0,
            WDTO_30MS = 1,
            WDTO_60MS = 2,
            WDTO_120MS = 3,
            WDTO_250MS = 4,
            WDTO_500MS = 5,
            WDTO_1S = 6,
            WDTO_2S = 7
        };
        __watchdog_reset();
        /* Write logical one to WDCE and WDE */
        WDTCR |= (1<<WDCE) | (1<<WDE);
        WDTCR |= (WDTO_2S & 0x07);
    }

//-----------------------------------------------------------------------------------------------------
    static void InterruptEnable(void)
    {
        __enable_interrupt();
    }

//-----------------------------------------------------------------------------------------------------
    static void InterruptDisable(void)
    {
        __disable_interrupt();
    }

//-----------------------------------------------------------------------------------------------------
    static void IncrementSystemTick(void)
    {
        m_uiSystemTick++;
    }

//-----------------------------------------------------------------------------------------------------
    static uint16_t GetSystemTick(void)
    {
        return m_uiSystemTick;
    }

//-----------------------------------------------------------------------------------------------------
    static void StatusLedSetPinOutput(void)
    {
        DDRF |=  BIT(DDF7);
//        DDRE |=  BIT(DDE3);
    };

//-----------------------------------------------------------------------------------------------------
    static void StatusLedOn(void)
    {
        PORTF &= ~BIT(PF7);
//        PORTE &= ~BIT(PE3);
    };

//-----------------------------------------------------------------------------------------------------
    static void StatusLedOff(void)
    {
        PORTF |=  BIT(PF7);
//        PORTE |=  BIT(PE3);
    };

//-----------------------------------------------------------------------------------------------------
    static void TxLedSetPinOutput(void)
    {
        DDRF |=  BIT(DDF6);
//        DDRE |=  BIT(DDE4);
    };

//-----------------------------------------------------------------------------------------------------
    static void TxLedOn(void)
    {
        PORTF &= ~BIT(PF6);
//        PORTE &= ~BIT(PE4);
    };

//-----------------------------------------------------------------------------------------------------
    static void TxLedOff(void)
    {
        PORTF |=  BIT(PF6);
//        PORTE |=  BIT(PE4);
    };

//-----------------------------------------------------------------------------------------------------




// Сирена
//-----------------------------------------------------------------------------------------------------
    static void BuzzerClockASetPinOutput(void)
    {
        DDRE |=  BIT(DDE3);
    };

//-----------------------------------------------------------------------------------------------------
    static void BuzzerClockAOn(void)
    {
        PORTE |= BIT(PORTE3);
    };

//-----------------------------------------------------------------------------------------------------
    static void BuzzerClockAOff(void)
    {
        PORTE &= ~BIT(PORTE3);
    };
//-----------------------------------------------------------------------------------------------------
    static void BuzzerClockBSetPinOutput(void)
    {
        DDRE |= BIT(DDE4);
    };

//-----------------------------------------------------------------------------------------------------
    static void BuzzerClockBOn(void)
    {
        PORTE |= BIT(PORTE4);
    };

//-----------------------------------------------------------------------------------------------------
    static void BuzzerClockBOff(void)
    {
        PORTE &= ~BIT(PORTE4);
    };
//-----------------------------------------------------------------------------------------------------




// Клавиатура.
//-----------------------------------------------------------------------------------------------------
    static void KeyOneSetPinInput(void)
    {
        DDRC &= ~BIT(DDC2);
    };

//-----------------------------------------------------------------------------------------------------
    static uint8_t KeyOneState(void)
    {
        return BitIsClear(PINC, PINC2);
    };

//-----------------------------------------------------------------------------------------------------
    static void KeyTwoSetPinInput(void)
    {
        DDRC &= ~BIT(DDC1);
    };

//-----------------------------------------------------------------------------------------------------
    static uint8_t KeyTwoState(void)
    {
        return BitIsClear(PINC, PINC1);
    };

//-----------------------------------------------------------------------------------------------------
    static void KeyThreeSetPinInput(void)
    {
        DDRC &= ~BIT(DDC0);
    };

//-----------------------------------------------------------------------------------------------------
    static uint8_t KeyThreeState(void)
    {
        return BitIsClear(PINC, PINC0);
    };

//-----------------------------------------------------------------------------------------------------
    static void ExternalKeySetPinInput(void)
    {
        DDRG &= ~BIT(DDG0);
    };

//-----------------------------------------------------------------------------------------------------
    static uint8_t ExternalKeyState(void)
    {
        return BitIsClear(PING, PING0);
    };

//-----------------------------------------------------------------------------------------------------





// LedDriver DM134.
//-----------------------------------------------------------------------------------------------------
    static void LedDriverClockSetPinOutput(void)
    {
        DDRF |=  BIT(DDF2);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverClockOn(void)
    {
        PORTF |=  BIT(PF2);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverClockOff(void)
    {
        PORTF &= ~BIT(PF2);
    };
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
    static void LedDriverSerialInSetPinOutput(void)
    {
        DDRF |=  BIT(DDF4);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverSerialInOn(void)
    {
        PORTF |=  BIT(PF4);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverSerialInOff(void)
    {
        PORTF &= ~BIT(PF4);
    };
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
    static void LedDriverLatchSetPinOutput(void)
    {
        DDRF |=  BIT(DDF1);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverLatchOn(void)
    {
        PORTF &= ~BIT(PF1);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverLatchOff(void)
    {
        PORTF |=  BIT(PF1);
    };
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable1SetPinOutput(void)
    {
        DDRF |=  BIT(DDF0);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable1On(void)
    {
        PORTF &= ~BIT(PF0);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable1Off(void)
    {
        PORTF |=  BIT(PF0);
    };
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable2SetPinOutput(void)
    {
        DDRF |=  BIT(DDF5);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable2On(void)
    {
        PORTF &= ~BIT(PF5);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable2Off(void)
    {
        PORTF |=  BIT(PF5);
    };
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable3SetPinOutput(void)
    {
        DDRE |=  BIT(DDE6);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable3On(void)
    {
        PORTE &= ~BIT(PE6);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable3Off(void)
    {
        PORTE |=  BIT(PE6);
    };
//-----------------------------------------------------------------------------------------------------

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable4SetPinOutput(void)
    {
        DDRE |=  BIT(DDE7);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable4On(void)
    {
        PORTE &= ~BIT(PE7);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverEnable4Off(void)
    {
        PORTE |=  BIT(PE7);
    };

//-----------------------------------------------------------------------------------------------------
    static void LedDriverDelay1uS()
    {
        __delay_cycles(1);
    }

//-----------------------------------------------------------------------------------------------------
    static void LedDriverDelay5uS()
    {
        __delay_cycles(5);
    }
//-----------------------------------------------------------------------------------------------------


// Spi
//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress0SetPinOutput(void)
    {
        DDRD |=  BIT(DDD7);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress0On(void)
    {
        PORTD |=  BIT(PD7);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress0Off(void)
    {
        PORTD &= ~BIT(PD7);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress1SetPinOutput(void)
    {
        DDRD |=  BIT(DDD6);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress1On(void)
    {
        PORTD |=  BIT(PD6);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress1Off(void)
    {
        PORTD &= ~BIT(PD6);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress2SetPinOutput(void)
    {
        DDRD |=  BIT(DDD5);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress2On(void)
    {
        PORTD |=  BIT(PD5);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress2Off(void)
    {
        PORTD &= ~BIT(PD5);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress3SetPinOutput(void)
    {
        DDRD |=  BIT(DDD4);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress3On(void)
    {
        PORTD |=  BIT(PD4);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectAddress3Off(void)
    {
        PORTD &= ~BIT(PD4);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectEnableSetPinOutput(void)
    {
        DDRD |=  BIT(DDD1);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectEnableOn(void)
    {
        PORTD |=  BIT(PD1);
    };

//-----------------------------------------------------------------------------------------------------
    static void SpiSlaveSelectEnableOff(void)
    {
        PORTD &= ~BIT(PD1);
    };

//-----------------------------------------------------------------------------------------------------

    static void Init(void);
    static void SystemTickInit(void);
    static void BuzzerTimerFrequencySet(uint16_t );
    static void BuzzerTimerStop(void);

//    static CUart* m_pxUart0;
    static CUart* m_pxUart1;

//-----------------------------------------------------------------------------------------------------
    static uint8_t m_uiWatchDogStepID;
private:
    static uint16_t m_uiSystemTick;

protected:
};
//-----------------------------------------------------------------------------------------------------
#endif // PLATFORM_H
