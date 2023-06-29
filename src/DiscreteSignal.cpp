//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "DiscreteSignal.h"
#include "Platform.h"

//-----------------------------------------------------------------------------------------------------
CDiscreteSignal::CDiscreteSignal()
{

}

//-----------------------------------------------------------------------------------------------------
CDiscreteSignal::~CDiscreteSignal()
{

}

////-----------------------------------------------------------------------------------------------------
//void CDiscreteSignal::Init(uint8_t uiActivityLevel,
//                           uint8_t uiAlarmType,
//                           uint8_t *puiSourseDiscreteInput,
//                           uint8_t *puiSourseModbusCoil)
//{
//    m_uiActivityLevel = uiActivityLevel;
//    m_uiAlarmType = uiAlarmType;
//    m_puiSourseDiscreteInput = puiSourseDiscreteInput;
//    m_puiSourseModbusCoil = puiSourseModbusCoil;
//}

//-----------------------------------------------------------------------------------------------------
void CDiscreteSignal::SetRelayOut(uint8_t uiModule, uint8_t uiRelay)
{
    if (uiModule < DISCRETE_OUTPUT_MODULE_MAX_NUMBER)
    {
        m_auiRelayOut[uiModule] |= (0x01 >> uiRelay);
    }
};

//-----------------------------------------------------------------------------------------------------
uint8_t CDiscreteSignal::GetRelayOut(uint8_t uiModule, uint8_t uiRelay)
{
    if (uiModule < DISCRETE_OUTPUT_MODULE_MAX_NUMBER)
    {
        return (m_auiRelayOut[uiModule] >> uiRelay);
    }
    else
    {
        return 0;
    }
};

//-----------------------------------------------------------------------------------------------------
uint8_t CDiscreteSignal::IsActive(void)
{
    if (GetDiscreteState() ^ GetActivityLevel())
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
