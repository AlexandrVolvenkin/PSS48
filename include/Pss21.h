//-----------------------------------------------------------------------------------------------------
//  Source      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CPSS7_H
#define CPSS7_H

#include <stdint.h>
#include "Driver.h"
#include "Mvsn21.h"
#include "Platform.h"
#include "InputDevice.h"
#include "Dfa.h"
#include "AlarmWindow.h"
#include "Alarm.h"
#include "NotifyerControl.h"
#include "LightBoard.h"
#include "ModbusRTU.h"
#include "Event.h"
#include "DataTypes.h"
#include "LinkControl.h"
#include "DataBase.h"
#include "Task.h"

//-----------------------------------------------------------------------------------------------------
class CPss21
{
public:
    enum
    {
        START = 0,
        RESTART,
        MAIN_CYCLE_START_WAITING,
        MAIN_CYCLE_MODULES_INTERACTION,
        MAIN_CYCLE_DISCRETE_SIGNALS_PROCESSING,
        MAIN_CYCLE_END,

        TEST_START,
        TEST_ON,

        ERROR_START,
        ERROR_ON,

        LINK_CONTROL_ERROR_START,
        LINK_CONTROL_ERROR_ON,
        LINK_CONTROL_ERROR_OFF,

        PROGRAMMING_START,
        PROGRAMMING_ON,

        REBOOT,
    };

    static uint16_t TEST_ON_TIME(void)
    {
        return 5000;
    };
//    CPss21(uint8_t uiType, CDriver* pxDriver);
//    virtual ~CPss21();
    static void ModbusInit(void);
    static void ModbusDefaultInit(void);
    static void Init(void);
    static void SearchModules(void);
    static void InitAllocationContext(TMemoryAllocationConext & );
    static void CreateDevices(void);
    static void DestroyDevices(uint8_t uiLength);
    static void AddressBusInit(void);
    static void ConnectDevice(uint8_t );
    static void DisconnectDevice(void);
    static uint16_t ReportType(uint8_t * , uint16_t );
    static void SetBytesFromBits(uint8_t *uiDestination,
                                 uint8_t *uiSource,
                                 uint16_t uiLength);
    static void ModbusDeviceControl(uint8_t* puiData,
                                    uint16_t uiLength,
                                    uint16_t uiAddress);
    static void ModbusDeviceControl(uint8_t uiData, uint16_t uiAddress);
    static bool ModbusRtuLinkControlIsOn(void);
    static uint16_t GetTimeoutModbusRtuLinkControl(void);
    static bool ModbusRtuLinkControlInProgress(void);
    static void SetModeModbusRtuLinkControlInProgress(bool bData);
    static void SendToDevicesReceipt(void);
    static void SendToDevicesReset(void);
    static void SendToDevicesModbusReceipt(void);
    static void SendToDevicesModbusReset(void);
    static void KeyStateProcessing(void);
    static void ReceiptResetGlobalFlagsClear(void);
    static uint8_t ModulesInteraction(uint8_t uiModuleIndex);
    static void DiscreteOutputControlClear(void);
    static void ConfigurationInit(void);
    static void AlarmTypeChange(void);
    static void AlarmTypeErrorChange(void);
    static void AlarmTypeReceipt(void);
    static uint8_t GetDiscreteInputState(uint8_t uiIndex);
    static void SetErrorAlarmState(uint8_t uiIndex, uint8_t uiData);
    static uint8_t GetErrorAlarmState(uint8_t uiIndex);
    static void AlarmTypeSet(uint8_t uiAlarmType);
    static void AlarmTypeReset(void);
    static void NotifyersControlProcessing(void);
    static void SetAlarmWindowType(uint8_t uiAlarmWindowIndex, uint8_t uiAlarmType);
    static void SaveContextNotifyerControl(void);
    static void RestoreContextNotifyerControl(void);
    static void DiscreteOutputsSet(uint8_t *puiLinkedDiscreteOutputs, uint8_t uiNewViolation);
    static void AlarmsProcessing(void);
    static void ErrorAlarmsProcessing(void);
    static void DiscreteSignalsProcessing(void);
    static void BoardWindowsUpdate(void);
    static void ActiveAlarmWindowOn(uint8_t uiAlarmType);
    static void ActiveAlarmWindowOff(uint8_t uiAlarmType);
    static void AllAlarmWindowOn(uint8_t uiAlarmType);
    static void ErrorWindowOn(uint8_t uiIndex);
    static void AllAlarmWindowOff(void);
    static void TestMainCycle(void);
    static void ErrorMainCycle(void);
    static void LinkControlErrorMainCycle(void);
    static void MainFsm(void);

    static uint8_t GetFsmState(void)
    {
        return m_uiFsmState;
    };
    static void SetFsmState(uint8_t uiData)
    {
        m_uiFsmState = uiData;
    };

    static void SetPanelReceipt(uint8_t uiData)
    {
        m_uiPanelReceipt = uiData;
    };
    static uint8_t GetPanelReceipt(void)
    {
        return m_uiPanelReceipt;
    };
    static void SetPanelReset(uint8_t uiData)
    {
        m_uiPanelReset = uiData;
    };
    static uint8_t GetPanelReset(void)
    {
        return m_uiPanelReset;
    };

    static void SetExternalReceipt(uint8_t uiData)
    {
        m_uiExternalReceipt = uiData;
    };
    static uint8_t GetExternalReceipt(void)
    {
        return m_uiExternalReceipt;
    };
    static void SetExternalReset(uint8_t uiData)
    {
        m_uiExternalReset = uiData;
    };
    static uint8_t GetExternalReset(void)
    {
        return m_uiExternalReset;
    };

    static void SetModbusReceipt(uint8_t uiData)
    {
        m_uiModbusReceipt = uiData;
    };
    static uint8_t GetModbusReceipt(void)
    {
        return m_uiModbusReceipt;
    };
    static void SetModbusReset(uint8_t uiData)
    {
        m_uiModbusReset = uiData;
    };
    static uint8_t GetModbusReset(void)
    {
        return m_uiModbusReset;
    };

    static void SetDiscreteSignalsReceipt(uint8_t uiData)
    {
        m_uiDiscreteSignalsReceipt = uiData;
    };
    static uint8_t GetDiscreteSignalsReceipt(void)
    {
        return m_uiDiscreteSignalsReceipt;
    };
    static void SetDiscreteSignalsReset(uint8_t uiData)
    {
        m_uiDiscreteSignalsReset = uiData;
    };
    static uint8_t GetDiscreteSignalsReset(void)
    {
        return m_uiDiscreteSignalsReset;
    };

    static void SetCommonAlarmType(uint8_t uiData)
    {
        m_uiCommonAlarmType = uiData;
    };
    static uint8_t GetCommonAlarmType(void)
    {
        return m_uiCommonAlarmType;
    };

    static void SetCommonAlarmTypePrevious(uint8_t uiData)
    {
        m_uiCommonAlarmTypePrevious = uiData;
    };
    static uint8_t GetCommonAlarmTypePrevious(void)
    {
        return m_uiCommonAlarmTypePrevious;
    };

    static void SetErrorCode(uint8_t uiData)
    {
        m_uiErrorCode = uiData;
    };
    static uint8_t GetErrorCode(void)
    {
        return m_uiErrorCode;
    };

    static uint8_t GetModuleIndex(void)
    {
        return m_uiModuleIndex;
    };
    static void SetModuleIndex(uint8_t uiData)
    {
        m_uiModuleIndex = uiData;
    };

    static CAlarmWindow* GetAlarmWindowControlPointer(uint8_t uiAlarmWindowIndex)
    {
        return &m_axAlarmWindowControl[uiAlarmWindowIndex];
    };

protected:
private:
    static uint8_t m_uiFsmState;
    static uint8_t m_uiType;
    static CDriver* m_apxDrivers[INTERNAL_MODULE_QUANTITY];
    static CUart m_xUart1;

    static CMultiFunctionKey m_xReceiptKey;
    static CMultiFunctionKey m_xResetKey;
    static CMultiFunctionKey m_xCheckKey;
    static CMultiFunctionKey m_xExternalKey;

//    static CIsReceiptButtonPressed m_xIsReceiptButtonPressed;

    static uint8_t m_uiPanelReceipt;
    static uint8_t m_uiPanelReset;
    static uint8_t m_uiExternalReceipt;
    static uint8_t m_uiExternalReset;
    static uint8_t m_uiModbusReceipt;
    static uint8_t m_uiModbusReset;
    static uint8_t m_uiDiscreteSignalsReceipt;
    static uint8_t m_uiDiscreteSignalsReset;
    static uint8_t m_uiErrorCode;
    static uint8_t m_uiModuleIndex;
    static CEventUniteLogicAnd m_xEventUniteLogicAndOne;
    static CTimer m_xMainCycleTimer;

    // Тип сигнализации.
    static uint8_t m_uiCommonAlarmType;
    static uint8_t m_uiCommonAlarmTypePrevious;
    static CAlarmDfa *m_apxAlarmDfa[DISCRETE_SIGNALS_NUMBER];
    static CErrorAlarmDfa *m_apxErrorAlarmDfa[HANDLED_ERROR_NUMBER];
    static uint8_t m_auiErrorAlarmDataArray[HANDLED_ERROR_NUMBER];

    // Массив управления модулями дискретных выходов(реле).
    static TDiscreteOutputControl m_axDiscreteOutputControl[DISCRETE_OUTPUT_NUMBER];
    static TOutputData m_xDiscreteOutputDataBase;
    static CAlarmWindow m_axAlarmWindowControl[ALARM_WINDOWS_NUMBER];
    static __flash uint8_t m_auiErrorLedOn[ALARM_WINDOWS_NUMBER];

public:
//    static CDataStore m_xDataStore;
    static CModbusRTU m_xModbusRtuOne;
    static TConfigDataPackOne m_xDeviceConfigSearch;
    static TDevConfig m_xDeviceConfiguration;
    // Состояние устройства хранимое в EEPROM.
    static TDeviceState m_xDeviceState;
    static TMBusSetting m_xModbusSettings;
    static CModbusRtuLinkControl m_xModbusRtuLinkControl;
    static CPreventiveAlarmWindowNotifyerControl m_xPreventiveAlarmWindowNotifyerControl;
    static CEmergencyAlarmWindowNotifyerControl m_xEmergencyAlarmWindowNotifyerControl;
    static CStatusLedNotifyerControl m_xStatusLedNotifyerControl;
    static CBuzzerNotifyerControl m_xBuzzerNotifyerControl;
//    static CLightBoard m_xLightBoard;

//    static uint8_t m_aucRtuCoilsArray[COILS_WORK_ARRAY_LENGTH];
//    static uint8_t m_aucRtuDiscreteInputsArray[DISCRETE_INPUTS_ARRAY_LENGTH];
    static uint16_t m_aucRtuHoldingRegistersArray[HOLDING_REGISTERS_ARRAY_LENGTH];
    static uint16_t m_aucRtuInputRegistersArray[INPUT_REGISTERS_ARRAY_LENGTH];
    static uint8_t m_aucRtuDiscreteDataArray[DISCRETE_DATA_ARRAY_LENGTH];
    static uint8_t m_auiReceiveMessageBuff[MODBUS_RTU_MAX_ADU_LENGTH];
//    static uint8_t m_auiTransmitMessageBuff[MODBUS_RTU_MAX_ADU_LENGTH];
    static uint8_t m_auiIntermediateBuff[256];
    static uint8_t m_auiSpiRxBuffer[SPI_BUFFER_LENGTH];
    static uint8_t m_auiSpiTxBuffer[SPI_BUFFER_LENGTH];
};

//-----------------------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------------------------
#endif // CPSS7_H

