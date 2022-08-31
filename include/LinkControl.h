//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CLINKCONTROL_H
#define CLINKCONTROL_H

#include <stdint.h>

#include "Configuration.h"
#include "Dfa.h"
#include "Timer.h"

//-----------------------------------------------------------------------------------------------------
class CLinkControl : public CDfa
{
public:
    CLinkControl();
    virtual ~CLinkControl();

    CTimer* GetTimerPointer(void)
    {
        return &m_xTimer;
    };

protected:
private:
    CTimer m_xTimer;
};

//-----------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------------
class CModbusRtuLinkControl : public CLinkControl
{
public:
    enum
    {
        NO_EVENT_FSM_EVENT = 0,
        LINK_SESSION_HAPPENED_FSM_EVENT,
        RECEIPT_HAPPENED_FSM_EVENT,
    };

    enum
    {
        IDDLE = 0,
        LINK_CONTROL_IS_ON_CHECK,
        LINK_CONTROL_IN_PROGRESS_ON_WAITING,
        NEXT_LINK_SESSION_WAITING,
        RECEIPT_OR_NEXT_LINK_SESSION_WAITING,
    };

    CModbusRtuLinkControl();
    virtual ~CModbusRtuLinkControl();
    void Fsm(void);

protected:
private:
};

//-----------------------------------------------------------------------------------------------------
#endif // CLINKCONTROL_H
