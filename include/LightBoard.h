//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CLIGHTBOARD_H
#define CLIGHTBOARD_H

#include <stdint.h>
#include "AlarmWindow.h"
#include "DM134.h"

//-----------------------------------------------------------------------------------------------------
class CLightBoard
{
public:
//    CLightBoard();
//    virtual ~CLightBoard();
    static void Init(CAlarmWindow* pxAlarmWindowControl);
    static void Set(CAlarmWindow* pxAlarmWindowControl);

protected:
private:
    // ���������� ����������� ����������� ����� �����������-���������.
    static const uint8_t m_uiLedDriverLedNumber = 16;
    // ���������� ���������-��������� ����������� �� ������ �������.
    static const uint8_t m_uiLedDriversNumber = 4;
    static const uint8_t m_uiBoardLedNumber = m_uiLedDriverLedNumber * m_uiLedDriversNumber;

    // ������ ���������� ���������� ����������� �� ������.
    static uint8_t m_auiBoardLampsControl[m_uiBoardLedNumber];
    // ����� ������������ ������� ���� �� ������ � ������� ��������� ���������� � ������� ����������.
    static __flash uint8_t m_auiLedMap[];
};

#endif // CLIGHTBOARD_H
