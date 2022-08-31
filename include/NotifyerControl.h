//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CNOTIFYERCONTROL_H
#define CNOTIFYERCONTROL_H


#include <stdint.h>

#include "Configuration.h"
#include "Dfa.h"
#include "Timer.h"
#include "AlarmWindow.h"

//Ощибка:
//Два коротких по 150мс
//Пауза 450мс

//Предупредительная:
//Один короткий 800мс
//Пауза 300мс

//Аварийная:
//Один короткий 300мс
//Пауза 300мс

//-----------------------------------------------------------------------------------------------------
class CNotifyerControl : public CDfa
{
public:
    enum
    {
        COMMAND_SOUND_SIGNAL_TYPE_NOT = 0,
        COMMAND_SOUND_SIGNAL_TYPE_OFF = 1,
        COMMAND_SOUND_SIGNAL_TYPE_WARNING = 2,
        COMMAND_SOUND_SIGNAL_TYPE_ALARM = 3,
        COMMAND_SOUND_SIGNAL_TYPE_ERROR = 4,
        COMMAND_SOUND_SIGNAL_TYPE_NO_SOUND = 0x80,

        SOUND_SIGNAL_TYPE_NOT = 0,
        SOUND_SIGNAL_TYPE_WARNING,
        SOUND_SIGNAL_TYPE_ALARM,
        SOUND_SIGNAL_TYPE_ERROR,
        SOUND_SIGNAL_TYPE_NO_SOUND = 0x80,
    };

    enum
    {
        IDDLE = 0,
        INDICATION_SIGNAL_START,
        INDICATION_SIGNAL_ON,
        INDICATION_SIGNAL_OFF,
        INDICATION_SIGNAL_START_NO_SOUND,
        INDICATION_SIGNAL_ON_NO_SOUND,
        INDICATION_SIGNAL_OFF_NO_SOUND,
        WARNING_SIGNAL_START,
        WARNING_SIGNAL_ON,
        WARNING_SIGNAL_OFF,
        WARNING_SIGNAL_START_NO_SOUND,
        WARNING_SIGNAL_ON_NO_SOUND,
        WARNING_SIGNAL_OFF_NO_SOUND,
        ALARM_SIGNAL_START,
        ALARM_SIGNAL_ON,
        ALARM_SIGNAL_OFF,
        ALARM_SIGNAL_START_NO_SOUND,
        ALARM_SIGNAL_ON_NO_SOUND,
        ALARM_SIGNAL_OFF_NO_SOUND,
        ERROR_SIGNAL_START,
        ERROR_SIGNAL_ON,
        ERROR_SIGNAL_OFF,
        ERROR_SIGNAL_ON_2,
        ERROR_SIGNAL_OFF_2,
        NORMAL_SIGNAL_START,
        NORMAL_SIGNAL_ON,
        NORMAL_SIGNAL_OFF,
        NORMAL_SIGNAL_START_NO_SOUND,
        NORMAL_SIGNAL_ON_NO_SOUND,
        NORMAL_SIGNAL_OFF_NO_SOUND,
        BEEP_SIGNAL_START,
        BEEP_SIGNAL_ON,
        BEEP_SIGNAL_OFF,
        FREQUENCY_LOW_TEST,
        FREQUENCY_HIGH_TEST,
        FREQUENCY_TEST,
        FREQUENCY_SIGNAL_OFF,
        STOP
    };

    CNotifyerControl();
    virtual ~CNotifyerControl();
    virtual void NotifyerNormalOn(void) = 0;
    virtual void NotifyerIndicationOn(void) = 0;
    virtual void NotifyerPreventiveOn(void) = 0;
    virtual void NotifyerEmergencyOn(void) = 0;
    virtual void NotifyerOff(void) = 0;
    virtual void AlarmSet(uint8_t uiAlarmType) = 0;
    void Fsm(void);

    virtual uint16_t NORMAL_SIGNAL_ON_TIME(void)
    {
        return 2000;
    };
    virtual uint16_t NORMAL_SIGNAL_OFF_TIME(void)
    {
        return 2000;
    };

    virtual uint16_t WARNING_SIGNAL_ON_TIME(void)
    {
        return 800;
    };
    virtual uint16_t WARNING_SIGNAL_OFF_TIME(void)
    {
        return 300;
    };

    virtual uint16_t ALARM_SIGNAL_ON_TIME(void)
    {
        return 300;
    };
    virtual uint16_t ALARM_SIGNAL_OFF_TIME(void)
    {
        return 300;
    };

    virtual uint16_t ERROR_SIGNAL_ON_TIME(void)
    {
        return 150;
    };
    virtual uint16_t ERROR_SIGNAL_OFF_TIME(void)
    {
        return 150;
    };
    virtual uint16_t ERROR_SIGNAL_PAUSE_TIME(void)
    {
        return 450;
    };

    virtual uint16_t BEEP_SIGNAL_ON_TIME(void)
    {
        return 50;
    };

protected:
private:
    // Тип сигнализации.
    uint8_t m_uiAlarmType;
    CTimer m_xTimer;
};
//-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
class CPreventiveAlarmWindowNotifyerControl : public CNotifyerControl
{
public:
    CPreventiveAlarmWindowNotifyerControl();
    virtual ~CPreventiveAlarmWindowNotifyerControl();
    void NotifyerNormalOn(void);
    void NotifyerIndicationOn(void);
    void NotifyerPreventiveOn(void);
    void NotifyerEmergencyOn(void);
    void NotifyerOff(void);
    void AlarmSet(uint8_t uiAlarmType);

    uint16_t NORMAL_SIGNAL_ON_TIME(void)
    {
        return 2000;
    };
    uint16_t NORMAL_SIGNAL_OFF_TIME(void)
    {
        return 2000;
    };
    uint16_t WARNING_SIGNAL_ON_TIME(void)
    {
        return 800;
    };
    uint16_t WARNING_SIGNAL_OFF_TIME(void)
    {
        return 300;
    };
    uint16_t ALARM_SIGNAL_ON_TIME(void)
    {
        return 300;
    };
    uint16_t ALARM_SIGNAL_OFF_TIME(void)
    {
        return 300;
    };

protected:
private:
};
//-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
class CEmergencyAlarmWindowNotifyerControl : public CNotifyerControl
{
public:
    CEmergencyAlarmWindowNotifyerControl();
    virtual ~CEmergencyAlarmWindowNotifyerControl();
    void NotifyerNormalOn(void);
    void NotifyerIndicationOn(void);
    void NotifyerPreventiveOn(void);
    void NotifyerEmergencyOn(void);
    void NotifyerOff(void);
    void AlarmSet(uint8_t uiAlarmType);

    uint16_t NORMAL_SIGNAL_ON_TIME(void)
    {
        return 2000;
    };
    uint16_t NORMAL_SIGNAL_OFF_TIME(void)
    {
        return 2000;
    };
    uint16_t WARNING_SIGNAL_ON_TIME(void)
    {
        return 800;
    };
    uint16_t WARNING_SIGNAL_OFF_TIME(void)
    {
        return 300;
    };
    uint16_t ALARM_SIGNAL_ON_TIME(void)
    {
        return 300;
    };
    uint16_t ALARM_SIGNAL_OFF_TIME(void)
    {
        return 300;
    };

protected:
private:
};
//-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
class CStatusLedNotifyerControl : public CNotifyerControl
{
public:
    CStatusLedNotifyerControl();
    virtual ~CStatusLedNotifyerControl();
    void NotifyerNormalOn(void);
    void NotifyerIndicationOn(void);
    void NotifyerPreventiveOn(void);
    void NotifyerEmergencyOn(void);
    void NotifyerOff(void);
    void AlarmSet(uint8_t uiAlarmType);

protected:
private:
};
//-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
class CBuzzerNotifyerControl : public CNotifyerControl
{
public:
    CBuzzerNotifyerControl();
    virtual ~CBuzzerNotifyerControl();
    void NotifyerNormalOn(void);
    void NotifyerIndicationOn(void);
    void NotifyerPreventiveOn(void);
    void NotifyerEmergencyOn(void);
    void NotifyerOff(void);
    void AlarmSet(uint8_t uiAlarmType);

protected:
private:
};

//-----------------------------------------------------------------------------------------------------
#endif // CNOTIFYERCONTROL_H
