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
//class CInputDevice : public CDfa
//{
//public:
//// ??????? ??????????? ???????.
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
//    // ????? ????????? ?????? ? ??????? ?????????, ??????????? ??????? ?????????.
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
//    // ????? ?????????? ??? ??????? ??????.
//    virtual uint16_t KEY_PRESSED_HOLD_REPEAT_TIME(void)
//    {
//        return 50;
//    };
//
//protected:
//private:
//    // ????????? ?? ??????? - ???????? ???????.
//    uint8_t (*m_fpuiEventSource)(void);
//    uint8_t m_uiEventCode;
//    uint8_t m_uiPreliminaryEventCode;
//    CTimer m_xTimer;
//
//    friend class CMultiFunctionKey;
//};
////-----------------------------------------------------------------------------------------------------






//-----------------------------------------------------------------------------------------------------
class CMultiFunctionKey : public CDfa// : public CInputDevice
{
public:
// ??????? ??????????? ???????.
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

    // ????? ????????? ?????? ? ??????? ?????????, ??????????? ??????? ?????????.
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
    // ????? ?????????? ??? ??????? ??????.
    uint16_t KEY_PRESSED_CHECK_REPEAT_TIME(void)
    {
        return 50;
    };

protected:
private:
    // ????????? ?? ??????? - ???????? ???????.
    uint8_t (*m_fpuiEventSource)(void);
    uint8_t m_uiEventCode;
    uint8_t m_uiPreliminaryEventCode;
    CTimer m_xTimer;

};

#endif // CINPUTDEVICE_H
