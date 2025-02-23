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

/**
 * @defgroup Values for System Clock possible inputs
 * @{
 */
#define RCC_CLK_SRC_HSI 0U
#define RCC_CLK_SRC_HSE 1U
#define RCC_CLK_SRC_PLLP 2U
#define RCC_CLK_SRC_PLLR 3U
/**@}*/

/**
 * @defgroup Values for HSE Modes
 * @{
 */
#define RCC_HSE_BYPASS 0U
#define RCC_HSI_BYPASS 1U
/**@}*/

/**
 * @defgroup Values for PLL Source
 * @{
 */
#define RCC_PLLSRC_HSI 0U
#define RCC_PLLSRC_HSE 1U
/**@}*/

/**
 * @defgroup Values for APB1 & APB2 Prescaler
 * @{
 */
#define RCC_APBPRE_DIV2 0x4U
#define RCC_APBPRE_DIV4 0x5U
#define RCC_APBPRE_DIV8 0x6U
#define RCC_APBPRE_DIV16 0x7U
/**@}*/

/**
 * @defgroup Values for AHB1 Prescaler
 * @{
 */
#define RCC_AHBPRE_DIV2 0x8U
#define RCC_AHBPRE_DIV4 0x9U
#define RCC_AHBPRE_DIV8 0xAU
#define RCC_AHBPRE_DIV16 0xBU
#define RCC_AHBPRE_DIV64 0xCU
#define RCC_AHBPRE_DIV128 0xDU
#define RCC_AHBPRE_DIV256 0xEU
#define RCC_AHBPRE_DIV512 0xFU
/**@}*/

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

    
    typedef struct
    {
        uint8_t clk_src;  // Clock source selection
        uint8_t hse_mode; // HSE mode configuration

        uint8_t pllm;   // PLL M factor
        uint8_t plln;   // PLL N factor
        uint8_t pllp;   // PLL P factor
        uint8_t pllq;   // PLL Q factor
        uint8_t pllr;   // PLL R factor
        uint8_t pllsrc; // PLL source selection

        uint32_t apb1_pre; // APB1 prescaler
        uint32_t apb2_pre; // APB2 prescaler
        uint32_t ahb1_pre; // AHB1 prescaler

    } RCC_Config_t;

    RCC_Error_t RCC_SetSystemClock(RCC_Config_t *pConfig);
    RCC_Error_t RCC_EnableGPIOClock(GPIO_TypeDef *pGPIOx);
    RCC_Error_t RCC_DisableGPIOClock(GPIO_TypeDef *pGPIOx);

    uint32_t RCC_GetSystemClockValue();
    uint32_t RCC_GetPCLK1Value();
    uint32_t RCC_GetPCLK2Value();

#ifdef __cplusplus
}
#endif

#endif
