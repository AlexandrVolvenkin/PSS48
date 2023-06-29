#ifndef CTASK_H
#define CTASK_H
//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------

#include <stdint.h>

#include "Dfa.h"
#include "Timer.h"

//-----------------------------------------------------------------------------------------------------
class CTaskInterface : public CDfaLite
{
public:
    virtual bool IsSolved(void) {};

protected:
    virtual bool IsSourceStateActive(void) {};
};

//-----------------------------------------------------------------------------------------------------






////-----------------------------------------------------------------------------------------------------
//class CTask
//{
//public:
//    CTask();
//    virtual ~CTask();
//    bool IsSolved(void);
//protected:
//    bool IsSourceStateActive(void)
//    {
//
//    };
//};
//
////-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
class CIsRegularButtonPressedInterface : public CTaskInterface
{
public:
    bool IsSolved(void) {};

private:
    virtual bool IsSourceStateActive(void) {};
    // время состояния кнопки в нажатом состоянии, исключающее дребезг контактов.
    virtual uint16_t KEY_PRESSED_TIME(void) {};
};
//-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
class CIsReceiptButtonPressed : public CTaskInterface
{
private:
    enum
    {
        TASK_IDDLE = 0,
        TASK_START,
        KEY_STATE_UNPRESSED,
        KEY_STATE_PRESSED,
        TASK_IS_SOLVED,
    };

public:
    CIsReceiptButtonPressed();
    virtual ~CIsReceiptButtonPressed();
    bool IsSolved(void);
    void Fsm(void);

private:
    bool IsSourceStateActive(void);
    // время состояния кнопки в нажатом состоянии, исключающее дребезг контактов.
    uint16_t KEY_PRESSED_TIME(void)
    {
        return 100;
    };

protected:
    CTimer m_xTimer;
};
//-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
class CIsAlarmReset : public CTaskInterface
{
private:
    enum
    {
        TASK_IDDLE = 0,
        TASK_START,
        TASK_IS_SOLVED
    };

public:
    CIsAlarmReset();
    virtual ~CIsAlarmReset();
    bool IsSolved(void);
    void Fsm(void);

private:
};

//-----------------------------------------------------------------------------------------------------

#endif // CTASK_H
