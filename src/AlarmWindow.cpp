//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "AlarmWindow.h"
#include "Platform.h"

//-----------------------------------------------------------------------------------------------------

CAlarmWindow::CAlarmWindow()
{
    m_uiActivityState = 0;
    m_uiSavedActivityState = 0;
    m_uiAlarmType = NORMAL;
    m_uiSavedAlarmType = NORMAL;
}

CAlarmWindow::~CAlarmWindow()
{

}
