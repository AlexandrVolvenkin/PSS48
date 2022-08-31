//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CMODBUSRTU_H
#define CMODBUSRTU_H

#include <stdint.h>
#include "Modbus.h"
#include "Configuration.h"
//#include "Pss21.h"

/* Modbus_Application_Protocol_V1_1b.pdf Chapter 4 Section 1 Page 5
 * RS232 / RS485 ADU = 253 bytes + slave (1 byte) + CRC (2 bytes) = 256 bytes
 */
//#define MODBUS_RTU_MAX_ADU_LENGTH  256

#define _MODBUS_RTU_35_TIMEOUT        (((1000000UL / MODBUS_RTU_BAUD_RATE) * 8UL * 4UL) / 1000) + 1

#define _MODBUS_RTU_HEADER_LENGTH      1
#define _MODBUS_RTU_PRESET_REQ_LENGTH  6
#define _MODBUS_RTU_PRESET_RSP_LENGTH  2

#define _MODBUS_RTU_CHECKSUM_LENGTH    2

#define MODBUS_RTU_RS232 0
#define MODBUS_RTU_RS485 1

//enum
//{
//    MODBUS_RTU_MAX_ADU_LENGTH = 256
//};

//-----------------------------------------------------------------------------------------------------
class CModbusRTU : virtual public CModbus
{
public:
    CModbusRTU();
//    CModbusRTU(CUart* pxDevice,
//               uint32_t uiBaudRate,
//               char cParity,
//               uint8_t uiDataBit,
//               uint8_t uiStopBit,
//               uint8_t *puiRxBuffer,
//               uint8_t *puiTxBuffer);
    virtual ~CModbusRTU();
    void Init(CUart* pxDevice,
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
              uint16_t uiInputRegistersNumber);
    void Reset(void);
    void Open(void);
    void Close(void);
    void ReceiveEnable(void);
    void ReceiveDisable(void);
    void TransmitEnable(void);
    void TransmitDisable(void);
    int16_t RequestBasis(uint8_t uiSlave,
                         uint8_t uiFunctionCode,
                         uint16_t uiAddress,
                         uint16_t uiBitNumber,
                         uint8_t *puiRequest);
    int16_t ResponseBasis(uint8_t , uint8_t , uint8_t * );
    int16_t Tail(uint8_t * , uint16_t );
    int16_t Send(uint8_t * , uint16_t );
    uint8_t MessageIsSended(void);
//    int16_t Receive(void);
    uint8_t Select(void);
    int16_t Receive(uint8_t * , uint16_t );
    uint8_t FrameIsReceived(void);
    uint8_t ReceiveTimeIsOver(void);
    uint8_t ConfirmationReceiveTimeIsOver(void);
    uint8_t TransmitDelayTimeIsOver(void);
    int8_t TimeIsOver(uint16_t uiTimeout);
    void GetSystemTime(void);
    uint16_t GetFrameLength(void);
    int8_t FrameCheck(void);
    int8_t FrameCheck(uint8_t * , uint16_t );
    void Fsm(void);
//    void TaskFsmSlave(void);
//    void TaskFsmMaster(void);

    uint16_t HEADER_LENGTH(void)
    {
        return 1;
    };
    uint16_t CRC_LENGTH(void)
    {
        return 2;
    };
//    #define HEADER_LENGTH HEADER_LENGTH()
//    #define CRC_LENGTH CRC_LENGTH()
//    static const uint8_t HEADER_LENGTH = 1;
//    static const uint8_t CRC_LENGTH = 2;

protected:
private:
    CUart* m_pxDevice;
    /* Bauds: 9600, 19200, 57600, 115200, etc */
    uint32_t m_uiBaudRate;
    /* Data bit */
    uint8_t m_uiDataBit;
    /* Stop bit */
    uint8_t m_uiStopBit;
    /* Parity: 'N', 'O', 'E' */
    char m_cParity;
    // таймоут по отсутствию следующего байта 3.5 бода.
    uint16_t m_uiGuardTimeout;
//    const static uint16_t m_uiGuardTimeout = _MODBUS_RTU_35_TIMEOUT;
    // таймоут по отсутствию запроса.
    const static uint16_t m_uiReceiveTimeout = 15000;
    // таймоут по отсутствию подтверждения.
    const static uint16_t m_uiConfirmationTimeout = 1000;
    const static uint16_t m_uiTransmitDelayTimeout = 5;

};

//-----------------------------------------------------------------------------------------------------



//-----------------------------------------------------------------------------------------------------
#endif // CMODBUSRTU_H
