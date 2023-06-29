//------------------------------------------------------------------------------
// Описание типов данных
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#ifndef __DATA_TYPES_H
#define __DATA_TYPES_H
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Версия программного обеспечения
struct TFirmwareVersion
{
 unsigned char Major;
 unsigned char Minor;
 unsigned char Hardware;
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Конфигурация устройства (НОВАЯ v1.60)
//#pragma bitfields = default                                                     // OK
struct TDevConfig
{
 unsigned char  ICount;			// Число модулей ввода
 unsigned char  OCount;			// Число модулей вывода
 unsigned char  Windows;		// Число окон сигнализации

 unsigned short FixConfig :  1;		// Признак фиксированной конфигурации 
 unsigned short MBusMaster:  1;		// Признак режима ModBus-Master
 unsigned short 	  : 14;		// РЕЗЕРВ	

 unsigned char MBTimeout;		// Таймаут канала ModBus
 unsigned char PRTimeout;               // Таймаут автоквитирования предупредительной сигнализации

 char BYTE[13];				// РЕЗЕРВ
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Настройки интерфейса ModBus
struct TMBusSetting
{
 unsigned char NetAddress;		// Сетевой адрес
 unsigned char BaudRate;		// Скорость обмена
 unsigned char LinkParam;		// Число стоп-бит, паритет
 unsigned char Interval;		// Интервал таймера
 unsigned char Prescaler;		// Делитель таймера
 unsigned char Silent[2];		// 2 байта под дополнительную задержку

 enum
 {
  STOPBITS_MASK = 0x08,
  PARITY_MASK   = 0x30,

  ONESTOPBITS	= 0x00,			// Один стоп-бит
  TWOSTOPBITS	= 0x08,			// Два стоп-бита
  NOPARITY	= 0x00,			// Без паритета
  EVENPARITY	= 0x20,			// Четный паритет
  ODDPARITY	= 0x30			// Нечетный паритета
 };
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Описатель настроек каналов индикации
#pragma bitfields = reversed
union TChannelSetting
{
 struct
 {
  unsigned char NoSound:	1;	// Признак отключения звука
  unsigned char :		3;
  unsigned char Type:		4;	// Тип отображения / обработки
 };

 unsigned char Byte;

 enum TYPE_INDICATION
 {
  EMPTY		 = 0,			// Нет отображения
  INDICATION	 = 1,			// Индикация
  PREVENTIVE	 = 2,			// Предупредительная сигнализация
  EMERGENCY	 = 3,			// Аварийная сигнализация

  IND_PREVENTIVE = 4,			// Индикация + предупредительная сигнализация
  IND_EMERGENCY  = 5			// Индикация + аварийная сигнализация
 };
};
//#pragma bitfields = default
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Описатель обработчиков функций протокола ModBus
struct TMBusHandler
{
 unsigned char Function;		// Номер функции
 unsigned char Lenght;			// Длинна сообщения
 unsigned char Flags;			// Флаги

 enum MBSH_FLAGS
 {
  FIX_LENGHT  = 0x00,			// Запрос фиксированной длинны
  VAR_LENGHT  = 0x80			// Флаг переменной длинны сообщения
 };

 unsigned char (*Handler)(unsigned char *Buff,unsigned char Lenght);

// TMBusHandler(void):Function(0xFF),Lenght(0),Flags(0),Handler(0){ };
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Описатель запроса ModBus Master
struct TMBMRequest
{
 unsigned char  NetAddress;		// Сетевой адрес устройства
 unsigned char  Function;		// Функция
 unsigned short Address;		// Адрес данных
 unsigned char  Value;			// Значение
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Описатель списка запросов ModBus Master
struct TMBMRequestList
{
 unsigned char Number;			// Число элементов списка
 TMBMRequest   Request[16];		// Запросы ModBus Master
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Описатель настроек канала модуля вывода
#pragma bitfields = reversed
union TOutSetting
{
 struct
 {
  unsigned char :		2;
  unsigned char LocalReceipt:	1;	// Квитирование с панели
  unsigned char LocalUnset:	1;	// Сброс с панели
  unsigned char MBusReceipt:	1;	// Квитирование с верхнего уровня
  unsigned char MBusUnset:	1;	// Сброс с верхнего уровня
  unsigned char Mode:		2;	// Режим выхода
 };

 unsigned char Byte;

 enum OUT_MODE
 {
  LIGHT_SIGNALING  = 0x00,		// Световая сигнализация
  SOUND_SIGNALING  = 0x02,		// Звуковая сигнализация
  CONTROL	   = 0x01,		// Управляющий выход
  SELFHOLD_CONTROL = 0x03		// Управляющий выход с самоблокировкой
 };

 operator unsigned char()		// Оператор преобразования к unsigned char
 {
  return Byte; 
 };
};
//#pragma bitfields = default
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Данные, передаваемые модулям вывода [##]
#pragma bitfields = reversed
struct TOutData
{
 unsigned char Current;			// Текущее состояние
 unsigned char New;			// Вновь возникшие срабатывания
 unsigned char ExtReceipt;		// Внешнее квитирование
 unsigned char ExtUnset;		// Внешний сброс

 unsigned char :		3;
 unsigned char Blocking:	1;	// Блокировка
 unsigned char LocalUnset:	1;	// Сброс с панели
 unsigned char LocalReceipt:	1;	// Квитирование с панели
 unsigned char MBusUnset:	1;	// Сброс с верхнего уровня
 unsigned char MBusReceipt:	1;	// Квитирование с верхнего уровня
};
//#pragma bitfields = default
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// Описатель канала вывода
struct TOutputData
{
 unsigned char OutBase[8];		// Настройки МР-54
 unsigned char ReceiptAddr[8];		// Адреса входов внешнего квитирования
 unsigned char UnsetAddr[8];		// Адреса входов внешнего сброса
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
/*
// Конфигурация устройства
struct TDevConfiguration
{
 unsigned char ICount;			// Число модулей ввода
 unsigned char OCount;			// Число модулей вывода

 bool FixConfig;			// Признак фиксированной конфигурации 
 bool MBusMaster;			// Признак режима ModBus-Master
 bool LED16Mode;			// Признак использования больших окон индикации

 unsigned char MBTimeout;		// Таймаут канала ModBus

 char BYTE[10];				// Стратегический запас партии
}; 
*/ 
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// БД настроек прибора
struct TDataBase
{
 TDevConfig	DevConfig;		// Конфигурация устройства
 unsigned short CRC0;

 TMBusSetting   MBSet;			// Параметры интерфейса ModBus
 unsigned short CRC1;

 unsigned char  InputType[8];		// Тип входа
 unsigned short CRC2;

 unsigned char  CrossBar[64];		// Переадресация
 unsigned short CRC3;

 unsigned char  ChannelType[32];	// Типы сигнализации по окнам 
 unsigned short CRC4;

 TOutputData    OutConfig;		// БД модулей вывода
 unsigned short CRC5;

 unsigned char  Relay[64];		// Выходные реле, сопоставленные физическим входам
 unsigned short CRC6;

 TMBMRequestList InputList;		// Список запросов сбора данных
 unsigned short  CRC7;

 TMBMRequestList ReceiptList;		// Список запросов квитирования
 unsigned short  CRC8;

 TMBMRequestList UnsetList;		// Список запросов сброса
 unsigned short  CRC9;

 enum DB_FIELDS
 {
  DEV_CONFIG	= 0,			// Конфигурация устройства
  MODBUS_SET	= 1,			// Параметры интерфейса ModBus
  INPUT_TYPE	= 2,			// Тип входа
  CROSS_BAR	= 3,			// Переадресация
  CHANNEL_TYPE	= 4,			// Типы сигнализации по окнам 
  OUT_BASE	= 5,			// БД модулей вывода
  RELAY		= 6,			// Выходные реле, сопоставленные физическим входам
  INPUT_LIST	= 7,			// Запросы сбора данных
  RECEIPT_LIST	= 8,			// Запросы квитирования
  UNSET_LIST	= 9			// Запросы сброса
 };
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// БД настроек прибора - Максимум 64 ОКНА
struct TDataBaseNEW
{
 TDevConfig	DevConfig;		// Конфигурация устройства
 unsigned short CRC0;

 TMBusSetting   MBSet;			// Параметры интерфейса ModBus
 unsigned short CRC1;

 unsigned char  InputType[2*8];		// Тип входа (2 * 64 бит / 8 = 16 байт)
 unsigned short CRC2;

 unsigned char  CrossBar[2*64];		// Переадресация
 unsigned short CRC3;

 unsigned char  ChannelType[2*32];	// Типы сигнализации по окнам 
 unsigned short CRC4;

 TOutputData    OutConfig;		// БД модулей вывода
 unsigned short CRC5;

 unsigned char  Relay[2*64];		// Выходные реле, сопоставленные физическим входам
 unsigned short CRC6;

 TMBMRequestList InputList;		// Список запросов сбора данных
 unsigned short  CRC7;

 TMBMRequestList ReceiptList;		// Список запросов квитирования
 unsigned short  CRC8;

 TMBMRequestList UnsetList;		// Список запросов сброса
 unsigned short  CRC9;

 enum DB_FIELDS
 {
  DEV_CONFIG	= 0,			// Конфигурация устройства
  MODBUS_SET	= 1,			// Параметры интерфейса ModBus
  INPUT_TYPE	= 2,			// Тип входа
  CROSS_BAR	= 3,			// Переадресация
  CHANNEL_TYPE	= 4,			// Типы сигнализации по окнам 
  OUT_BASE	= 5,			// БД модулей вывода
  RELAY		= 6,			// Выходные реле, сопоставленные физическим входам
  INPUT_LIST	= 7,			// Запросы сбора данных
  RECEIPT_LIST	= 8,			// Запросы квитирования
  UNSET_LIST	= 9			// Запросы сброса
 };
};
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#endif //__DATA_TYPES_H
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
