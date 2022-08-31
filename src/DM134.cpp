//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "DM134.h"
#include "Platform.h"
#include "Pss21.h"
#include "LightBoard.h"

////-----------------------------------------------------------------------------------------------------
//CDM134::CDM134()
//{
//    Init();
//}
//
////-----------------------------------------------------------------------------------------------------
//CDM134::~CDM134()
//{
//
//}

//-----------------------------------------------------------------------------------------------------
void CDM134::Init(void)
{
    CPlatform::LedDriverClockOff();
    CPlatform::LedDriverSerialInOff();
    CPlatform::LedDriverLatchOff();
    CPlatform::LedDriverClockSetPinOutput();
    CPlatform::LedDriverSerialInSetPinOutput();
    CPlatform::LedDriverLatchSetPinOutput();
}

//-----------------------------------------------------------------------------------------------------
void CDM134::Set(uint8_t* puiBoardLampsControl, uint8_t uiLampNumber)
{
    for(uint8_t i = 0; i < uiLampNumber; i++)
    {
        if(puiBoardLampsControl[i])
        {
            CPlatform::LedDriverSerialInOn();
        }
        else
        {
            CPlatform::LedDriverSerialInOff();
        }


        CPlatform::LedDriverClockOn();
        CPlatform::LedDriverDelay1uS();
        CPlatform::LedDriverClockOff();
    }

    CPlatform::LedDriverLatchOff();
    CPlatform::LedDriverDelay5uS();
    CPlatform::LedDriverLatchOn();
}
