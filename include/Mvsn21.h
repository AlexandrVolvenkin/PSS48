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
#include "Driver.h"
#include "DataTypes.h"
#include "Dfa.h"

//-----------------------------------------------------------------------------------------------------
// Обмен данными модуля ввода дискретных сигналов МВДС9 с МЦП
// * Запрос на циклический обмен:$42
// Ответ:$42-данные готовы(ЭХО), $24-данные не готовы, конец связи
// * На выходе:сост.входов - 4б, доп.байт - 1б -> в sec1 - sec1+4
// байт 1:D0,D1-сост.вх.1, D2,D3-сост.вх.2,D4,D5-сост.вх.3,D6,D7-сост.вх.4
// байт 2:D0,D1-сост.вх.5, D2,D3-сост.вх.6,D4,D5-сост.вх.7,D6,D7-сост.вх.8
// байт 3:D0,D1-сост.вх.9, D2,D3-сост.вх.10,D4,D5-сост.вх.11,D6,D7-сост.вх.12
// байт 4:D0,D1-сост.вх.13, D2,D3-сост.вх.14,D4,D5-сост.вх.15,D6,D7-сост.вх.16
// байт 4:D0,D1-сост.вх.17, D2,D3-сост.вх.18,D4,D5-сост.вх.19,D6,D7-сост.вх.20
// байт 6:D0,D1-сост.вх.21, D2,D3-сост.вх.22,D4,D5-сост.вх.23,D6,D7-сост.вх.24
// байт 7: в ПАС-05 не используется
// байт 8: доп. байт
// байт 9: КС байтов 1-9

//  состояние входов в байтах 1-3:
//  четные биты (D0,D2,D4,D6) =0 - разомкнуто (OFF), =1 - замкнуто (ON)
//  нечетные биты (D1,D3,D5,D7) =0 - достоверно, =1 - недостоверно

class CMvsn21Driver : public CDriver, public CDfa
{
public:

    enum
    {
        DATA_EXCHANGE_COMMAND = 0x42,
        DATA_READY = 0x42,
        DATA_EXCHANGE_OK	= 0x7E,				// Нормальное завершение обмена
        DATA_NOT_READY	= 0x24,				// Данные не готовы
        DBASE_ERR	= 0x25,				// БД повреждена
        // длина ответного сообщения не включающая SPI_PREAMBLE_LENGTH + ONE_BYTE_CRC_LENGTH.
        DATA_EXCHANGE_COMMAND_ANSWER_LENGTH = 6,
        DISCRETE_INPUT_BYTE_QUANTITY = 6,
        DISCRETE_INPUT_BITS_IN_BYTE_QUANTITY = 8,
        DISCRETE_INPUTS_IN_BYTE_QUANTITY = 4,
        PRIAMBLE_LENGTH = 2,
        // 2 - смещение на данные в массиве RX SPI. 0 - команда запроса, 1 - "эхо" команды запроса.
        DATA_BYTE_OFFSET = 2,
        // 1 - смещение на команду в массиве RX SPI.
        COMMAND_BYTE_OFFSET = 1,
        COMMAND_BYTE_LENGTH = 1,
    };

    CMvsn21Driver(uint8_t uiType);
    virtual ~CMvsn21Driver();
    void Allocate(TMemoryAllocationConext &xMemoryAllocationConext);
    uint8_t DataExchange(void);

protected:
private:
    uint8_t m_uiAddress;
    uint8_t* m_puiRxBuffer;
    uint8_t* m_puiTxBuffer;
    uint8_t* m_puiDiscreteInputs;
    uint8_t m_uiBadAnswerCounter;
};

#endif // CMVDS9_H

