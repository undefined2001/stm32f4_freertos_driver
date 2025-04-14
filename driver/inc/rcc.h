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
 * @defgroup: Defining Macros for Enabling GPIO Peripheral Clock
 */

#define RCC_SYSCFG_ENABLE() (RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN)
#define RCC_GPIOA_ENABLE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN)
#define RCC_GPIOB_ENABLE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN)
#define RCC_GPIOC_ENABLE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN)
#define RCC_GPIOD_ENABLE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN)
#define RCC_GPIOE_ENABLE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN)
#define RCC_GPIOF_ENABLE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN)
#define RCC_GPIOG_ENABLE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN)
#define RCC_GPIOH_ENABLE() (RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN)

/**
 * @defgroup: Defining Macros for Enabling GPIO Peripheral Clock
 */
#define RCC_GPIOA_DISABLE() (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOAEN)
#define RCC_GPIOB_DISABLE() (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOBEN)
#define RCC_GPIOC_DISABLE() (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOCEN)
#define RCC_GPIOD_DISABLE() (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIODEN)
#define RCC_GPIOE_DISABLE() (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOEEN)
#define RCC_GPIOF_DISABLE() (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOFEN)
#define RCC_GPIOG_DISABLE() (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOGEN)
#define RCC_GPIOH_DISABLE() (RCC->AHB1ENR &= ~RCC_AHB1ENR_GPIOHEN)

/**
 * @defgroup: Defining Macros for Enabling USART Peripheral Clock
 */
#define RCC_USART1_ENABLE() (RCC->APB2ENR |= RCC_APB2ENR_USART1EN)
#define RCC_USART2_ENABLE() (RCC->APB2ENR |= RCC_APB2ENR_USART1EN)
#define RCC_USART3_ENABLE() (RCC->APB1ENR |= RCC_APB1ENR_USART3EN)
#define RCC_UART4_ENABLE() (RCC->APB1ENR |= RCC_APB1ENR_UART4EN)
#define RCC_UART5_ENABLE() (RCC->APB1ENR |= RCC_APB1ENR_UART5EN)

/**
 * @defgroup: Defining Macros for Disabling USART Peripheral Clock
 */
#define RCC_USART1_DISABLE() (RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN)
#define RCC_USART2_DISABLE() (RCC->APB2ENR &= ~RCC_APB2ENR_USART1EN)
#define RCC_USART3_DISABLE() (RCC->APB1ENR &= ~RCC_APB1ENR_USART3EN)
#define RCC_UART4_DISABLE() (RCC->APB1ENR &= ~RCC_APB1ENR_UART4EN)
#define RCC_UART5_DISABLE() (RCC->APB1ENR &= ~RCC_APB1ENR_UART5EN)

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
#define RCC_HSE_NO_BYPASS 0U
#define RCC_HSE_BYPASS 1U
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
#define RCC_AHBPRE_DIV1 0x0U
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
    } RCC_Error_t;

    typedef struct
    {
        uint32_t CLK_SRC;  // Clock source selection
        uint32_t HSE_MODE; // HSE mode configuration32
        uint32_t PLLM;     // PLL M factor
        uint32_t PLLN;     // PLL N factor
        uint32_t PLLP;     // PLL P factor
        uint32_t PLLQ;     // PLL Q factor
        uint32_t PLLR;     // PLL R factor
        uint32_t PLLSRC;   // PLL source selection

        uint32_t APB1PRE; // APB1 prescaler
        uint32_t APB2PRE; // APB2 prescaler
        uint32_t AHB1PRE; // AHB1 prescaler

    } RCC_Config_t;

    RCC_Error_t RCC_SetSystemClock(RCC_Config_t *pConfig);
    RCC_Error_t RCC_EnableGPIOClock(GPIO_TypeDef *pGPIOx);
    RCC_Error_t RCC_DisableGPIOClock(GPIO_TypeDef *pGPIOx);
    RCC_Error_t RCC_EnableUSARTClock(USART_TypeDef *pUSARTx);
    RCC_Error_t RCC_DisableUSARTClock(USART_TypeDef *pUSARTx);

    uint32_t RCC_GetSystemClockValue();
    uint32_t RCC_GetPCLK1Value();
    uint32_t RCC_GetPCLK2Value();

#ifdef __cplusplus
}
#endif

#endif
