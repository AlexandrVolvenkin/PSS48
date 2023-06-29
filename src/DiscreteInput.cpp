//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "DiscreteInput.h"
#include "Platform.h"

//-----------------------------------------------------------------------------------------------------
CDiscreteInput::CDiscreteInput()
{
    //ctor
}

//-----------------------------------------------------------------------------------------------------
CDiscreteInput::~CDiscreteInput()
{
    //dtor
}

////-----------------------------------------------------------------------------------------------------
//CDiscreteInputDriver::CDiscreteInputDriver(uint8_t uiType)
//{
//    //ctor
//}
//
////-----------------------------------------------------------------------------------------------------
//CDiscreteInputDriver::~CDiscreteInputDriver()
//{
//    //dtor
//}

//-----------------------------------------------------------------------------------------------------
CModbusDiscreteInputDriver::CModbusDiscreteInputDriver(uint8_t uiType)
{

}

//-----------------------------------------------------------------------------------------------------
CModbusDiscreteInputDriver::~CModbusDiscreteInputDriver()
{

}


//-----------------------------------------------------------------------------------------------------
void CModbusDiscreteInputDriver::Init(void)
{

}

//-----------------------------------------------------------------------------------------------------
void CModbusDiscreteInputDriver::Allocate(TMemoryAllocationConext &xMemoryAllocationConext)
{
    m_uiAddress = xMemoryAllocationConext.uiAddress;
    m_puiRxBuffer = xMemoryAllocationConext.puiRxBuffer;
    m_puiTxBuffer = xMemoryAllocationConext.puiTxBuffer;
    // Получим указатель на место в массиве дискретных входов для текущего модуля.
    m_puiDiscreteInputs =
        &xMemoryAllocationConext.
        puiDiscreteInputs[xMemoryAllocationConext.uiUsedDiscreteInputs];
    // Увеличим общий объём выделенной памяти.
    xMemoryAllocationConext.
    uiUsedDiscreteInputs +=
        MVSN21_DISCRETE_INPUTS_NUMBER;
}

//-----------------------------------------------------------------------------------------------------
uint16_t CModbusDiscreteInputDriver::ReportType(uint8_t *puiDestination, uint16_t uiLength)
{

}

//-----------------------------------------------------------------------------------------------------
uint8_t CModbusDiscreteInputDriver::DataExchange(void)
{

}
