//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "LinkControl.h"
#include "Pss21.h"

//-----------------------------------------------------------------------------------------------------

CLinkControl::CLinkControl()
{

}

CLinkControl::~CLinkControl()
{

}

//-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------

CModbusRtuLinkControl::CModbusRtuLinkControl()
{
    SetFsmEvent(NO_EVENT_FSM_EVENT);
    SetFsmState(LINK_CONTROL_IS_ON_CHECK);
}

CModbusRtuLinkControl::~CModbusRtuLinkControl()
{

}

//-----------------------------------------------------------------------------------------------------
void CModbusRtuLinkControl::Fsm(void)
{
    switch (GetFsmState())
    {
    case IDDLE:
        break;

    case LINK_CONTROL_IS_ON_CHECK:
        // Режим контроля связи вклюен?
        if (CPss21::ModbusRtuLinkControlIsOn())
        {
            // Режим контроля связи в рабочем процессе?
            if (CPss21::ModbusRtuLinkControlInProgress())
            {
                // Установим время ожидания следующего сеанса связи.
                GetTimerPointer() -> Set(CPss21::GetTimeoutModbusRtuLinkControl());
                SetFsmState(NEXT_LINK_SESSION_WAITING);
            }
            else
            {
                SetFsmState(LINK_CONTROL_IN_PROGRESS_ON_WAITING);
            }
        }
        else
        {
            SetFsmState(IDDLE);
        }
        break;

    case LINK_CONTROL_IN_PROGRESS_ON_WAITING:
        // Состоялся сеанс связи?
        if (GetFsmEvent() == LINK_SESSION_HAPPENED_FSM_EVENT)
        {
            SetFsmEvent(NO_EVENT_FSM_EVENT);
            // Запустим рабоий процесс режима контроля связи.
            CPss21::SetModeModbusRtuLinkControlInProgress(true);
            // Установим время ожидания следующего сеанса связи.
            GetTimerPointer() -> Set(CPss21::GetTimeoutModbusRtuLinkControl());
            SetFsmState(NEXT_LINK_SESSION_WAITING);
        }
        break;

    case NEXT_LINK_SESSION_WAITING:
        // Состоялся сеанс связи?
        if (GetFsmEvent() == LINK_SESSION_HAPPENED_FSM_EVENT)
        {
            SetFsmEvent(NO_EVENT_FSM_EVENT);
            // Установим время ожидания следующего сеанса связи.
            GetTimerPointer() -> Set(CPss21::GetTimeoutModbusRtuLinkControl());
        }
        else
        {
            // Время ожидания следующего сеанса связи закончилось?
            if (GetTimerPointer() -> IsOverflow())
            {
                CPss21::SetErrorCode(MBS_ERROR);
                SetFsmState(RECEIPT_OR_NEXT_LINK_SESSION_WAITING);
            }
        }

        break;

    case RECEIPT_OR_NEXT_LINK_SESSION_WAITING:
        switch (GetFsmEvent())
        {
        case LINK_SESSION_HAPPENED_FSM_EVENT:
            SetFsmEvent(NO_EVENT_FSM_EVENT);
            CPss21::SetFsmState(CPss21::LINK_CONTROL_ERROR_OFF);
            // Установим время ожидания следующего сеанса связи.
            GetTimerPointer() -> Set(CPss21::GetTimeoutModbusRtuLinkControl());
            SetFsmState(NEXT_LINK_SESSION_WAITING);
            break;

        case RECEIPT_HAPPENED_FSM_EVENT:
            SetFsmEvent(NO_EVENT_FSM_EVENT);
            // Остановим рабоий процесс режима контроля связи.
            CPss21::SetModeModbusRtuLinkControlInProgress(false);
            CPss21::SetFsmState(CPss21::LINK_CONTROL_ERROR_OFF);
            SetFsmState(LINK_CONTROL_IN_PROGRESS_ON_WAITING);
            break;

        default:
            break;
        }
        break;

    default:
        break;
    }
}


