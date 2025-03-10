#include "rcc.h"
#include "stddef.h"

static void RCC_HSI_Init()
{
    RCC->CR |= RCC_CR_HSION; //* Enable HSI As a Clock Source

    while (!(RCC->CR & RCC_CR_HSIRDY))
        ; //* Wait untill HSI is stable

    RCC->CFGR &= ~RCC_CFGR_SWS; //* Swtting all the bits to 0 so that HSI Works as a Clock Source

    RCC->CR &= ~RCC_CR_HSEON; //* Disable HSE Source
}

static void RCC_HSE_Init(RCC_Config_t *pConfig)
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
}

static void RCC_PLL_Init(RCC_Config_t *pConfig)
{
    if (pConfig->pllsrc == RCC_PLLSRC_HSE)
    {
        RCC_HSE_Init(pConfig);
    }
    else
    {
        RCC_HSI_Init();
    }
    uint32_t DummyReg = 0;
    /**
     ** @brief : Setting the PLL Source
     */

    DummyReg |= pConfig->pllsrc << RCC_PLLCFGR_PLLSRC_Pos;

    /**
     ** @brief: PLLM is a Divider for the PLLCLK which is used to configure the Clock Frequency
     ** Here I am configuring the PLLM value which consists [5:0] 6bits from 0 to 5
     */
    DummyReg |= pConfig->pllm << RCC_PLLCFGR_PLLM_Pos;

    /**
     ** @brief: PLLN is also a Clock divider which gives us the freedom of configuring PLL Clock Further and more precisely
     ** Here PLLM takes [14:6] 9 bits
     */
    DummyReg |= pConfig->plln << RCC_PLLCFGR_PLLN_Pos;

    /**
     ** @brief: PLLP is also a Clock divider which gives us the freedom of configuring PLL Clock Further and more precisely
     ** Here PLLM takes [17:16] 2 bits
     */
    DummyReg |= pConfig->pllp << RCC_PLLCFGR_PLLP_Pos;

    /**
     ** @brief: Writing All the values into the PLL configuration Register
     */
    RCC->PLLCFGR = DummyReg;

    /**
     ** @brief: Here We Have to Turn PLL On
     */

    RCC->CR |= RCC_CR_PLLON;

    /**
     ** @brief : using a busy while loop to hold until PLL is stablize
     */
    while (!(RCC->CR & RCC_CR_PLLRDY))
        ;
    /**
     ** @brief: Chanign the System Clock Source MUX to use PLL as Clock Source
     */

    RCC->CFGR |= RCC_CFGR_SW_PLL;
}

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
        RCC_HSI_Init();
    }

    if (pConfig->clk_src == RCC_CLK_SRC_HSE)
    {
        RCC_HSE_Init(pConfig);
        RCC->CFGR |= RCC_CFGR_SW_0; //* Switching the source to HSE Clock Source
    }
    else
    {
        RCC_PLL_Init(pConfig);
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
