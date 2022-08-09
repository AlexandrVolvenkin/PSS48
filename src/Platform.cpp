//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "Platform.h"
#include "Pss21.h"


// ATMega128a
//-----------------------------------------------------------------------------------------------------
CUart::CUart()
{

}

//-----------------------------------------------------------------------------------------------------
CUart::CUart(volatile uint8_t *ubrrh, volatile uint8_t *ubrrl,
             volatile uint8_t *ucsra, volatile uint8_t *ucsrb,
             volatile uint8_t *ucsrc, volatile uint8_t *udr,
             volatile uint8_t *rs485ddr, volatile uint8_t rs485ddpin,
             volatile uint8_t *rs485port, volatile uint8_t rs485pin) :
    m_UBRRH(ubrrh), m_UBRRL(ubrrl), m_UCSRA(ucsra),
    m_UCSRB(ucsrb), m_UCSRC(ucsrc), m_UDR(udr),
    m_rs485ddr(rs485ddr), m_rs485ddpin(rs485ddpin), m_rs485port(rs485port), m_rs485pin(rs485pin)
{
    if (m_rs485ddr)
    {
        *m_rs485ddr |= _BV(m_rs485ddpin);
        *m_rs485port &= ~(_BV(m_rs485pin));
    }
}

//-----------------------------------------------------------------------------------------------------
CUart::~CUart()
{

}

//-----------------------------------------------------------------------------------------------------
void CUart::Init(uint32_t ulBaudRate,
                 uint8_t ucParity,
                 uint8_t ucDataBits,
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
//    switch (ucDataBits)
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
//    *m_UCSRB |= (1 << RXCIE0);
    *m_UCSRB |= (1 << RXEN0) | (1 << RXCIE0);
}

//-----------------------------------------------------------------------------------------------------
void CUart::Disable(void)
{
//    *m_UCSRB &= ~((1 << RXCIE0));
//    *m_UCSRB &= ~((1 << TXEN0) | (1 << TXCIE0));
    *m_UCSRB &= ~((1 << RXEN0) | (1 << RXCIE0));
}

//-----------------------------------------------------------------------------------------------------
void CUart::Rs485RtsOn(void)
{
    *m_rs485port |= (1 << m_rs485pin);
}

//-----------------------------------------------------------------------------------------------------
void CUart::Rs485RtsOff(void)
{
    *m_rs485port &= ~(1 << m_rs485pin);
}

//-----------------------------------------------------------------------------------------------------
void CUart::TransmitEnable(void)
{
    if (m_rs485ddr)
    {
        Rs485RtsOn();
    }

    *m_UCSRA |= (1 << TXC0) | (1 << UDRE0);
//    *m_UCSRB |= (1 << UDRIE0);
////    *m_UCSRA |= (1 << TXC0) | (1 << UDRE0);
    *m_UCSRB |= (1 << TXEN0) | (1 << UDRIE0);

}

//-----------------------------------------------------------------------------------------------------
void CUart::TransmitDisable(void)
{
//    *m_UCSRB &= ~((1 << TXCIE0) | (1 << UDRIE0));
////    *m_UCSRA &= ~(1 << UDRE0);
    *m_UCSRB &= ~((1 << TXEN0) | (1 << TXCIE0) | (1 << UDRIE0));

    if (m_rs485ddr)
    {
        Rs485RtsOff();
    }
}

//-----------------------------------------------------------------------------------------------------
int16_t CUart::Write(uint8_t *puiSourse, uint16_t uiLength)
{
    m_puiTxBuffer = (uint8_t*)puiSourse;
    m_nuiTxBuffByteCounter = uiLength;

//    *m_UCSRA &= ~(1 << RXC0);
//    *m_UCSRB &= ~((1 << RXEN0) | (1 << RXCIE0));
//
//    if (m_rs485ddr)
//    {
//        Rs485RtsOn();
//    }
////    UDR0 = *pucUsartTxBuff++;
//    //    UCSR0B |= (1 << TXEN0) | (1 << TXCIE0);
//    *m_UCSRA |= (1 << TXC0) | (1 << UDRE0);
//    *m_UCSRB |= (1 << TXEN0) | (1 << UDRIE0);

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
//
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
//    *m_UCSRB &= ~((1 << TXEN0) | (1 << TXCIE0));

//    if (m_rs485ddr)//debag//
//    {
//        Rs485RtsOff();
//    }
//    *m_UCSRA |= (1 << RXC0);
//    *m_UCSRB |= (1 << RXEN0) | (1 << RXCIE0);
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
        // не инкрементируем pucUsartRxBuff, чтобы не выйти за границы буфера.
        m_bfByteIsReceived = 1;
    }
    else
    {
//        m_puiRxBuffer[m_nuiRxBuffByteCounter++] = *m_UDR;
//        uint8_t uiTempUdr = *m_UDR;
//        if (uiTempUdr != 0)
//        {
//            uiTempUdr = uiTempUdr;
//        }
//        m_auiIntermediateBuff[m_nuiRxBuffByteCounter++] = uiTempUdr;
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
uint8_t CEeprom::Read(uint8_t *pucRamDestination, uint16_t uiEepromSourse, uint16_t nuiLength)
{
    while (nuiLength != 0)
    {
        *pucRamDestination++ = ReadByte(uiEepromSourse++);
        nuiLength--;
    }
    return 1;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CEeprom::Write(uint16_t uiEepromDestination, uint8_t *pucRamSourse, uint16_t nuiLength)
{
    while (nuiLength != 0)
    {
        WriteByte((uiEepromDestination++), (*pucRamSourse++));
        nuiLength--;
    }
    return 1;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CEeprom::ReadByte(uint16_t ui16EepromSourse)
{
    __watchdog_reset();
    while (BitIsSet(EECR, EEWE))
    {
        __watchdog_reset();
    }
    __disable_interrupt();
    EEAR = ui16EepromSourse;
    SetBit(EECR, EERE);
    __enable_interrupt();
    return EEDR;
}

//-----------------------------------------------------------------------------------------------------
void CEeprom::WriteByte(uint16_t ui16EepromDestination, uint8_t ucData)
{
    if (ReadByte(ui16EepromDestination) != ucData)
    {
        __watchdog_reset();
        while (BitIsSet(EECR, EEWE))
        {
            __watchdog_reset();
        }
        __disable_interrupt();
        EEAR = ui16EepromDestination;
        EEDR = ucData;
        EECR |= (1<<EEMWE);
        EECR |= (1<<EEWE);
        __enable_interrupt();
    }
}

//-----------------------------------------------------------------------------------------------------
void CEeprom::WriteInterrupt(uint16_t uiEepromDestination, uint8_t *pucRamSourse, uint16_t nuiLength)
{
    SetAddress(uiEepromDestination);
    SetBufferPointer(pucRamSourse);
    SetLength(nuiLength);
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

    DDRB |= (Bit(MOSI) | Bit(SCK));		// PB1 (SCK), PB2 (MOSI) - на выход
//    PORTB |= (Bit(MOSI) | Bit(SCK));

    SPCR  |= BIT(SPE);			// Активируем интерфейс SPI
};

//-----------------------------------------------------------------------------------------------------
void CSpi::Reset(void)
{
//    m_nuiBuffByteCounter = 0;
//    m_uiReceivedByteCounter = 0;
//    m_bfByteIsReceived = 0;
//    m_bfByteIsTransmited = 0;
//    m_bfDataExchangeInProgress = 0;
//    m_bfDataExchangeIsOccur = 0;
//    m_bfRxBuffOverflow = 0;
//    m_uiExchangeByte = 0;
}

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
    delay_us(30);
    SPDR = uiData;

    uint8_t uiGuardCounter = 0;

    while(!(SPSR & BIT(SPIF)))		// Ожидание конца передачи
    {
        CPlatform::WatchdogReset();

        if (uiGuardCounter < 100)
        {
            uiGuardCounter++;
        }
        else
        {
            return  SPDR;
        }
    };

    return  SPDR;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpi::Exchange(uint8_t *puiDestination, uint8_t *pucSourse, uint16_t nuiLength)
{
    if (nuiLength > BUFFER_LENGTH)
    {
        return 0;
    }

    for (uint16_t i = 0; i < nuiLength; i++)
    {
        puiDestination[i] = Exchange(pucSourse[i]);
    }
    return 1;
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpi::Read(uint8_t *puiDestination, uint16_t nuiLength)
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

    /* Setup clock Sourse and compare match behaviour. */
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

    /* Setup clock Sourse and compare match behaviour. */
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



