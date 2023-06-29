//-----------------------------------------------------------------------------------------------------
//  Sourse      : FileName.cpp
//  Created     : 01.06.2022
//  Author      : Alexandr Volvenkin
//  email       : aav-36@mail.ru
//  GitHub      : https://github.com/AlexandrVolvenkin
//-----------------------------------------------------------------------------------------------------
#include "Socket.h"

//-----------------------------------------------------------------------------------------------------
CUartSocket::CUartSocket()
{

}

//-----------------------------------------------------------------------------------------------------
CUartSocket::~CUartSocket()
{
    return xUart -> Read();
}

//-----------------------------------------------------------------------------------------------------
uint8_t UartSocket::Connect(uint32_t ulBaudRate,
                            uint8_t ucParity,
                            uint8_t ucDataBits,
                            uint8_t ucStopBit,
                            uint8_t *puiRxBuffer,
                            uint8_t *puiTxBuffer)
{
    xUart -> Init(m_uiBaudRate,
                  m_cParity,
                  m_uiDataBit,
                  m_uiStopBit,
                  puiRxBuffer,
                  puiTxBuffer);
}

//-----------------------------------------------------------------------------------------------------
uint8_t UartSocket::Select(void)
{
    return xUart -> ByteIsReceived();
}

//-----------------------------------------------------------------------------------------------------
uint8_t UartSocket::Recv(void)
{
    return xUart -> Read();
}

//-----------------------------------------------------------------------------------------------------
uint8_t UartSocket::Recv(uint8_t *puiDestination)
{
    return xUart -> Read(puiDestination);
}

//-----------------------------------------------------------------------------------------------------
uint8_t UartSocket::Recv(uint8_t *puiDestination, uint16_t uiLength)
{
    return xUart -> Read(puiDestination, uiLength);
}

//-----------------------------------------------------------------------------------------------------
uint8_t UartSocket::Send(uint8_t *puiSourse, uint16_t uiLength)
{
    return xUart -> Write(puiDestination, uiLength);
}
//-----------------------------------------------------------------------------------------------------





//-----------------------------------------------------------------------------------------------------
CSpiSocket::CSpiSocket()
{

}

//-----------------------------------------------------------------------------------------------------
CSpiSocket::~CSpiSocket()
{

}

//-----------------------------------------------------------------------------------------------------
uint8_t UartSocket::Select(void)
{
//    return xSpi -> ByteIsReceived();
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpiSocket::Recv(void)
{
    return xSpi -> Read();
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpiSocket::Recv(uint8_t *puiDestination)
{
    return xSpi -> Read(puiDestination);
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpiSocket::Recv(uint8_t *puiDestination, uint16_t uiLength)
{
    return xSpi -> Read(puiDestination, uiLength);
}

//-----------------------------------------------------------------------------------------------------
uint8_t CSpiSocket::Send(uint8_t *puiSourse, uint16_t uiLength)
{
    return xSpi -> Write(puiDestination, uiLength);
}
