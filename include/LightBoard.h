//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CLIGHTBOARD_H
#define CLIGHTBOARD_H

#include <stdint.h>
#include "Configuration.h"
#include "AlarmWindow.h"
#include "BoardLamp.h"
#include "DM134.h"

//-----------------------------------------------------------------------------------------------------
class CLightBoard
{
public:
    typedef CDM134 CLedDriver;

    CLightBoard();
    virtual ~CLightBoard();
    void Init(CAlarmWindow* pxAlarmWindowControl);
    void Set(void);

    // Количество светодиодов управляемых одной микросхемой-драйвером.
    static const uint8_t m_uiLedDriverLedNumber = 16;
    // Количество микросхем-драйверов светодиодов на панели прибора.
    static const uint8_t m_uiLedDriversNumber = 4;
    static const uint8_t m_uiBoardLedNumber = m_uiLedDriverLedNumber * m_uiLedDriversNumber;

protected:
private:
    CLedDriver m_xLedDriver;
    uint8_t m_auiBoardLampsControl[m_uiBoardLedNumber];
    CAlarmWindow* m_pxAlarmWindowControl;
    static __flash uint8_t m_auiLedMap[];
};

#endif // CLIGHTBOARD_H
