//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "Dfa.h"
#include "Platform.h"
#include "Pss21.h"

//-----------------------------------------------------------------------------------------------------
CAlarmDfa::CAlarmDfa()
{
    //ctor
}

//-----------------------------------------------------------------------------------------------------
CAlarmDfa::~CAlarmDfa()
{
    //dtor
}

//-----------------------------------------------------------------------------------------------------
// Автомат обработки сигнализации дискретного сигнала.
void CAlarmDfa::Fsm(void)
{
    switch (GetFsmState())
    {
    case START:
        break;

    case ACTIVE_STATE_WAITING:
        // Дискретный сигнал активен?
        if (CPss21::GetDiscreteInputState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL())
        {
            // Установим связанные дискретный выходы - новое нарушение.
            CPss21::DiscreteOutputsSet(GetLinkedDiscreteOutputsPointer(), NEW_VIOLATION);
            // Тип запрограммированной сигнализации дискретного сигнала имеет более высокий приоритет,
            // чем тип общей сигнализации?
            if ((CPss21::GetCommonAlarmType() != EMERGENCY) &&
                    (CPss21::GetCommonAlarmType() < ALARM_TYPE()))
            {
                // Установим тип общей сигнализацию.
                CPss21::SetCommonAlarmType(ALARM_TYPE());
                // Изменим тип общей сигнализацию.
                CPss21::AlarmTypeChange();
            }
            // Установим тип сигнализации связанному окну в массиве управления окнами извещателя.
            CPss21::SetAlarmWindowType(GetAlarmWindowIndex(), ALARM_TYPE());
            SetFsmState(RECEIPT_OR_RESET_WAITING);
        }
        break;

    case RECEIPT_OR_RESET_WAITING:
        // Дискретный сигнал активен?
        if (CPss21::GetDiscreteInputState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL())
        {
            // Установим связанные дискретный выходы - не новое нарушение.
            CPss21::DiscreteOutputsSet(GetLinkedDiscreteOutputsPointer(), NOT_NEW_VIOLATION);
        }

        // Событие сброшено?
        if (CPss21::GetDiscreteSignalsReset())
        {
            // Переведём автоматы сигнализаций в состояние - квитировано.
            CPss21::AlarmTypeReceipt();
            // Установим тип сигнализации связанному окну в массиве управления окнами извещателя.
            CPss21::SetAlarmWindowType(GetAlarmWindowIndex(), INDICATION);
            SetFsmState(RESETED_NOT_ACTIVE_STATE_WAITING);
        }
        // Событие квитировано?
        else if (CPss21::GetDiscreteSignalsReceipt())
        {
            // Переведём автоматы сигнализаций в состояние - квитировано.
            CPss21::AlarmTypeReceipt();
            // Установим тип сигнализации связанному окну в массиве управления окнами извещателя.
            CPss21::SetAlarmWindowType(GetAlarmWindowIndex(), INDICATION);
            SetFsmState(RECEIPTED_RESET_OR_NOT_ACTIVE_STATE_WAITING);
        }
        break;

    case RECEIPTED_RESET_OR_NOT_ACTIVE_STATE_WAITING:
        // Событие сброшено?
        if (CPss21::GetDiscreteSignalsReset())
        {
            SetFsmState(RESETED_NOT_ACTIVE_STATE_WAITING);
        }
        // Дискретный сигнал не активен?
        else if (!(CPss21::GetDiscreteInputState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL()))
        {
            SetFsmState(RECEIPTED_RESET_WAITING);
        }
        else
        {
            // Установим связанные дискретный выходы - не новое нарушение.
            CPss21::DiscreteOutputsSet(GetLinkedDiscreteOutputsPointer(), NOT_NEW_VIOLATION);
        }
        break;

    case RESETED_NOT_ACTIVE_STATE_WAITING:
        // Дискретный сигнал не активен?
        if (!(CPss21::GetDiscreteInputState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL()))
        {
            // Переведём автоматы сигнализаций в состояние - сброшено.
            CPss21::AlarmTypeReset();
            // Установим тип сигнализации связанному окну в массиве управления окнами извещателя.
            CPss21::SetAlarmWindowType(GetAlarmWindowIndex(), NORMAL);
            SetFsmState(ACTIVE_STATE_WAITING);
        }
        else
        {
            // Установим связанные дискретный выходы - не новое нарушение.
            CPss21::DiscreteOutputsSet(GetLinkedDiscreteOutputsPointer(), NOT_NEW_VIOLATION);
        }
        break;

    case RECEIPTED_RESET_WAITING:
        // Дискретный сигнал активен?
        if (CPss21::GetDiscreteInputState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL())
        {
            // Установим связанные дискретный выходы - не новое нарушение.
            CPss21::DiscreteOutputsSet(GetLinkedDiscreteOutputsPointer(), NOT_NEW_VIOLATION);
        }

        // Событие сброшено?
        if (CPss21::GetDiscreteSignalsReset())
        {
            // Переведём автоматы сигнализаций в состояние - сброшено.
            CPss21::AlarmTypeReset();
            // Установим тип сигнализации связанному окну в массиве управления окнами извещателя.
            CPss21::SetAlarmWindowType(GetAlarmWindowIndex(), NORMAL);
            SetFsmState(ACTIVE_STATE_WAITING);
        }
        break;

    default:
        break;
    }
}
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
CNormalAlarmDfa::CNormalAlarmDfa()
{
    SetFsmState(START);
}

//-----------------------------------------------------------------------------------------------------
CNormalAlarmDfa::~CNormalAlarmDfa()
{
    //dtor
}

//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
CPreventiveAlarmLowLevelDfa::CPreventiveAlarmLowLevelDfa()
{
    SetFsmState(ACTIVE_STATE_WAITING);
}

//-----------------------------------------------------------------------------------------------------
CPreventiveAlarmLowLevelDfa::~CPreventiveAlarmLowLevelDfa()
{
    //dtor
}

//-----------------------------------------------------------------------------------------------------
CPreventiveAlarmHighLevelDfa::CPreventiveAlarmHighLevelDfa()
{
    SetFsmState(ACTIVE_STATE_WAITING);
}

//-----------------------------------------------------------------------------------------------------
CPreventiveAlarmHighLevelDfa::~CPreventiveAlarmHighLevelDfa()
{
    //dtor
}
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
CEmergencyAlarmLowLevelDfa::CEmergencyAlarmLowLevelDfa()
{
    SetFsmState(ACTIVE_STATE_WAITING);
}

//-----------------------------------------------------------------------------------------------------
CEmergencyAlarmLowLevelDfa::~CEmergencyAlarmLowLevelDfa()
{
    //dtor
}

//-----------------------------------------------------------------------------------------------------
CEmergencyAlarmHighLevelDfa::CEmergencyAlarmHighLevelDfa()
{
    SetFsmState(ACTIVE_STATE_WAITING);
}

//-----------------------------------------------------------------------------------------------------
CEmergencyAlarmHighLevelDfa::~CEmergencyAlarmHighLevelDfa()
{
    //dtor
}
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
CIndicationAlarmLowLevelDfa::CIndicationAlarmLowLevelDfa()
{
    SetFsmState(ACTIVE_STATE_WAITING);
}

//-----------------------------------------------------------------------------------------------------
CIndicationAlarmLowLevelDfa::~CIndicationAlarmLowLevelDfa()
{
    //dtor
}

//-----------------------------------------------------------------------------------------------------
// Автомат обработки сигнализации дискретного сигнала.
void CIndicationAlarmLowLevelDfa::Fsm(void)
{
    switch (GetFsmState())
    {
    case START:
        break;

    case ACTIVE_STATE_WAITING:
        // Дискретный сигнал активен?
        if (CPss21::GetDiscreteInputState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL())
        {
            // Установим связанные дискретный выходы - новое нарушение.
            CPss21::DiscreteOutputsSet(GetLinkedDiscreteOutputsPointer(), NEW_VIOLATION);
//            // Тип запрограммированной сигнализации дискретного сигнала имеет более высокий приоритет,
//            // чем тип общей сигнализации?
//            if ((CPss21::GetCommonAlarmType() != EMERGENCY) &&
//                    (CPss21::GetCommonAlarmType() < ALARM_TYPE()))
//            {
//                // Установим тип общей сигнализацию.
//                CPss21::SetCommonAlarmType(ALARM_TYPE());
//                // Изменим тип общей сигнализацию.
//                CPss21::AlarmTypeChange();
//            }

            // Установим тип сигнализации связанному окну в массиве управления окнами извещателя.
            CPss21::SetAlarmWindowType(GetAlarmWindowIndex(), ALARM_TYPE());
            // Актмвизируем окно сигнализации, для отображения извещателем.
            CPss21::GetAlarmWindowControlPointer(GetAlarmWindowIndex()) -> SetActivityState(1);
            CPss21::BoardWindowsUpdate();
            SetFsmState(NOT_ACTIVE_STATE_WAITING);
        }
        break;

    case NOT_ACTIVE_STATE_WAITING:
        // Дискретный сигнал не активен?
        if (!(CPss21::GetDiscreteInputState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL()))
        {
//            // Переведём автоматы сигнализаций в состояние - сброшено.
//            CPss21::AlarmTypeReset();
            // Установим тип сигнализации связанному окну в массиве управления окнами извещателя.
            CPss21::SetAlarmWindowType(GetAlarmWindowIndex(), NORMAL);
            // Деактмвируем окно сигнализации, для прекращения отображения извещателем.
            CPss21::GetAlarmWindowControlPointer(GetAlarmWindowIndex()) -> SetActivityState(0);
            CPss21::BoardWindowsUpdate();
            SetFsmState(ACTIVE_STATE_WAITING);
        }
        else
        {
            // Установим связанные дискретный выходы - не новое нарушение.
            CPss21::DiscreteOutputsSet(GetLinkedDiscreteOutputsPointer(), NOT_NEW_VIOLATION);
        }
        break;

    default:
        break;
    }
}
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
CIndicationAlarmHighLevelDfa::CIndicationAlarmHighLevelDfa()
{
    SetFsmState(ACTIVE_STATE_WAITING);
}

//-----------------------------------------------------------------------------------------------------
CIndicationAlarmHighLevelDfa::~CIndicationAlarmHighLevelDfa()
{
    //dtor
}
//-----------------------------------------------------------------------------------------------------








//-----------------------------------------------------------------------------------------------------
CErrorAlarmDfa::CErrorAlarmDfa()
{
    SetFsmState(ACTIVE_STATE_WAITING);
}

//-----------------------------------------------------------------------------------------------------
CErrorAlarmDfa::~CErrorAlarmDfa()
{
    //dtor
}

//-----------------------------------------------------------------------------------------------------
// Автомат обработки системных ошибок.
void CErrorAlarmDfa::Fsm(void)
{
    switch (GetFsmState())
    {
    case START:
        break;

    case ACTIVE_STATE_WAITING:
        // Дискретный сигнал активен?
        if (CPss21::GetErrorAlarmState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL())
        {
            // Тип запрограммированной сигнализации дискретного сигнала имеет более высокий приоритет,
            // чем тип общей сигнализации?
            if ((CPss21::GetCommonAlarmType() != ERROR) &&
                    (CPss21::GetCommonAlarmType() < ALARM_TYPE()))
            {
                // Установим тип общей сигнализацию.
                CPss21::SetCommonAlarmType(ALARM_TYPE());

                // Изменим тип общей сигнализацию.
                CPss21::AlarmTypeErrorChange();
            }

//            // Установим тип сигнализации связанному окну в массиве управления окнами извещателя.
            CPss21::ErrorWindowOn(GetAlarmWindowIndex());
            SetFsmState(RECEIPT_WAITING);
        }
        break;

    case RECEIPT_WAITING:
        // Событие квитировано?
        if (CPss21::GetDiscreteSignalsReceipt())
        {
            // Переведём автоматы сигнализаций в состояние - квитировано.
            CPss21::AlarmTypeReceipt();
            SetFsmState(RECEIPTED_NOT_ACTIVE_STATE_WAITING);
        }
        break;

    case RECEIPTED_NOT_ACTIVE_STATE_WAITING:
        // Дискретный сигнал не активен?
        if (!(CPss21::GetErrorAlarmState(GetDiscreteStateIndex()) ^ ACTIVE_LEVEL()))
        {
            // Переведём автоматы сигнализаций в состояние - сброшено.
            CPss21::AlarmTypeReset();
            CPss21::AllAlarmWindowOff();
            SetFsmState(ACTIVE_STATE_WAITING);
        }
        break;

    default:
        break;
    }
}
//-----------------------------------------------------------------------------------------------------









////-----------------------------------------------------------------------------------------------------
//CInputModuleErrorAlarmDfa::CInputModuleErrorAlarmDfa()
//{
//    SetFsmState(START);
//}
//
////-----------------------------------------------------------------------------------------------------
//CInputModuleErrorAlarmDfa::~CInputModuleErrorAlarmDfa()
//{
//    //dtor
//}
//
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
//COutpuModuleErrorAlarmDfa::COutpuModuleErrorAlarmDfa()
//{
//    SetFsmState(START);
//}
//
////-----------------------------------------------------------------------------------------------------
//COutpuModuleErrorAlarmDfa::~COutpuModuleErrorAlarmDfa()
//{
//    //dtor
//}
//
////-----------------------------------------------------------------------------------------------------







