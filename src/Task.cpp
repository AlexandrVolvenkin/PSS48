
//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "Task.h"
#include "Platform.h"

////-----------------------------------------------------------------------------------------------------
//CTask::CTask()
//{
//
//}
//
//
////-----------------------------------------------------------------------------------------------------
//CTask::~CTask()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
CIsReceiptButtonPressed::CIsReceiptButtonPressed()
{
    SetFsmState(TASK_START);
}

//-----------------------------------------------------------------------------------------------------
CIsReceiptButtonPressed::~CIsReceiptButtonPressed()
{

}

//-----------------------------------------------------------------------------------------------------
bool CIsReceiptButtonPressed::IsSourceStateActive(void)
{
    if (CPlatform::KeyOneState())
    {
        return true;
    }
    else
    {
        return false;
    }
}

//-----------------------------------------------------------------------------------------------------
void CIsReceiptButtonPressed::Fsm(void)
{
    // какое событие обрабатываем?
    switch (GetFsmState())
    {
    case TASK_IDDLE:
        break;

    case TASK_START:
        SetFsmState(KEY_STATE_UNPRESSED);
        break;

    case KEY_STATE_UNPRESSED:
        // кнопка нажата?
        if (IsSourceStateActive())
        {
            m_xTimer.Set(KEY_PRESSED_TIME());
            SetFsmState(KEY_STATE_PRESSED);
        }
        break;
    case KEY_STATE_PRESSED:
        // кнопка нажата?
        if (IsSourceStateActive())
        {
            if (m_xTimer.IsOverflow())
            {
                SetFsmState(TASK_IS_SOLVED);
            }
        }
        else
        {
            SetFsmState(KEY_STATE_UNPRESSED);
        }
        break;

    case TASK_IS_SOLVED:
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------------------
bool CIsReceiptButtonPressed::IsSolved(void)
{
    if (GetFsmState() == TASK_IS_SOLVED)
    {
        SetFsmState(TASK_START);
        return true;
    }
    else
    {
        return false;
    }
}

//-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
CIsAlarmReset::CIsAlarmReset()
{
    SetFsmState(TASK_START);
}

//-----------------------------------------------------------------------------------------------------
CIsAlarmReset::~CIsAlarmReset()
{

}

//-----------------------------------------------------------------------------------------------------
void CIsAlarmReset::Fsm(void)
{
    // какое событие обрабатываем?
    switch (GetFsmState())
    {
    case TASK_IDDLE:
        break;

    case TASK_START:
        break;

    case TASK_IS_SOLVED:
        break;

    default:
        break;
    }
}

//-----------------------------------------------------------------------------------------------------
bool CIsAlarmReset::IsSolved(void)
{
    if (GetFsmState() == TASK_IS_SOLVED)
    {
        SetFsmState(TASK_START);
        return true;
    }
    else
    {
        return false;
    }
}

//-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
