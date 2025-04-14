#include "rcc.h"
#include "stddef.h"

// Lookup table for GPIO base addresses and corresponding RCC enable bits
RCC_Error_t RCC_EnableGPIOClock(GPIO_TypeDef *pGPIOx)
{
    if (pGPIOx == GPIOA)
        RCC_GPIOA_ENABLE();
    else if (pGPIOx == GPIOB)
        RCC_GPIOB_ENABLE();
    else if (pGPIOx == GPIOC)
        RCC_GPIOC_ENABLE();
    else if (pGPIOx == GPIOD)
        RCC_GPIOD_ENABLE();
    else if (pGPIOx == GPIOE)
        RCC_GPIOE_ENABLE();
    else if (pGPIOx == GPIOF)
        RCC_GPIOF_ENABLE();
    else if (pGPIOx == GPIOG)
        RCC_GPIOG_ENABLE();
    else if (pGPIOx == GPIOH)
        RCC_GPIOH_ENABLE();
}

RCC_Error_t RCC_DisableGPIOClock(GPIO_TypeDef *pGPIOx)
{
    if (pGPIOx == GPIOA)
        RCC_GPIOA_DISABLE();
    else if (pGPIOx == GPIOB)
        RCC_GPIOB_DISABLE();
    else if (pGPIOx == GPIOC)
        RCC_GPIOC_DISABLE();
    else if (pGPIOx == GPIOD)
        RCC_GPIOD_DISABLE();
    else if (pGPIOx == GPIOE)
        RCC_GPIOE_DISABLE();
    else if (pGPIOx == GPIOF)
        RCC_GPIOF_DISABLE();
    else if (pGPIOx == GPIOG)
        RCC_GPIOG_DISABLE();
    else if (pGPIOx == GPIOH)
        RCC_GPIOH_DISABLE();
}

RCC_Error_t RCC_EnableUSARTClock(USART_TypeDef *pUSARTx)
{
    switch ((uint32_t)pUSARTx)
    {
    case (uint32_t)USART1:
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        break;
    case (uint32_t)USART2:
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
        break;
    case (uint32_t)USART3:
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
        break;
    case (uint32_t)UART4:
        RCC->APB1ENR |= RCC_APB1ENR_UART4EN;
        break;
    case (uint32_t)UART5:
        RCC->APB1ENR |= RCC_APB1ENR_UART5EN;
        break;
    default:
        return RCC_ERR; // Invalid USART
    }
    return RCC_OK;
}

RCC_Error_t RCC_DisableUSARTClock(USART_TypeDef *pUSARTx)
{
    switch ((uint32_t)pUSARTx)
    {
    case (uint32_t)USART1:
        RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN;
        break;
    case (uint32_t)USART2:
        RCC->APB1ENR &= ~RCC_APB1ENR_USART2EN;
        break;
    case (uint32_t)USART3:
        RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN;
        break;
    case (uint32_t)UART4:
        RCC->APB1ENR &= ~RCC_APB1ENR_UART4EN;
        break;
    case (uint32_t)UART5:
        RCC->APB1ENR &= ~RCC_APB1ENR_UART5EN;
        break;
    default:
        return RCC_ERR; // Invalid USART
    }
    return RCC_OK;
}
