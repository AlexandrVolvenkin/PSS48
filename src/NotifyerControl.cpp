//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "NotifyerControl.h"
#include "Platform.h"
#include "Pss21.h"
#include "Buzzer.h"

//-----------------------------------------------------------------------------------------------------
CNotifyerControl::CNotifyerControl()
{
    SetFsmState(STOP);
    SetSavedFsmState(STOP);
}

CNotifyerControl::~CNotifyerControl()
{

}

////-----------------------------------------------------------------------------------------------------
//void CNotifyerControl::Init(CAlarmWindow* pxAlarmWindowControl)
//{
////    m_pxAlarmWindowControl = pxAlarmWindowControl;
//    SetFsmState(CNotifyerControl::STOP);
//}

////-----------------------------------------------------------------------------------------------------
//void CNotifyerControl::AlarmSet(uint8_t uiAlarmType)
//{
////    SetSavedFsmState(GetFsmState());
////    m_uiAlarmType = uiAlarmType;
////    switch (m_uiAlarmType)
//    switch (uiAlarmType)
//    {
//    case NORMAL:
//        SetFsmState(STOP);
//        break;
//
//    case NORMAL:
//        SetFsmState(NORMAL_SIGNAL_START);
//        break;
//
//    case INDICATION:
//        SetFsmState(INDICATION_SIGNAL_START);
//        break;
//
//    case PREVENTIVE:
//        SetFsmState(WARNING_SIGNAL_START);
//        break;
//
//    case EMERGENCY:
//        SetFsmState(ALARM_SIGNAL_START);
//        break;
//
//    case IND_PREVENTIVE:
//        break;
//
//    case IND_EMERGENCY:
//        break;
//
//    default:
//        break;
//    }
//}

//class Base
//{
//    const int k;
//public:
//    Base(const int i) :
//        k(i)
//    {
//    }
//    virtual void print() const
//    {
//        std::cout << k << std::endl;
//    }
//};
//class D1 : public Base
//{
//public:
//    D1(const int j) :
//        Base(j)
//    {
//    }
//};

//-----------------------------------------------------------------------------------------------------
void CNotifyerControl::Fsm(void)
{
    switch (GetFsmState())
    {
    case IDDLE:
        break;

    case NORMAL_SIGNAL_START:
        m_xTimer.Set(NORMAL_SIGNAL_ON_TIME());
        NotifyerNormalOn();
        SetFsmState(NORMAL_SIGNAL_ON);
        break;

    case NORMAL_SIGNAL_ON:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(NORMAL_SIGNAL_OFF_TIME());
            NotifyerOff();
            SetFsmState(NORMAL_SIGNAL_OFF);
        }
        break;

    case NORMAL_SIGNAL_OFF:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(NORMAL_SIGNAL_ON_TIME());
            NotifyerNormalOn();
            SetFsmState(NORMAL_SIGNAL_ON);
        }
        break;

    case INDICATION_SIGNAL_START:
//        m_xTimer.Set(NORMAL_SIGNAL_ON_TIME());
        NotifyerIndicationOn();
//        SetFsmState(INDICATION_SIGNAL_ON);
        break;

//    case INDICATION_SIGNAL_ON:
////        if (m_xTimer.IsOverflow())
////        {
////            m_xTimer.Set(NORMAL_SIGNAL_OFF_TIME());
//////            NotifyerOff();
////            SetFsmState(INDICATION_SIGNAL_OFF);
////        }
//        break;
//
//    case INDICATION_SIGNAL_OFF:
////        if (m_xTimer.IsOverflow())
////        {
////            m_xTimer.Set(NORMAL_SIGNAL_ON_TIME());
////            NotifyerIndicationOn();
////            SetFsmState(INDICATION_SIGNAL_ON);
////        }
//        break;

    case WARNING_SIGNAL_START:
        m_xTimer.Set(WARNING_SIGNAL_ON_TIME());
        NotifyerPreventiveOn();
        SetFsmState(WARNING_SIGNAL_ON);
        break;

    case WARNING_SIGNAL_ON:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(WARNING_SIGNAL_OFF_TIME());
            NotifyerOff();
            SetFsmState(WARNING_SIGNAL_OFF);
        }
        break;

    case WARNING_SIGNAL_OFF:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(WARNING_SIGNAL_ON_TIME());
            NotifyerPreventiveOn();
            SetFsmState(WARNING_SIGNAL_ON);
        }
        break;

    case ALARM_SIGNAL_START:
        m_xTimer.Set(ALARM_SIGNAL_ON_TIME());
        NotifyerEmergencyOn();
        SetFsmState(ALARM_SIGNAL_ON);
        break;

    case ALARM_SIGNAL_ON:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(ALARM_SIGNAL_OFF_TIME());
            NotifyerOff();
            SetFsmState(ALARM_SIGNAL_OFF);
        }
        break;

    case ALARM_SIGNAL_OFF:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(ALARM_SIGNAL_ON_TIME());
            NotifyerEmergencyOn();
            SetFsmState(ALARM_SIGNAL_ON);
        }
        break;

    case ERROR_SIGNAL_START:
        m_xTimer.Set(ERROR_SIGNAL_ON_TIME());
        NotifyerEmergencyOn();
        SetFsmState(ERROR_SIGNAL_ON);
        break;

    case ERROR_SIGNAL_ON:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(ERROR_SIGNAL_OFF_TIME());
            NotifyerOff();
            SetFsmState(ERROR_SIGNAL_OFF);
        }
        break;

    case ERROR_SIGNAL_OFF:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(ERROR_SIGNAL_ON_TIME());
            NotifyerEmergencyOn();
            SetFsmState(ERROR_SIGNAL_ON_2);
        }
        break;

    case ERROR_SIGNAL_ON_2:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(ERROR_SIGNAL_PAUSE_TIME());
            NotifyerOff();
            SetFsmState(ERROR_SIGNAL_OFF_2);
        }
        break;

    case ERROR_SIGNAL_OFF_2:
        if (m_xTimer.IsOverflow())
        {
            m_xTimer.Set(ERROR_SIGNAL_ON_TIME());
            NotifyerEmergencyOn();
            SetFsmState(ERROR_SIGNAL_ON);
        }
        break;

    case BEEP_SIGNAL_START:
        m_xTimer.Set(BEEP_SIGNAL_ON_TIME());
        NotifyerEmergencyOn();
        SetFsmState(BEEP_SIGNAL_ON);
        break;

    case BEEP_SIGNAL_ON:
        if (m_xTimer.IsOverflow())
        {
            NotifyerOff();
            // Восстановим предыдущее состояние автомата.
            SetFsmState(GetSavedFsmState());
//            SetFsmState(STOP);
        }
        break;

    case STOP:
        NotifyerOff();
        SetFsmState(IDDLE);
        break;

    default:
        break;
    };
}
//-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
CPreventiveAlarmWindowNotifyerControl::CPreventiveAlarmWindowNotifyerControl()
{
    SetFsmState(STOP);
    SetSavedFsmState(STOP);
}

CPreventiveAlarmWindowNotifyerControl::~CPreventiveAlarmWindowNotifyerControl()
{
    SetFsmState(STOP);
}

//-----------------------------------------------------------------------------------------------------
void CPreventiveAlarmWindowNotifyerControl::AlarmSet(uint8_t uiAlarmType)
{
    // Сохраним текущее состояние автомата.
    SetSavedFsmState(GetFsmState());
    switch (uiAlarmType)
    {
    case NORMAL:
        SetFsmState(STOP);
        break;

    case INDICATION:
        SetFsmState(INDICATION_SIGNAL_START);
        break;

    case PREVENTIVE:
        SetFsmState(WARNING_SIGNAL_START);
        break;

    case EMERGENCY:
        SetFsmState(WARNING_SIGNAL_START);
        break;

    case IND_PREVENTIVE:
        break;

    case IND_EMERGENCY:
        break;

    case ERROR:
        break;

    case BEEP_SIGNAL:
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------------------
void CPreventiveAlarmWindowNotifyerControl::NotifyerNormalOn(void)
{

}

//-----------------------------------------------------------------------------------------------------
void CPreventiveAlarmWindowNotifyerControl::NotifyerIndicationOn(void)
{
    CPss21::ActiveAlarmWindowOn(INDICATION);
}

//-----------------------------------------------------------------------------------------------------
void CPreventiveAlarmWindowNotifyerControl::NotifyerPreventiveOn(void)
{
    CPss21::ActiveAlarmWindowOn(PREVENTIVE);
}

//-----------------------------------------------------------------------------------------------------
void CPreventiveAlarmWindowNotifyerControl::NotifyerEmergencyOn(void)
{

}

//-----------------------------------------------------------------------------------------------------
void CPreventiveAlarmWindowNotifyerControl::NotifyerOff(void)
{
    CPss21::ActiveAlarmWindowOff(PREVENTIVE);
    CPss21::BoardWindowsUpdate();
}
//-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
CEmergencyAlarmWindowNotifyerControl::CEmergencyAlarmWindowNotifyerControl()
{
    SetFsmState(STOP);
    SetSavedFsmState(STOP);
}

CEmergencyAlarmWindowNotifyerControl::~CEmergencyAlarmWindowNotifyerControl()
{
    SetFsmState(STOP);
}

//-----------------------------------------------------------------------------------------------------
void CEmergencyAlarmWindowNotifyerControl::AlarmSet(uint8_t uiAlarmType)
{
    // Сохраним текущее состояние автомата.
    SetSavedFsmState(GetFsmState());
    switch (uiAlarmType)
    {
    case NORMAL:
        SetFsmState(STOP);
        break;

    case INDICATION:
        SetFsmState(INDICATION_SIGNAL_START);
        break;

    case PREVENTIVE:
        SetFsmState(STOP);
        break;

    case EMERGENCY:
        SetFsmState(ALARM_SIGNAL_START);
        break;

    case IND_PREVENTIVE:
        break;

    case IND_EMERGENCY:
        break;

    case ERROR:
        break;

    case BEEP_SIGNAL:
        break;

    default:
        break;
    }
}


//-----------------------------------------------------------------------------------------------------
void CEmergencyAlarmWindowNotifyerControl::NotifyerNormalOn(void)
{

}

//-----------------------------------------------------------------------------------------------------
void CEmergencyAlarmWindowNotifyerControl::NotifyerIndicationOn(void)
{
    CPss21::ActiveAlarmWindowOn(INDICATION);
}

//-----------------------------------------------------------------------------------------------------
void CEmergencyAlarmWindowNotifyerControl::NotifyerPreventiveOn(void)
{

}

//-----------------------------------------------------------------------------------------------------
void CEmergencyAlarmWindowNotifyerControl::NotifyerEmergencyOn(void)
{
    CPss21::ActiveAlarmWindowOn(EMERGENCY);
}

//-----------------------------------------------------------------------------------------------------
void CEmergencyAlarmWindowNotifyerControl::NotifyerOff(void)
{
    CPss21::ActiveAlarmWindowOff(EMERGENCY);
    CPss21::BoardWindowsUpdate();
}
//-----------------------------------------------------------------------------------------------------









//-----------------------------------------------------------------------------------------------------

CStatusLedNotifyerControl::CStatusLedNotifyerControl()
{
    SetFsmState(NORMAL_SIGNAL_START);
    SetSavedFsmState(NORMAL_SIGNAL_START);
}

CStatusLedNotifyerControl::~CStatusLedNotifyerControl()
{
    SetFsmState(STOP);
}

//-----------------------------------------------------------------------------------------------------
void CStatusLedNotifyerControl::AlarmSet(uint8_t uiAlarmType)
{
    // Сохраним текущее состояние автомата.
    SetSavedFsmState(GetFsmState());
    switch (uiAlarmType)
    {
    case NORMAL:
        SetFsmState(NORMAL_SIGNAL_START);
        break;

    case INDICATION:
        SetFsmState(NORMAL_SIGNAL_START);
        break;

    case PREVENTIVE:
        SetFsmState(WARNING_SIGNAL_START);
        break;

    case EMERGENCY:
        SetFsmState(ALARM_SIGNAL_START);
        break;

    case IND_PREVENTIVE:
        break;

    case IND_EMERGENCY:
        break;

    case ERROR:
        SetFsmState(ERROR_SIGNAL_START);
        break;

    case BEEP_SIGNAL:
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------------------
void CStatusLedNotifyerControl::NotifyerNormalOn(void)
{
    CPlatform::StatusLedOn();
}

//-----------------------------------------------------------------------------------------------------
void CStatusLedNotifyerControl::NotifyerIndicationOn(void)
{

}

//-----------------------------------------------------------------------------------------------------
void CStatusLedNotifyerControl::NotifyerPreventiveOn(void)
{
    CPlatform::StatusLedOn();
}

//-----------------------------------------------------------------------------------------------------
void CStatusLedNotifyerControl::NotifyerEmergencyOn(void)
{
    CPlatform::StatusLedOn();
}

//-----------------------------------------------------------------------------------------------------
void CStatusLedNotifyerControl::NotifyerOff(void)
{
    CPlatform::StatusLedOff();
    CPss21::BoardWindowsUpdate();
}
//-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------

CBuzzerNotifyerControl::CBuzzerNotifyerControl()
{
    SetFsmState(STOP);
    SetSavedFsmState(STOP);
}

CBuzzerNotifyerControl::~CBuzzerNotifyerControl()
{
    SetFsmState(STOP);
}

//-----------------------------------------------------------------------------------------------------
void CBuzzerNotifyerControl::AlarmSet(uint8_t uiAlarmType)
{
    // Сохраним текущее состояние автомата.
    SetSavedFsmState(GetFsmState());
    switch (uiAlarmType)
    {
    case NORMAL:
        SetFsmState(STOP);
        break;

    case INDICATION:
        SetFsmState(STOP);
        break;

    case PREVENTIVE:
        SetFsmState(WARNING_SIGNAL_START);
        break;

    case EMERGENCY:
        SetFsmState(ALARM_SIGNAL_START);
        break;

    case IND_PREVENTIVE:
        break;

    case IND_EMERGENCY:
        break;

    case ERROR:
        SetFsmState(ERROR_SIGNAL_START);
        break;

    case BEEP_SIGNAL:
        SetFsmState(BEEP_SIGNAL_START);
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------------------
void CBuzzerNotifyerControl::NotifyerNormalOn(void)
{
    CBuzzer::Off();
}

//-----------------------------------------------------------------------------------------------------
void CBuzzerNotifyerControl::NotifyerIndicationOn(void)
{
    CBuzzer::Off();
}

//-----------------------------------------------------------------------------------------------------
void CBuzzerNotifyerControl::NotifyerPreventiveOn(void)
{
    CBuzzer::LowOn();
}

//-----------------------------------------------------------------------------------------------------
void CBuzzerNotifyerControl::NotifyerEmergencyOn(void)
{
    CBuzzer::HighOn();
}

//-----------------------------------------------------------------------------------------------------
void CBuzzerNotifyerControl::NotifyerOff(void)
{
    CBuzzer::Off();
    CPss21::BoardWindowsUpdate();
}



