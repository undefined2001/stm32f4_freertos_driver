#include "uart.h"

static void RCC_EnableUSARTClock(USART_TypeDef *pUSARTx) {
};

void UART_Init(UART_Handle_t *pHandle)
{
    // Enabling Clock for the UART peripheral
    RCC_EnableUSARTClock(pHandle->pUARTx);

    // Configuring Data Line. Example: TX Only, RX Only or Both TX and RX

    // Configuraing Baud Rate
}