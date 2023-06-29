//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CDISCRETEINPUT_H
#define CDISCRETEINPUT_H

#include <stdint.h>
#include "Device.h"
#include "Driver.h"
#include "DataTypes.h"

//-----------------------------------------------------------------------------------------------------
class CDiscreteInput : public CDevice
{
public:
    CDiscreteInput();
    virtual ~CDiscreteInput();
protected:
private:
};

//-----------------------------------------------------------------------------------------------------
class CDiscreteInputDriver : public CDriver
{
public:

//    CDiscreteInputDriver(uint8_t uiType);
//    CDiscreteInputDriver();
//    virtual ~CDiscreteInputDriver();
//    void Init(void);
//    void Allocate(TMemoryAllocationConext &xMemoryAllocationConext);
//    uint16_t ReportType(uint8_t * , uint16_t );
//    uint8_t DataExchange(void);

protected:
private:
    uint8_t m_uiAddress;
    uint8_t *m_puiRxBuffer;
    uint8_t *m_puiTxBuffer;
    uint8_t *m_puiDiscreteInputs;

    friend class CModbusDiscreteInputDriver;
};

//-----------------------------------------------------------------------------------------------------
class CModbusDiscreteInputDriver : public CDiscreteInputDriver
{
public:

    CModbusDiscreteInputDriver(uint8_t uiType);
    CModbusDiscreteInputDriver();
    virtual ~CModbusDiscreteInputDriver();
    void Init(void);
    void Allocate(TMemoryAllocationConext &xMemoryAllocationConext);
    uint16_t ReportType(uint8_t * , uint16_t );
    uint8_t DataExchange(void);

protected:
private:
};

//-----------------------------------------------------------------------------------------------------
#endif // CDISCRETEINPUT_H
