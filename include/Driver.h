//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CDRIVER_H
#define CDRIVER_H

#include <stdint.h>
#include "DataTypes.h"

//-----------------------------------------------------------------------------------------------------
class CDriver
{
public:
    virtual void Allocate(TMemoryAllocationConext &xMemoryAllocationConext) = 0;
    virtual uint8_t DataExchange(void) = 0;

    void SetReceipt(uint8_t uiData)
    {
        m_uiReceipt = uiData;
    };
    uint8_t GetReceipt(void)
    {
        return m_uiReceipt;
    };
    void SetReset(uint8_t uiData)
    {
        m_uiReset = uiData;
    };
    uint8_t GetReset(void)
    {
        return m_uiReset;
    };

    void SetModbusReceipt(uint8_t uiData)
    {
        m_uiModbusReceipt = uiData;
    };
    uint8_t GetModbusReceipt(void)
    {
        return m_uiModbusReceipt;
    };
    void SetModbusReset(uint8_t uiData)
    {
        m_uiModbusReset = uiData;
    };
    uint8_t GetModbusReset(void)
    {
        return m_uiModbusReset;
    };

    void SetErrorAlarmData(uint8_t uiData)
    {
        *m_puiErrorAlarmDataArray = uiData;
    };

protected:
private:
    uint8_t m_uiType;
    uint8_t m_uiReceipt;
    uint8_t m_uiReset;
    uint8_t m_uiModbusReceipt;
    uint8_t m_uiModbusReset;
    uint8_t *m_puiErrorCode;
    uint8_t* m_puiErrorAlarmDataArray;

    friend class CMvsn21Driver;
    friend class CModuleMrXXDriver;
};

//-----------------------------------------------------------------------------------------------------
#endif // CDRIVER_H
