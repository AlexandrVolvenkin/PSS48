//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CEVENT_H
#define CEVENT_H

//-----------------------------------------------------------------------------------------------------
#include <stdint.h>

#include "Timer.h"
#include "Dfa.h"

//-----------------------------------------------------------------------------------------------------
class CEvent : public CDfa
{
public:
    CEvent();
    virtual ~CEvent();

protected:
private:
};
//-----------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------------
class CEventUniteLogicAnd : public CEvent
{
public:
    enum
    {
        START = 0,
        EVENT_WAITING,
        EVENT_UNITE_WAITING,
        STOP,
    };
    // Время ожидания объединения событий.
    uint16_t UNITED_WAITING_TIME(void)
    {
        return 500;
    };

    CEventUniteLogicAnd();
    CEventUniteLogicAnd(uint16_t uiTime);
    virtual ~CEventUniteLogicAnd();

    uint8_t IsHappened(uint8_t uiEventOne, uint8_t uiEventTwo);

protected:
private:
    CTimer m_xTimer;
    uint16_t m_uiTime;
    uint8_t m_uiEventsState;
};

//-----------------------------------------------------------------------------------------------------
#endif // CEVENT_H
