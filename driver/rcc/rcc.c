#include "rcc.h"
#include "stddef.h"

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
