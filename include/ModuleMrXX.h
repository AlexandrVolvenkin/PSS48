//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#ifndef CMODULEMRXX_H
#define CMODULEMRXX_H

//-----------------------------------------------------------------------------------------------------
#include <stdint.h>
#include "Device.h"
#include "Driver.h"
#include "DataTypes.h"

#include "Timer.h"
//#include "Task.h"
#include "Dfa.h"

//-----------------------------------------------------------------------------------------------------
enum
{
// состо€ние автомата - запись базы данных.
    MRXX_FSM_STATE_WRITE_DATABASE = 0x00,
// состо€ние автомата - нормальный обмен.
    MRXX_FSM_STATE_TRANSFER = 0x01,
};

enum
{
// байты состо€ни€ обмоток 8 реле модул€. только ћ–53.
// байт - 2: состо€ни€ обмоток реле, если бит = 1 - короткое замыкание.
    MRXX_STAT_DO_SHORT_CIRCUIT_BIT_OFFSET = 0,
// байт - 3: состо€ни€ обмоток реле, если бит = 1 - обрыв.
    MRXX_STAT_DO_BREACK_BIT_OFFSET = 1,
// код событи€ - включение-выключение реле.
    MRXX_ERROR_CODE_RELAY_ON_OFF = 0x01,
// код событи€ - включение-выключение реле.
    MRXX_ERROR_CODE_RELAY_SHORT_CIRCUIT = 0x04,
// код событи€ - включение-выключение реле.
    MRXX_ERROR_CODE_RELAY_BREACK = 0x08,
};

enum
{
// биты управлени€ ћ– байта f_bou.
// квитирование с верхнего уровн€.
    GLOBAL_KVIT_PC_BIT = 0,
// сброс с верхнего уровн€.
    GLOBAL_RESET_PC_BIT = 1,
// квитирование с цетральной панели ћ»Ќƒ.
    GLOBAL_KVIT_BUTTON_BIT = 2,
// сброс с цетральной панели ћ»Ќƒ.
    GLOBAL_RESET_BUTTON_BIT = 3,
// режим блокировки.
    GLOBAL_BLOCK_BIT = 4,
};

enum
{
// биты описател€ базы данных выходных дискретных сигналов.
// байт 0 (рез.,рез, ¬÷,—Ѕ÷,¬” ,¬”—,ЅЋ/“ ,“»ѕ).
// “»ѕ Ц тип выхода 0 Ц сигнализирующий, 1 Ц управл€ющий
    OUTPUT_TYPE_MASK = 0x01,
// ЅЋ/“ : дл€ управл€ющего выхода: 1 Ц с блокировкой, 0 Ц без блокировки;
// дл€ сигнализирующего выхода: - 1 квитирование с гашением (звук),
// 0 Ц квитирование с переводом в посто€нное значение (свет);
    BLOCK_ALARM_TYPE_MASK = 0x02,
// ¬”— Ц сброс с верхнего уровн€: 1 Ц есть, 0 Ц нет;
    PC_RESET_MASK = 0x04,
// ¬”  Ц квитирование с верхнего уровн€: 1 Ц есть, 0 Ц нет; (только дл€ сигн. выхода);
    PC_KVIT_MASK = 0x08,
// —Ѕ÷ Ц сброс с центральной панели ћ»Ќƒ: 1 Ц есть, 0 Ц нет;
    BUTTON_RESET_MASK = 0x10,
//  ¬÷ Ц квитирование с центральной панели ћ»Ќƒ: 1 Ц есть, 0 Ц нет (только дл€ сигн. выхода);
    BUTTON_KVIT_MASK = 0x20,
};

//-----------------------------------------------------------------------------------------------------




//-----------------------------------------------------------------------------------------------------
class CModuleMrXXDriver : public CDriver, public CDfa
{
public:
    enum
    {
        DATA_EXCHANGE_COMMAND = 0x42,
        DATA_READY = 0x42,
        // Ќормальное завершение обмена
        DATA_EXCHANGE_OK	= 0x7E,
        DATA_EXCHANGE_OK_LENGTH = 1,
        // ƒанные не готовы
        DATA_NOT_READY	= 0x24,
        // Ѕƒ повреждена
        DBASE_ERR	= 0x24,
        // «апрос на передачу базы данных от ћ÷ѕ к ћ– - $81.
        MRXX_SET_DATA_BASE_COMMAND = 0x81,
        // количество байт в пакете обмена данными, кроме, CRC - 2 байта и байта подтверждени€.
        MRXX_GET_DISCRETE_OUTPUT_DATA_COMMAND_ANSWER_LENGTH = 5,
        // количество байт в пакете записи базы данных, кроме, CRC - 2 байта и байта подтверждени€.
        MRXX_SET_DATA_BASE_COMMAND_ANSWER_LENGTH = 8,
        // длина ответного сообщени€ не включающа€ PREAMBLE_LENGTH + TWO_BYTE_CRC_LENGTH.
        DATA_EXCHANGE_COMMAND_ANSWER_LENGTH = 5,
        PRIAMBLE_LENGTH = 2,
        // 2 - смещение на данные в массиве RX SPI. 0 - команда запроса, 1 - "эхо" команды запроса.
        DATA_BYTE_OFFSET = 2,
        // 1 - смещение на команду в массиве RX SPI.
        COMMAND_BYTE_OFFSET = 1,
        COMMAND_BYTE_LENGTH = 1,
    };

    CModuleMrXXDriver(uint8_t uiType);
    CModuleMrXXDriver();
    virtual ~CModuleMrXXDriver();
    void Allocate(TMemoryAllocationConext &xMemoryAllocationConext);
    uint8_t WriteDataBase(void);
    uint8_t DataExchange(void);
    uint8_t Exchange(void);

protected:
private:
    uint8_t m_uiAddress;
    uint8_t *m_puiRxBuffer;
    uint8_t *m_puiTxBuffer;
    uint8_t *m_puiDiscreteInputs;
    uint8_t *m_puiDiscreteOutputState;
    TDiscreteOutputControl *m_pxDiscreteOutputControl;
    TOutputData *m_pxDiscreteOutputDataBase;
    uint8_t m_uiBadAnswerCounter;
};
//-----------------------------------------------------------------------------------------------------
#endif // CMODULEMRXX_H
