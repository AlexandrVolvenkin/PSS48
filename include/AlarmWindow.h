//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CALARMWINDOW_H
#define CALARMWINDOW_H

#include <stdint.h>

#include "Configuration.h"

//-----------------------------------------------------------------------------------------------------
class CAlarmWindow
{
public:
    CAlarmWindow();
    virtual ~CAlarmWindow();
    void SetActivityState(uint8_t uiData)
    {
        m_uiActivityState = uiData;
    };
    uint8_t GetActivityState(void)
    {
        return m_uiActivityState;
    };
    void SetSavedActivityState(uint8_t uiData)
    {
        m_uiSavedActivityState = uiData;
    };
    uint8_t GetSavedActivityState(void)
    {
        return m_uiSavedActivityState;
    };

    void SetAlarmType(uint8_t uiData)
    {
        m_uiAlarmType = uiData;
    };
    uint8_t GetAlarmType(void)
    {
        return m_uiAlarmType;
    };

    void SetSavedAlarmType(uint8_t uiData)
    {
        m_uiSavedAlarmType = uiData;
    };
    uint8_t GetSavedAlarmType(void)
    {
        return m_uiSavedAlarmType;
    };

protected:
private:
    uint8_t m_uiActivityState;
    uint8_t m_uiSavedActivityState;
    // Тип сигнализации.
    uint8_t m_uiAlarmType;
    uint8_t m_uiSavedAlarmType;
};

//-----------------------------------------------------------------------------------------------------
#endif // CALARMWINDOW_H
