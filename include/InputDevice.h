//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CINPUTDEVICE_H
#define CINPUTDEVICE_H

//-----------------------------------------------------------------------------------------------------
#include <stdint.h>

#include "Timer.h"
//#include "Task.h"
#include "Dfa.h"

//-----------------------------------------------------------------------------------------------------
enum
{
    KEY_ONE = 1,
    KEY_TWO,
    KEY_THREE
};


////-----------------------------------------------------------------------------------------------------
//class CInputDeviceInterface : public CDfa
//{
//public:
//    virtual bool IsReceipt(void) {};
//    virtual bool IsReset(void) {};
//    virtual bool IsSetDefault(void) {};
//
//protected:
//    // время состояния кнопки в нажатом состоянии, исключающее дребезг контактов.
//    virtual uint16_t KEY_PRESSED_TIME_PUSH(void) {};
//    virtual uint16_t KEY_PRESSED_TIME_HOLD(void) {};
//    virtual uint16_t KEY_PRESSED_TIME_CHECK(void) {};
//    // время промежутка при зажатой кнопке.
//    virtual uint16_t KEY_PRESSED_HOLD_REPEAT_TIME(void) {};
//
//    virtual bool IsActiveState(void);
//    virtual void Fsm(void) {};
//};
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//class CRegularButton : public CInputDeviceInterface
//{
//// Состояния автомата.
//    enum
//    {
//        KEY_STATE_UNPRESSED = 0,
//        KEY_STATE_WAITING_PRESSED,
//        KEY_STATE_PRESSED_PUSH,
//        KEY_STATE_PRESSED_RECEIPT = KEY_STATE_PRESSED_PUSH,
//        KEY_STATE_PRESSED_HOLD,
//        KEY_STATE_PRESSED_RESET = KEY_STATE_PRESSED_HOLD,
//        KEY_STATE_PRESSED_CHECK,
//        KEY_STATE_PRESSED_SET_DEFAULT,
//        KEY_STATE_PRESSED_REPEAT,
//        KEY_STATE_UNPRESSED_WAITING,
//    };
//
//// события создаваемые кнопкой.
//    enum
//    {
//        KEY_EVENT_UNPRESSED = 0,
//        KEY_EVENT_WAITING_PRESSED,
//        KEY_EVENT_PRESSED_PUSH,
//        KEY_EVENT_PRESSED_RECEIPT = KEY_EVENT_PRESSED_PUSH,
//        KEY_EVENT_PRESSED_HOLD,
//        KEY_EVENT_PRESSED_RESET = KEY_EVENT_PRESSED_HOLD,
//        KEY_EVENT_PRESSED_CHECK,
//        KEY_EVENT_PRESSED_SET_DEFAULT,
//        KEY_EVENT_PRESSED_REPEAT,
//        KEY_EVENT_UNPRESSED_WAITING,
//    };
//
//public:
//    CRegularButton();
//    virtual ~CRegularButton();
//    bool IsPressed(void);
//
//private:
//    // время состояния кнопки в нажатом состоянии, исключающее дребезг контактов.
//    uint16_t KEY_PRESSED_TIME_PUSH(void)
//    {
//        return 100;
//    };
//    uint16_t KEY_PRESSED_TIME_HOLD(void)
//    {
//        return 1500;
//    };
//    uint16_t KEY_PRESSED_TIME_CHECK(void)
//    {
//        return 3000;
//    };
//    // время промежутка при зажатой кнопке.
//    uint16_t KEY_PRESSED_HOLD_REPEAT_TIME(void)
//    {
//        return 50;
//    };
//
//    bool IsActiveState(void)
//    {
//        if (m_fpuiStateSource())
//        {
//            return true;
//        }
//        else
//        {
//            return false;
//        }
//    };
//    void Fsm(void);
//
//protected:
//    // указатель на функцию - источник состояния.
//    uint8_t (*m_fpuiStateSource)(void);
//    uint8_t m_uiEventCode;
//    uint8_t m_uiPreliminaryEventCode;
//    CTimer m_xTimer;
//};
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//class CInputDevice : public CDfa
//{
//public:
//// события создаваемые кнопкой.
//    enum
//    {
//        KEY_EVENT_UNPRESSED = 0,
//        KEY_EVENT_WAITING_PRESSED,
//        KEY_EVENT_PRESSED_PUSH,
//        KEY_EVENT_PRESSED_RECEIPT = KEY_EVENT_PRESSED_PUSH,
//        KEY_EVENT_PRESSED_HOLD,
//        KEY_EVENT_PRESSED_RESET = KEY_EVENT_PRESSED_HOLD,
//        KEY_EVENT_PRESSED_CHECK,
//        KEY_EVENT_PRESSED_SET_DEFAULT,
//        KEY_EVENT_PRESSED_REPEAT,
//        KEY_EVENT_UNPRESSED_WAITING,
//    };
//
//    CInputDevice();
//    CInputDevice(uint8_t (* )(void));
//    virtual ~CInputDevice();
//    void SetCapabilities(uint8_t (* )(void));
//    uint8_t EventHappened(void);
//    uint8_t KeyEventHappened(uint8_t );
//    void Fsm(void);
//
//    // время состояния кнопки в нажатом состоянии, исключающее дребезг контактов.
//    virtual uint16_t KEY_PRESSED_TIME_PUSH(void)
//    {
//        return 100;
//    };
//    virtual uint16_t KEY_PRESSED_TIME_HOLD(void)
//    {
//        return 1500;
//    };
//    virtual uint16_t KEY_PRESSED_TIME_CHECK(void)
//    {
//        return 3000;
//    };
//    // время промежутка при зажатой кнопке.
//    virtual uint16_t KEY_PRESSED_HOLD_REPEAT_TIME(void)
//    {
//        return 50;
//    };
//
//protected:
//private:
//    // указатель на функцию - источник события.
//    uint8_t (*m_fpuiEventSource)(void);
//    uint8_t m_uiEventCode;
//    uint8_t m_uiPreliminaryEventCode;
//    CTimer m_xTimer;
//
//    friend class CMultiFunctionKey;
//};
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//class CReceiptKey : public CInputDeviceInterface
//{
//public:
//    CReceiptKey();
//    virtual ~CReceiptKey();
//    bool IsReceipt(void);
//
//private:
////    bool IsEventHappened(void);
//    void Fsm(void);
//};
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//class CIsAlarmReset : public CInputDeviceInterface
//{
//public:
//    CResetKey();
//    virtual ~CResetKey();
//    bool IsSolved(void);
//
//private:
////    bool IsEventHappened(void);
//    void Fsm(void);
//};
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//class CResetKey : public CInputDeviceInterface
//{
//public:
//    CResetKey();
//    virtual ~CResetKey();
//    bool IsReset(void);
//
//private:
////    bool IsEventHappened(void);
//    void Fsm(void);
//};
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//class CCheckKey : public CInputDeviceInterface
//{
//public:
//    CCheckKey();
//    virtual ~CCheckKey();
//    bool IsSetDefault(void);
//
//private:
////    bool IsEventHappened(void);
//    void Fsm(void);
//};
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//class CSetDefaultKey : public CInputDeviceInterface
//{
//public:
//    CSetDefaultKey();
//    virtual ~CSetDefaultKey();
//    bool IsSetDefault(void);
//
//private:
////    bool IsEventHappened(void);
//    void Fsm(void);
//};
////-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
class CMultiFunctionKey : public CDfa// : public CInputDevice
{
public:
// события создаваемые кнопкой.
    enum
    {
        KEY_EVENT_UNPRESSED = 0,
        KEY_EVENT_WAITING_PRESSED,
        KEY_EVENT_PRESSED_PUSH,
        KEY_EVENT_PRESSED_RECEIPT = KEY_EVENT_PRESSED_PUSH,
        KEY_EVENT_PRESSED_HOLD,
        KEY_EVENT_PRESSED_RESET = KEY_EVENT_PRESSED_HOLD,
        KEY_EVENT_PRESSED_CHECK,
        KEY_EVENT_PRESSED_SET_DEFAULT,
        KEY_EVENT_PRESSED_REPEAT,
        KEY_EVENT_UNPRESSED_WAITING,
    };

    CMultiFunctionKey();
    CMultiFunctionKey(uint8_t (* )(void));
    virtual ~CMultiFunctionKey();
    void SetCapabilities(uint8_t (* )(void));
    uint8_t EventHappened(void);
    uint8_t KeyEventHappened(uint8_t );
    void Fsm(void);

    // время состояния кнопки в нажатом состоянии, исключающее дребезг контактов.
    uint16_t KEY_PRESSED_TIME_RECEIPT(void)
    {
        return 100;
    };
    uint16_t KEY_PRESSED_TIME_RESET(void)
    {
        return 1500;
    };
    uint16_t KEY_PRESSED_TIME_CHECK(void)
    {
        return 3000;
    };
    uint16_t KEY_PRESSED_TIME_SET_DEFAULT(void)
    {
        return 5000;
    };
    // время промежутка при зажатой кнопке.
    uint16_t KEY_PRESSED_CHECK_REPEAT_TIME(void)
    {
        return 50;
    };

protected:
private:
    // указатель на функцию - источник события.
    uint8_t (*m_fpuiEventSource)(void);
    uint8_t m_uiEventCode;
    uint8_t m_uiPreliminaryEventCode;
    CTimer m_xTimer;

};

#endif // CINPUTDEVICE_H
