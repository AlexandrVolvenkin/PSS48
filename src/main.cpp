//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "Platform.h"
#include "Timer.h"
#include "Modbus.h"
#include "ModbusRTU.h"
#include "InputDevice.h"
#include "Pss21.h"
#include "Mvsn21.h"
#include "Buzzer.h"
#include "DataStore.h"
#include "Alarm.h"
#include "HammingCodes.h"
#include "NotifyerControl.h"

//-----------------------------------------------------------------------------------------------------
int main()
{
    CPss21::SetFsmState(CPss21::START);

    while(1)
    {
        CPss21::MainFsm();
    }

    return 0;
}
