#include "rcc.h"
#include "stddef.h"

RCC_Error_t RCC_SetSystemClock(RCC_Config_t *pConfig)
{
    /**
     * *Configuring All the Bus Prescaler [AHB1PRESCALER< APB1PRESCALER, APB2PRESCALER]
     */
    RCC->CFGR &= ~RCC_CFGR_HPRE;    //*Clearing Bit Position for AHB Prescaler
    RCC->CFGR |= pConfig->apb1_pre; //* Setting the Value of AHB Prescaler

    RCC->CFGR &= ~RCC_CFGR_PPRE1;   //* Clearing Bit position for APB1 Prescaler
    RCC->CFGR |= pConfig->apb1_pre; //* Setting the value of APB1 Prescaler

    RCC->CFGR &= ~RCC_CFGR_PPRE2;   //* Clearing Bit position for APB2 Prescaler
    RCC->CFGR |= pConfig->apb2_pre; //* Setting the value of APB2 Prescaler

    if (pConfig->clk_src == RCC_CLK_SRC_HSI)
    {
        RCC->CR |= RCC_CR_HSION; //* Enable HSI As a Clock Source

        while (!(RCC->CR & RCC_CR_HSIRDY))
            ; //* Wait untill HSI is stable

        RCC->CFGR &= ~RCC_CFGR_SWS; //* Swtting all the bits to 0 so that HSI Works as a Clock Source

        RCC->CR &= ~RCC_CR_HSEON; //* Disable HSE Source
    }

    if (pConfig->clk_src == RCC_CLK_SRC_HSE)
    {
        /**
         * *Checking if HSE is Bypassed with external clock or not
         * *If Bypassed then set the HSEBYP = 1
         * *Else HSEBYP = 0
         */
        if (pConfig->hse_mode == RCC_HSE_BYPASS)
        {
            RCC->CR |= RCC_CR_HSEBYP;
        }
        else
        {
            RCC->CR &= ~RCC_CR_HSEBYP;
        }

        RCC->CR |= RCC_CR_HSEON; //* Turning on HSE Source

        while (!(RCC->CR & RCC_CR_HSERDY))
            ; //* Wait Until HSE is Stable and Ready to use

        RCC->CFGR |= RCC_CFGR_SW_0; //* Switching the source to HSE Clock Source
    }
    else if (pConfig->clk_src == RCC_CLK_SRC_PLLP)
    {
    }
    else
    {
        
    }
}

// Lookup table for GPIO base addresses and corresponding RCC enable bits
static const struct
{
    GPIO_TypeDef *gpio;
    uint32_t rcc_en_bit;
} gpio_clk_map[] = {
    {GPIOA, RCC_AHB1ENR_GPIOAEN},
    {GPIOB, RCC_AHB1ENR_GPIOBEN},
    {GPIOC, RCC_AHB1ENR_GPIOCEN},
    {GPIOD, RCC_AHB1ENR_GPIODEN},
    {GPIOE, RCC_AHB1ENR_GPIOEEN},
    {GPIOF, RCC_AHB1ENR_GPIOFEN},
    {GPIOG, RCC_AHB1ENR_GPIOGEN},
    {GPIOH, RCC_AHB1ENR_GPIOHEN}};

RCC_Error_t RCC_EnableGPIOClock(GPIO_TypeDef *pGPIOx)
{
    if (pGPIOx == NULL)
    {
        return RCC_ERR;
    }

    for (size_t i = 0; i < sizeof(gpio_clk_map) / sizeof(gpio_clk_map[0]); i++)
    {
        if (pGPIOx == gpio_clk_map[i].gpio)
        {
            RCC->AHB1ENR |= gpio_clk_map[i].rcc_en_bit;
            return RCC_OK;
        }
    }

    return RCC_ERR; // If pGPIOx doesn't match any known GPIO peripheral
}

RCC_Error_t RCC_DisableGPIOClock(GPIO_TypeDef *pGPIOx)
{
    if (pGPIOx == NULL)
    {
        return RCC_ERR;
    }

    for (size_t i = 0; i < sizeof(gpio_clk_map) / sizeof(gpio_clk_map[0]); i++)
    {
        if (pGPIOx == gpio_clk_map[i].gpio)
        {
            RCC->AHB1ENR &= ~gpio_clk_map[i].rcc_en_bit;
            return RCC_OK;
        }
    }

    return RCC_ERR; // If pGPIOx doesn't match any known GPIO peripheral
}
