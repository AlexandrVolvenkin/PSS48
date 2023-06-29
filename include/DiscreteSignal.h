//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CDISCRETESYGNAL_H
#define CDISCRETESYGNAL_H

#include <stdint.h>

#include "Configuration.h"

//#define DISCRETE_INPUT_RELAY_OUTPUT_QUANTITY DO_VALUE_BIT_ARRAY_LENGTH
// норма.
#define FLOW_CONTROL_NORMA 1
// новое нарушение.
#define FLOW_CONTROL_NEW_VIOLATION 2
// не новое нарушение.
#define FLOW_CONTROL_NOT_NEW_VIOLATION 3


//-----------------------------------------------------------------------------------------------------
class CDiscreteSignal
{
public:
    CDiscreteSignal();
    virtual ~CDiscreteSignal();
    uint8_t IsActive(void);
    void SetRelayOut(uint8_t uiModule, uint8_t uiRelay);
    uint8_t GetRelayOut(uint8_t uiModule, uint8_t uiRelay);

    void SetActivityLevel(uint8_t uiData)
    {
        m_uiActivityLevel = uiData;
    };
    uint8_t GetActivityLevel(void)
    {
        return m_uiActivityLevel;
    };

    void SetActivityState(uint8_t uiData)
    {
        m_uiActivityState = uiData;
    };
    uint8_t GetActivityState(void)
    {
        return m_uiActivityState;
    };

    void SetAlarmState(uint8_t uiData)
    {
        m_uiAlarmState = uiData;
    };
    uint8_t GetAlarmState(void)
    {
        return m_uiAlarmState;
    };

    void SetAlarmType(uint8_t uiData)
    {
        m_uiAlarmType = uiData;
    };
    uint8_t GetAlarmType(void)
    {
        return m_uiAlarmType;
    };

//    void SetNoSound(uint8_t uiData)
//    {
//        m_uiNoSound = uiData;
//    };
//    uint8_t GetNoSound(void)
//    {
//        return m_uiNoSound;
//    };

    void SetAlarmWindowIndex(uint8_t uiData)
    {
        m_uiAlarmWindowIndex = uiData;
    };
    uint8_t GetAlarmWindowIndex(void)
    {
        return m_uiAlarmWindowIndex;
    };

    void SetDiscreteStateSourse(uint8_t *puiPointer)
    {
        m_puiDiscreteStateSourse = puiPointer;
    };
    uint8_t* GetDiscreteStateSourse(void)
    {
        return m_puiDiscreteStateSourse;
    };
    uint8_t GetDiscreteState(void)
    {
        return *m_puiDiscreteStateSourse;
    };

protected:
private:
    // Уровень дискретного сигнала интерпретируемый как активный.
    uint8_t m_uiActivityLevel;
    uint8_t m_uiAlarmType;
//    uint8_t m_uiNoSound;
    uint8_t m_uiActivityState;
    uint8_t m_uiAlarmState;

    uint8_t m_uiAlarmWindowIndex;
    // Выходы на МР.
    uint8_t m_auiRelayOut[DISCRETE_OUTPUT_MODULE_MAX_NUMBER];
    // Источник дискретного сигнала.
    uint8_t *m_puiDiscreteStateSourse;
};

//-----------------------------------------------------------------------------------------------------
#endif // CDISCRETESYGNAL_H
