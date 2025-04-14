#ifndef __UART_H__
#define __UART_H__
#include "stm32f446xx.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        USART_TypeDef *pUARTx;
        uint32_t Direcrtion;
        uint32_t Parity;
        uint32_t ParityCtrl;
        uint32_t DataFrameFormat;

    } UART_Handle_t;

    void UART_Init(UART_Handle_t *pHandle);
    void UART_SendBuffer();
    void UART_RecvBuffer();
    void UART_SendBufferDMA();
    void UART_RecvBufferDMA();
    void UART_SendBufferIT();
    void UART_RecvBufferIT();

#ifdef __cplusplus
}
#endif

#endif