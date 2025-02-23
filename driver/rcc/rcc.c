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
