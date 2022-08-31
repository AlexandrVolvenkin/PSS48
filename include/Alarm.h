//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CALARM_H
#define CALARM_H

#include <stdint.h>

#include "Configuration.h"
#include "AlarmWindow.h"

//-----------------------------------------------------------------------------------------------------
class CAlarmDfa : public CDfaLite
{
public:
    enum
    {
        START = 0,
        ACTIVE_STATE_WAITING,
        RECEIPT_OR_RESET_WAITING,
        RECEIPTED_RESET_OR_NOT_ACTIVE_STATE_WAITING,
        RESETED_NOT_ACTIVE_STATE_WAITING,
        RECEIPTED_RESET_WAITING,
        NOT_ACTIVE_STATE_WAITING,
    };

    enum
    {
        NOT_NEW_VIOLATION = 0,
        NEW_VIOLATION = 1,
    };

    virtual uint8_t ALARM_TYPE(void)
    {
        return NORMAL;
    };

    virtual uint8_t ACTIVE_LEVEL(void)
    {
        return 0;
    };

    CAlarmDfa();
    virtual ~CAlarmDfa();
    virtual void Fsm(void);

    void SetDiscreteStateIndex(uint8_t uiDiscreteStateIndex)
    {
        m_uiDiscreteStateIndex = uiDiscreteStateIndex;
    };
    uint8_t GetDiscreteStateIndex(void)
    {
        return m_uiDiscreteStateIndex;
    };

    void SetAlarmWindowIndex(uint8_t uiAlarmWindowIndex)
    {
        m_uiAlarmWindowIndex = uiAlarmWindowIndex;
    };
    uint8_t GetAlarmWindowIndex(void)
    {
        return m_uiAlarmWindowIndex;
    };

    uint8_t* GetLinkedDiscreteOutputsPointer(void)
    {
        return m_auiLinkedDiscreteOutputs;
    };

protected:
private:
    // Индекс окна извещателя - светового табло.
    uint8_t m_uiAlarmWindowIndex;
    // Выходы на МР.
    uint8_t m_auiLinkedDiscreteOutputs[DISCRETE_OUTPUT_MODULE_MAX_NUMBER];
    // Источник дискретного сигнала.
    uint8_t m_uiDiscreteStateIndex;
};
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
class CNormalAlarmDfa : public CAlarmDfa
{
public:

    uint8_t ALARM_TYPE(void)
    {
        return NORMAL;
    };

    uint8_t ACTIVE_LEVEL(void)
    {
        return 0;
    };

    CNormalAlarmDfa();
    virtual ~CNormalAlarmDfa();

protected:
private:
};
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
class CPreventiveAlarmLowLevelDfa : public CAlarmDfa
{
public:

    uint8_t ALARM_TYPE(void)
    {
        return PREVENTIVE;
    };

    uint8_t ACTIVE_LEVEL(void)
    {
        return 0;
    };

    CPreventiveAlarmLowLevelDfa();
    virtual ~CPreventiveAlarmLowLevelDfa();


protected:
private:
};
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
class CPreventiveAlarmHighLevelDfa : public CAlarmDfa
{
public:

    uint8_t ALARM_TYPE(void)
    {
        return PREVENTIVE;
    };

    uint8_t ACTIVE_LEVEL(void)
    {
        return 1;
    };

    CPreventiveAlarmHighLevelDfa();
    virtual ~CPreventiveAlarmHighLevelDfa();

protected:
private:
};
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
class CEmergencyAlarmLowLevelDfa : public CAlarmDfa
{
public:

    uint8_t ALARM_TYPE(void)
    {
        return EMERGENCY;
    };

    uint8_t ACTIVE_LEVEL(void)
    {
        return 0;
    };

    CEmergencyAlarmLowLevelDfa();
    virtual ~CEmergencyAlarmLowLevelDfa();

protected:
private:
};
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
class CEmergencyAlarmHighLevelDfa : public CAlarmDfa
{
public:

    uint8_t ALARM_TYPE(void)
    {
        return EMERGENCY;
    };

    uint8_t ACTIVE_LEVEL(void)
    {
        return 1;
    };

    CEmergencyAlarmHighLevelDfa();
    virtual ~CEmergencyAlarmHighLevelDfa();

protected:
private:
};
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
class CIndicationAlarmLowLevelDfa : public CAlarmDfa
{
public:

    uint8_t ALARM_TYPE(void)
    {
        return INDICATION;
    };

    uint8_t ACTIVE_LEVEL(void)
    {
        return 0;
    };

    CIndicationAlarmLowLevelDfa();
    virtual ~CIndicationAlarmLowLevelDfa();
    virtual void Fsm(void);

protected:
private:
};
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
class CIndicationAlarmHighLevelDfa : public CIndicationAlarmLowLevelDfa
{
public:

    uint8_t ALARM_TYPE(void)
    {
        return INDICATION;
    };

    uint8_t ACTIVE_LEVEL(void)
    {
        return 1;
    };

    CIndicationAlarmHighLevelDfa();
    virtual ~CIndicationAlarmHighLevelDfa();

protected:
private:
};

//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
class CErrorAlarmDfa : public CDfaLite
{
public:
    enum
    {
        START = 0,
        ACTIVE_STATE_WAITING,
        RECEIPT_WAITING,
        RECEIPTED_NOT_ACTIVE_STATE_WAITING,
    };

    virtual uint8_t ALARM_TYPE(void)
    {
        return ERROR;
    };

    virtual uint8_t ACTIVE_LEVEL(void)
    {
        return 0;
    };

    CErrorAlarmDfa();
    virtual ~CErrorAlarmDfa();
    virtual void Fsm(void);

    void SetDiscreteStateIndex(uint8_t uiDiscreteStateIndex)
    {
        m_uiDiscreteStateIndex = uiDiscreteStateIndex;
    };
    uint8_t GetDiscreteStateIndex(void)
    {
        return m_uiDiscreteStateIndex;
    };

    void SetAlarmWindowIndex(uint8_t uiAlarmWindowIndex)
    {
        m_uiAlarmWindowIndex = uiAlarmWindowIndex;
    };
    uint8_t GetAlarmWindowIndex(void)
    {
        return m_uiAlarmWindowIndex;
    };

protected:
private:
    // Индекс окна извещателя - светового табло.
    uint8_t m_uiAlarmWindowIndex;
    // Источник дискретного сигнала.
    uint8_t m_uiDiscreteStateIndex;
};
//-----------------------------------------------------------------------------------------------------








////-----------------------------------------------------------------------------------------------------
//class CInputModuleErrorAlarmDfa : public CErrorAlarmDfa
//{
//public:
//
//    uint8_t ALARM_TYPE(void)
//    {
//        return ERROR;
//    };
//
//    uint8_t ACTIVE_LEVEL(void)
//    {
//        return 1;
//    };
//
//    CInputModuleErrorAlarmDfa();
//    virtual ~CInputModuleErrorAlarmDfa();
//
//protected:
//private:
//};
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//class COutpuModuleErrorAlarmDfa : public CErrorAlarmDfa
//{
//public:
//
//    uint8_t ALARM_TYPE(void)
//    {
//        return EMERGENCY;
//    };
//
//    uint8_t ACTIVE_LEVEL(void)
//    {
//        return 1;
//    };
//
//    COutpuModuleErrorAlarmDfa();
//    virtual ~COutpuModuleErrorAlarmDfa();
//
//protected:
//private:
//};
////-----------------------------------------------------------------------------------------------------

#endif // CALARM_H
