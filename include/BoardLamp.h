//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CBOARDLAMP_H
#define CBOARDLAMP_H

#include <stdint.h>

#include "Configuration.h"

//-----------------------------------------------------------------------------------------------------
class CBoardLamp
{
public:
    CBoardLamp();
    virtual ~CBoardLamp();
    void SetLampState(uint8_t uiData)
    {
        m_uiLampState = uiData;
    };
    uint8_t GetLampState(void)
    {
        return m_uiLampState;
    };

protected:
private:
    uint8_t m_uiLampState;
};

//-----------------------------------------------------------------------------------------------------
#endif // CBOARDLAMP_H
