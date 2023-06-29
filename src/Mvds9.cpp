//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "Mvsn21.h"
#include "Platform.h"
#include "Config.h"
#include "Pss7.h"
//#include "Crc.h"

extern uint8_t auiSpiRxBuffer[CSpi::BUFFER_LENGTH];
extern uint8_t auiSpiTxBuffer[CSpi::BUFFER_LENGTH];
//-----------------------------------------------------------------------------------------------------
CMvsn21::CMvsn21(void)
{
    m_uiType = MODULE_TYPE_MVDS9;
    CMvsn21Driver xMvsn21Driver(m_uiType);
    m_pxDriver = &xMvsn21Driver;
}

//-----------------------------------------------------------------------------------------------------
CMvsn21::~CMvsn21()
{

}

//-----------------------------------------------------------------------------------------------------
uint16_t CMvsn21::ReportType(uint8_t *puiDestination, uint16_t uiLength)
{

}
//-----------------------------------------------------------------------------------------------------







//-----------------------------------------------------------------------------------------------------
CMvsn21Driver::CMvsn21Driver(uint8_t uiType)
{
    m_uiType = uiType;
}

//-----------------------------------------------------------------------------------------------------
CMvsn21Driver::~CMvsn21Driver()
{

}

//-----------------------------------------------------------------------------------------------------
uint16_t CMvsn21Driver::ReportType(uint8_t *puiDestination, uint16_t uiLength)
{
    memset(auiSpiTxBuffer, 0, 4);
    uint8_t uiLengthLocal = 0;
    auiSpiTxBuffer[uiLengthLocal++] = GET_MODULE_TYPE_COMMAND;
    auiSpiTxBuffer[uiLengthLocal++] = 0;
    auiSpiTxBuffer[uiLengthLocal++] = 0;
//    auiSpiTxBuffer[uiLengthLocal] = iCrcSummOneByteCalculation(auiSpiTxBuffer,
//                                    uiLengthLocal);
    // Размер сообщения на один больше, чтобы принять последний бвйт.
    uiLengthLocal++;
    CPss7::ConnectDevice(0);
    delay_us(500);
    CSpi::Exchange(auiSpiRxBuffer, auiSpiTxBuffer, uiLengthLocal);
    CPss7::DisconnectDevice();
}
