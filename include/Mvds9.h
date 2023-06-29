//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CMVDS9_H
#define CMVDS9_H

#include <stdint.h>
#include "Device.h"
#include "Driver.h"

//-----------------------------------------------------------------------------------------------------
class CMvsn21 : virtual public CDevice
{
public:
    CMvsn21(void);
    CMvsn21(uint8_t uiType, CDriver* pxDriver);
    virtual ~CMvsn21();
    uint16_t ReportType(uint8_t * , uint16_t );

protected:
private:

};

//-----------------------------------------------------------------------------------------------------
class CMvsn21Driver : virtual public CDriver
{
public:
    CMvsn21Driver(uint8_t uiType);
    virtual ~CMvsn21Driver();
    uint16_t ReportType(uint8_t * , uint16_t );

protected:
private:
};

#endif // CMVDS9_H

