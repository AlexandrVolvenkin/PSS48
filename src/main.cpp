//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
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


enum
{
    MAIN_START,
    MAIN_FIRST_STEP,
    MAIN_SECOND_STEP,
    MAIN_THIRD_STEP,
    MAIN_FORTH_STEP,
    MAIN_THIRD_REBOOT,
    MAIN_STOP
};

//-----------------------------------------------------------------------------------------------------
int main()
{
//  test
//  uint8_t uiData;
//            uiData = i;
//            uiData = m_axDiscreteSignals[i].GetAlarmType();
//            uiData = m_axDiscreteSignals[i].GetAlarmState();
//            uiData = m_axDiscreteSignals[i].GetAlarmWindowIndex();
////            m_aucRtuHoldingRegistersArray[5] = m_axAlarmWindowControl[i].GetAlarmType();
//            uiData = m_axAlarmWindowControl[m_axDiscreteSignals[i].GetAlarmWindowIndex()].GetAlarmType();//m_axDiscreteSignals[i].GetAlarmWindowIndex();
//
////            m_aucRtuHoldingRegistersArray[1] = i;
////            m_aucRtuHoldingRegistersArray[2] = m_axDiscreteSignals[i].GetAlarmType();
////            m_aucRtuHoldingRegistersArray[3] = m_axDiscreteSignals[i].GetAlarmState();
////            m_aucRtuHoldingRegistersArray[4] = m_axDiscreteSignals[i].GetAlarmWindowIndex();
//            m_aucRtuHoldingRegistersArray[5] = m_axDiscreteSignals[i].GetAlarmState();
//            m_aucRtuHoldingRegistersArray[6] = m_axAlarmWindowControl[m_axDiscreteSignals[i].GetAlarmWindowIndex()].GetAlarmType();//m_axDiscreteSignals[i].GetAlarmWindowIndex();
//
//            // Тип запрограммированной сигнализации дискретного сигнала имеет более высокий приоритет,
//            // чем тип общей сигнализации?
//            if (m_uiCommonAlarmType != EMERGENCY)
//            {
//                // Установим тип общей сигнализацию.
//                m_uiCommonAlarmType = m_axDiscreteSignals[i].GetAlarmState();
//            }
////            CPss21::m_aucRtuHoldingRegistersArray[8 + i] = ((static_cast<uint16_t>(m_axAlarmWindowControl[i].GetActivityState()) << 8) | m_axAlarmWindowControl[i].GetAlarmType());
//        CPss21::m_aucRtuHoldingRegistersArray[8 + i] = (i | (static_cast<uint16_t>(m_axDiscreteSignals[i].GetAlarmWindowIndex()) << 8));
//        CPss21::m_aucRtuHoldingRegistersArray[8 + i] = ((static_cast<uint16_t>(i) << 8) | (static_cast<uint16_t>(m_axDiscreteSignals[i].GetAlarmWindowIndex()) & 0x00FF));

//    uint8_t auiTestHamming[16] =
//    {
//        0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
//    };
//
//    if (CDataStore::WriteAndCheck(auiTestHamming, (sizeof(auiTestHamming) - CDataStore::CRC_LENGTH), CDataStore::TEST_CONTEXT))
//    {
//        CDataStore::Read(auiTestHamming, CDataStore::TEST_CONTEXT);
//    }
//    else
//    {
//        CDataStore::Read(auiTestHamming, CDataStore::TEST_CONTEXT);
//    }

//    for (uint8_t i = 0;
//            i < ALARM_WINDOWS_NUMBER;
//            i++)
//    {
//        CPss21::m_aucRtuHoldingRegistersArray[8 + i] = ((static_cast<uint16_t>(m_axAlarmWindowControl[i].GetAlarmType()) << 8) | m_axAlarmWindowControl[i].GetActivityState());
//    };


//    struct TBlockPositionData
//    {
//        uint16_t uiOffset;
//        uint16_t uiLength;
//        uint16_t uiCrc;
//    };
//
//    struct TBlocksControlData
//    {
//        uint16_t uiFileNumber;
//        uint16_t uiCrc;
//        TBlockPositionData axBlockPositionData[8];
//    };
//
//    CDataStore xDataStore;

//    for (uint16_t i = 0; i < 256; i++)
//    {
//        CEeprom::WriteByte(i, 0x00);
//    }

//        // Восстановим БД по умолчанию.
//        for (uint8_t i = 0; i < 4; i++)
//        {
//            CPlatform::TxLedOn();//debag//
//            delay_ms(200);
//            CPlatform::TxLedOff();
//            delay_ms(200);
//        }
//            delay_ms(2000);


    uint8_t uiNumber = 0;
    uiNumber = sizeof(struct CDevice);
    uiNumber = sizeof(struct CAlarmDfa);
    uiNumber = sizeof(struct CPss21);
    uiNumber = sizeof(struct CDataStore::TBlocksControlData);
    uiNumber = CDataStore::BLOCKS_CONTROL_DATA_LENGTH;


    extern TDataBase __flash DBMain;
    uiNumber = sizeof(DBMain.ReceiptList);
    uiNumber = sizeof(DBMain.DeviceState);


//    uint8_t auiTempArray[9];
//    uint8_t auiCompareArray[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
//    uint8_t auiCompareArray2[9] = {0, 1, 2, 3, 4, 5, 7, 7, 8};
//
//    uint16_t uiLength = CHammingCodes::BytesToHammingCodes(CPss21::m_auiIntermediateBuff, auiCompareArray, 8);
//    CHammingCodes::HammingCodesToBytes(auiTempArray, CPss21::m_auiIntermediateBuff, uiLength);
//
//    if (memcmp(auiTempArray, auiCompareArray, 8))
//    {
//        uiNumber = 0;
//    }
//    else
//    {
//        uiNumber = 1;
//    }
//
//    if (memcmp(auiTempArray, auiCompareArray2, 8))
//    {
//        uiNumber = 0;
//    }
//    else
//    {
//        uiNumber = 1;
//    }

////-----------------------------------------------------------------------------------------------------
//
//    uint16_t uiSize;
//    uiSize = sizeof(struct TDataBase);
//    uiSize = sizeof(struct TDevConfig);
//    uiSize = sizeof(struct TMBusSetting);
//    uiSize = sizeof(struct TOutputData);
//    uiSize = sizeof(struct TMBMRequestList);

//    CPss21::m_aucRtuCoilsArray[0] = 7;
//    CPss21::m_aucRtuCoilsArray[1] = 0;
//    CPss21::m_aucRtuCoilsArray[2] = 5;
//    CPss21::m_aucRtuCoilsArray[3] = 0;
//
//    CPss21::m_aucRtuDiscreteInputsArray[0] = 7;
//    CPss21::m_aucRtuDiscreteInputsArray[1] = 0;
//
//    CPss21::m_aucRtuHoldingRegistersArray[0] = 17;
//    CPss21::m_aucRtuHoldingRegistersArray[1] = 0;
//    CPss21::m_aucRtuHoldingRegistersArray[2] = 321;
//    CPss21::m_aucRtuHoldingRegistersArray[3] = 48;
//
//    CPss21::m_aucRtuInputRegistersArray[0] = 0;
//    CPss21::m_aucRtuInputRegistersArray[1] = 17;
//    CPss21::m_aucRtuInputRegistersArray[2] = 256;
//    CPss21::m_aucRtuInputRegistersArray[3] = 987;

//    CUart xUart0(&UBRR0H, &UBRR0L, &UCSR0A, &UCSR0B, &UCSR0C, &UDR0, &DDRC, DDC7, &PORTC, PC7);
//    CPlatform::m_pxUart0 = &xUart0;

//-----------------------------------------------------------------------------------------------------

////    CPlatform::WatchdogEnable();
//    CPlatform::Init();
//    CBuzzer::Init();
//    CDataBase::Init();
//    CPss21::ConfigurationInit();
//    CPss21::Init();
//    CPlatform::InterruptEnable();
////    CTimer m_xMainCycleTimer(MAIN_CYCLE_PERIOD_TIME);
////    CTimer m_xPeripheryTimer(PERIPHERY_SCAN_TIME);
//    CSpi::Init();
//    CPss21::AddressBusInit();
//    CPss21::SearchModules();
//    CPss21::CreateDevices();
//
//    CPlatform::m_uiWatchDogStepID = 0;

    CPss21::SetFsmState(CPss21::START);

    while(1)
    {
        CPss21::MainFsm();
    }

    return 0;
}
