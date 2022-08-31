//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------

#include "Platform.h"
#include "Timer.h"

//-----------------------------------------------------------------------------------------------------
CTimer::CTimer()
{

}

//-----------------------------------------------------------------------------------------------------
CTimer::CTimer(uint16_t uiTime)
{
    m_uiLastSystemTick = CPlatform::GetSystemTick();
    m_uiTime = uiTime;
}

//-----------------------------------------------------------------------------------------------------
CTimer::~CTimer()
{

}

//-----------------------------------------------------------------------------------------------------
void CTimer::Set(uint16_t uiTime)
{
    m_uiLastSystemTick = CPlatform::GetSystemTick();
    m_uiTime = uiTime;
}

//-----------------------------------------------------------------------------------------------------
void CTimer::Reset(void)
{
    m_uiLastSystemTick = CPlatform::GetSystemTick();
}

//-----------------------------------------------------------------------------------------------------
bool CTimer::IsOverflow(void)
{
    //    if ((CPlatform::GetSystemTick() - m_uiLastSystemTick)  >=
//            m_uiTime)
//    {
//        return true;
//    }
//    else
//    {
//        return false;
//    }
    return ((CPlatform::GetSystemTick() - m_uiLastSystemTick)  >=
            m_uiTime);
}

//-----------------------------------------------------------------------------------------------------

