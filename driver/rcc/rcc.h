/**
 * @file rcc.h
 * @author Asraful Islam Taj
 * @date 23 Feb 2025
 * @brief This Header file Contains all the public functions to configure RCC Peripherals
 *
 **Public Functions:
 **      - uint32_t RCC_GetPCLK1Value(void)
 **      - uint32_t RCC_GetPCLK2Value(void)
 **      - uint32_t RCC_GetPLLOutputClock(void)
 **      - RCC_Error_t  RCC_SetSystemClock(RCC_Config_t RCC_Config)
 **      - RCC_Error_t RCC_EnableGPIOClock(GPIO_TypeDef *pGPIOx)
 **      - RCC_Error_t RCC_DisableGPIOClock(PIO_TypeDef *pGPIOx)
 */

#ifndef __RCC_H__
#define __RCC_H__
#include "stm32f446xx.h"

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        RCC_ERR = -1,
        RCC_OK = 0,
        RCC_INVALID_PLLM_VAL,
        RCC_INVALID_PLLN_VAL,
        RCC_INVALID_PLLP_VAL,

    } RCC_Error_t;

    RCC_Error_t RCC_SetSystemClock();
    RCC_Error_t RCC_EnableGPIOClock(GPIO_TypeDef *pGPIOx);
    RCC_Error_t RCC_DisableGPIOClock(GPIO_TypeDef *pGPIOx);

    uint32_t RCC_GetSystemClockValue();
    uint32_t RCC_GetPCLK1Value();
    uint32_t RCC_GetPCLK2Value();

#ifdef __cplusplus
}
#endif

#endif
