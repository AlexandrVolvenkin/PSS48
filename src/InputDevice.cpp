//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "InputDevice.h"
#include "Platform.h"

////-----------------------------------------------------------------------------------------------------
//CInputDevice::CInputDevice()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//CInputDevice::CInputDevice(uint8_t (*fpuiEventSource)(void)) :
//    m_fpuiEventSource(fpuiEventSource)
//{
//    m_uiEventCode = KEY_EVENT_UNPRESSED;
//    SetFsmState(KEY_EVENT_UNPRESSED);
//}
//
////-----------------------------------------------------------------------------------------------------
//CInputDevice::~CInputDevice()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//void CInputDevice::SetCapabilities(uint8_t (*fpuiEventSource)(void))
//{
//    m_fpuiEventSource = fpuiEventSource;
//    m_uiEventCode = KEY_EVENT_UNPRESSED;
//    SetFsmState(KEY_EVENT_UNPRESSED);
//}
//
////-----------------------------------------------------------------------------------------------------
//uint8_t CInputDevice::EventHappened(void)
//{
//    if (m_fpuiEventSource())
//    {
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }
//
//}
//
////-----------------------------------------------------------------------------------------------------
//uint8_t CInputDevice::KeyEventHappened(uint8_t uiCode)
//{
//    Fsm();
//
//    if (m_uiEventCode == uiCode)
//    {
//        m_uiEventCode = KEY_EVENT_UNPRESSED;
//        m_uiPreliminaryEventCode = KEY_EVENT_UNPRESSED;
//        return 1;
//    }
//    else
//    {
//        return 0;
//    }
//
//}
//
////-----------------------------------------------------------------------------------------------------
//void CInputDevice::Fsm(void)
//{
//    // какое событие обрабатываем?
//    switch (GetFsmState())
//    {
//    case KEY_EVENT_UNPRESSED:
//        SetFsmState(KEY_EVENT_WAITING_PRESSED);
//        break;
//
//    case KEY_EVENT_WAITING_PRESSED:
//        // кнопка нажата?
//        if (EventHappened())
//        {
//            m_xTimer.Set(KEY_PRESSED_TIME_PUSH());
//            SetFsmState(KEY_EVENT_PRESSED_PUSH);
//        }
//        break;
//    case KEY_EVENT_PRESSED_PUSH:
//        // кнопка нажата?
//        if (EventHappened())
//        {
//            if (m_xTimer.IsOverflow())
//            {
//                m_xTimer.Set(KEY_PRESSED_TIME_HOLD());
//                m_uiEventCode = KEY_EVENT_PRESSED_PUSH;
//                SetFsmState(KEY_EVENT_PRESSED_HOLD);
//
//            }
//        }
//        else
//        {
//            SetFsmState(KEY_EVENT_UNPRESSED);
//        }
//        break;
//    case KEY_EVENT_PRESSED_HOLD:
//        // кнопка нажата?
//        if (EventHappened())
//        {
//            if (m_xTimer.IsOverflow())
//            {
//                m_xTimer.Set(KEY_PRESSED_HOLD_REPEAT_TIME());
//                m_uiEventCode = KEY_EVENT_PRESSED_HOLD;
//                SetFsmState(KEY_EVENT_PRESSED_REPEAT);
//
//            }
//        }
//        else
//        {
//            SetFsmState(KEY_EVENT_UNPRESSED);
//        }
//        break;
//
//    case KEY_EVENT_PRESSED_REPEAT:
//        // кнопка нажата?
//        if (EventHappened())
//        {
//            if (m_xTimer.IsOverflow())
//            {
//                m_xTimer.Set(KEY_PRESSED_HOLD_REPEAT_TIME());
//                m_uiEventCode = KEY_EVENT_PRESSED_REPEAT;
//            }
//        }
//        else
//        {
//            SetFsmState(KEY_EVENT_UNPRESSED);
//        }
//        break;
//    default:
//        break;
//    }
//}
////-----------------------------------------------------------------------------------------------------






////-----------------------------------------------------------------------------------------------------
//CRegularButton::CRegularButton()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//CRegularButton::~CRegularButton()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//bool CRegularButton::IsPressed(void)
//{
//
//
//}
//
////-----------------------------------------------------------------------------------------------------
//void CRegularButton::Fsm(void)
//{
//    // какое событие обрабатываем?
//    switch (GetFsmState())
//    {
//    case KEY_STATE_UNPRESSED:
//        m_uiEventCode = m_uiPreliminaryEventCode;
//        SetFsmState(KEY_STATE_WAITING_PRESSED);
//        break;
//
//    case KEY_STATE_WAITING_PRESSED:
//        // кнопка нажата?
//        if (IsActiveState())
//        {
//            m_xTimer.Set(KEY_PRESSED_TIME_RECEIPT());
//            SetFsmState(KEY_STATE_PRESSED_RECEIPT);
//        }
//        break;
//    case KEY_STATE_PRESSED_RECEIPT:
//        // кнопка нажата?
//        if (IsActiveState())
//        {
//            if (m_xTimer.IsOverflow())
//            {
//                m_xTimer.Set(KEY_PRESSED_TIME_RESET());
//                m_uiPreliminaryEventCode = KEY_EVENT_PRESSED_RECEIPT;
//                m_uiEventCode = m_uiPreliminaryEventCode;
//                SetFsmState(KEY_STATE_PRESSED_RESET);
//            }
//        }
//        else
//        {
//            m_uiEventCode = m_uiPreliminaryEventCode;
//            SetFsmState(KEY_STATE_UNPRESSED);
//        }
//        break;
//    case KEY_STATE_PRESSED_RESET:
//        // кнопка нажата?
//        if (IsActiveState())
//        {
//            if (m_xTimer.IsOverflow())
//            {
//                m_xTimer.Set(KEY_PRESSED_TIME_CHECK());
//                m_uiPreliminaryEventCode = KEY_EVENT_PRESSED_RESET;
//                SetFsmState(KEY_STATE_PRESSED_CHECK);
//
//            }
//        }
//        else
//        {
//            m_uiEventCode = m_uiPreliminaryEventCode;
//            SetFsmState(KEY_STATE_UNPRESSED);
//        }
//        break;
//
//    case KEY_STATE_PRESSED_CHECK:
//        // кнопка нажата?
//        if (IsActiveState())
//        {
//            if (m_xTimer.IsOverflow())
//            {
//                m_xTimer.Set(KEY_PRESSED_TIME_SET_DEFAULT());
//                m_uiPreliminaryEventCode = KEY_EVENT_PRESSED_CHECK;
//                SetFsmState(KEY_STATE_PRESSED_SET_DEFAULT);
//
//            }
//        }
//        else
//        {
//            m_uiEventCode = m_uiPreliminaryEventCode;
//            SetFsmState(KEY_STATE_UNPRESSED);
//        }
//        break;
//
//    case KEY_STATE_PRESSED_SET_DEFAULT:
//        // кнопка нажата?
//        if (IsActiveState())
//        {
//            if (m_xTimer.IsOverflow())
//            {
//                m_xTimer.Set(KEY_PRESSED_CHECK_REPEAT_TIME());
//                m_uiPreliminaryEventCode = KEY_EVENT_PRESSED_SET_DEFAULT;
//                m_uiEventCode = m_uiPreliminaryEventCode;
//                SetFsmState(KEY_STATE_UNPRESSED_WAITING);
//
//            }
//        }
//        else
//        {
//            SetFsmState(KEY_STATE_UNPRESSED);
//        }
//        break;
//
//    case KEY_STATE_UNPRESSED_WAITING:
//        // кнопка не нажата?
//        if (!(IsActiveState()))
//        {
//            SetFsmState(KEY_STATE_UNPRESSED);
//        }
//        break;
//
//
//    default:
//        break;
//    }
//}
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//CReceiptKey::CReceiptKey()
//{
//    m_fpuiEventSource = CPlatform::KeyOneState;
//    m_uiPreliminaryEventCode = KEY_EVENT_UNPRESSED;
//    m_uiEventCode = KEY_EVENT_UNPRESSED;
//    SetFsmState(KEY_STATE_UNPRESSED);
//}
//
////-----------------------------------------------------------------------------------------------------
//CReceiptKey::~CReceiptKey()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//bool CReceiptKey::IsReceipt(void)
//{
//
//
//}
//
////-----------------------------------------------------------------------------------------------------
//void CReceiptKey::Fsm(void)
//{
//
//
//}
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//CResetKey::CResetKey()
//{
//    m_fpuiEventSource = CPlatform::KeyTwoState;
//}
//
////-----------------------------------------------------------------------------------------------------
//CResetKey::~CResetKey()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//bool CResetKey::IsReset(void)
//{
//
//
//}
//
////-----------------------------------------------------------------------------------------------------
//void CResetKey::Fsm(void)
//{
//
//
//}
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//CCheckKey::CCheckKey()
//{
//    m_fpuiEventSource = CPlatform::KeyThreeState;
//}
//
////-----------------------------------------------------------------------------------------------------
//CCheckKey::~CCheckKey()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//bool CCheckKey::IsSetDefault(void)
//{
//
//
//}
//
////-----------------------------------------------------------------------------------------------------
//void CCheckKey::Fsm(void)
//{
//
//
//}
////-----------------------------------------------------------------------------------------------------
//
//
//
//
//
//
//
////-----------------------------------------------------------------------------------------------------
//CSetDefaultKey::CSetDefaultKey()
//{
//    m_fpuiEventSource = CPlatform::ExternalKeyState;
//}
//
////-----------------------------------------------------------------------------------------------------
//CSetDefaultKey::~CSetDefaultKey()
//{
//
//}
//
////-----------------------------------------------------------------------------------------------------
//bool CSetDefaultKey::IsSetDefault(void)
//{
//
//
//}
//
////-----------------------------------------------------------------------------------------------------
//void CSetDefaultKey::Fsm(void)
//{
//
//
//}
////-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
CMultiFunctionKey::CMultiFunctionKey()
{

}

//-----------------------------------------------------------------------------------------------------
CMultiFunctionKey::CMultiFunctionKey(uint8_t (*fpuiEventSource)(void))
{
    m_fpuiEventSource = fpuiEventSource;
    m_uiPreliminaryEventCode = KEY_EVENT_UNPRESSED;
    m_uiEventCode = KEY_EVENT_UNPRESSED;
    SetFsmState(KEY_EVENT_UNPRESSED);
}

//-----------------------------------------------------------------------------------------------------
CMultiFunctionKey::~CMultiFunctionKey()
{

}

//-----------------------------------------------------------------------------------------------------
void CMultiFunctionKey::SetCapabilities(uint8_t (*fpuiEventSource)(void))
{
    m_fpuiEventSource = fpuiEventSource;
    m_uiEventCode = KEY_EVENT_UNPRESSED;
    SetFsmState(KEY_EVENT_UNPRESSED);
}

//-----------------------------------------------------------------------------------------------------
uint8_t CMultiFunctionKey::EventHappened(void)
{
    if (m_fpuiEventSource())
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

//-----------------------------------------------------------------------------------------------------
uint8_t CMultiFunctionKey::KeyEventHappened(uint8_t uiCode)
{
    Fsm();

    if (m_uiEventCode == uiCode)
    {
        m_uiEventCode = KEY_EVENT_UNPRESSED;
        m_uiPreliminaryEventCode = KEY_EVENT_UNPRESSED;
        return 1;
    }
    else
    {
        return 0;
    }

}

//-----------------------------------------------------------------------------------------------------
void CMultiFunctionKey::Fsm(void)
{
    // какое событие обрабатываем?
    switch (GetFsmState())
    {
    case KEY_EVENT_UNPRESSED:
        m_uiEventCode = m_uiPreliminaryEventCode;
        SetFsmState(KEY_EVENT_WAITING_PRESSED);
        break;

    case KEY_EVENT_WAITING_PRESSED:
        // кнопка нажата?
        if (EventHappened())
        {
            m_xTimer.Set(KEY_PRESSED_TIME_RECEIPT());
            SetFsmState(KEY_EVENT_PRESSED_RECEIPT);
        }
        break;
    case KEY_EVENT_PRESSED_RECEIPT:
        // кнопка нажата?
        if (EventHappened())
        {
            if (m_xTimer.IsOverflow())
            {
                m_xTimer.Set(KEY_PRESSED_TIME_RESET());
                m_uiPreliminaryEventCode = KEY_EVENT_PRESSED_RECEIPT;
                m_uiEventCode = m_uiPreliminaryEventCode;
                SetFsmState(KEY_EVENT_PRESSED_RESET);
            }
        }
        else
        {
            m_uiEventCode = m_uiPreliminaryEventCode;
            SetFsmState(KEY_EVENT_UNPRESSED);
        }
        break;
    case KEY_EVENT_PRESSED_RESET:
        // кнопка нажата?
        if (EventHappened())
        {
            if (m_xTimer.IsOverflow())
            {
                m_xTimer.Set(KEY_PRESSED_TIME_CHECK());
                m_uiPreliminaryEventCode = KEY_EVENT_PRESSED_RESET;
                m_uiEventCode = m_uiPreliminaryEventCode;
                SetFsmState(KEY_EVENT_PRESSED_CHECK);

            }
        }
        else
        {
            m_uiEventCode = m_uiPreliminaryEventCode;
            SetFsmState(KEY_EVENT_UNPRESSED);
        }
        break;

    case KEY_EVENT_PRESSED_CHECK:
        // кнопка нажата?
        if (EventHappened())
        {
            if (m_xTimer.IsOverflow())
            {
                m_xTimer.Set(KEY_PRESSED_TIME_SET_DEFAULT());
                m_uiPreliminaryEventCode = KEY_EVENT_PRESSED_CHECK;
                m_uiEventCode = m_uiPreliminaryEventCode;
//                SetFsmState(KEY_EVENT_PRESSED_SET_DEFAULT);
                SetFsmState(KEY_EVENT_UNPRESSED_WAITING);

            }
        }
        else
        {
            m_uiEventCode = m_uiPreliminaryEventCode;
            SetFsmState(KEY_EVENT_UNPRESSED);
        }
        break;

    case KEY_EVENT_PRESSED_SET_DEFAULT:
        // кнопка нажата?
        if (EventHappened())
        {
            if (m_xTimer.IsOverflow())
            {
                m_xTimer.Set(KEY_PRESSED_CHECK_REPEAT_TIME());
                m_uiPreliminaryEventCode = KEY_EVENT_PRESSED_SET_DEFAULT;
                m_uiEventCode = m_uiPreliminaryEventCode;
                SetFsmState(KEY_EVENT_UNPRESSED_WAITING);

            }
        }
        else
        {
            SetFsmState(KEY_EVENT_UNPRESSED);
        }
        break;

    case KEY_EVENT_UNPRESSED_WAITING:
        // кнопка не нажата?
        if (!(EventHappened()))
        {
            SetFsmState(KEY_EVENT_UNPRESSED);
        }
        break;


    default:
        break;
    }
}
