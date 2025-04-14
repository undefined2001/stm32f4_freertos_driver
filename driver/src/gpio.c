#include "gpio.h"
#include "rcc.h"

Error_t GPIO_Init(GPIOConfig_t *pConfig)
{
    // Here goes the Validation of Date Fields
    uint32_t TempReg = 0;
    uint32_t AfrIndex = 0;

    for (int CurrentPin = 0; CurrentPin < 16; CurrentPin++)
    {
        if (pConfig->Pin & (uint32_t)(0x1U << CurrentPin))
        {

            TempReg = (uint32_t)pConfig->pPort->MODER;
            CLEAR_REG_TWO_BITS(TempReg, CurrentPin * 2);
            TempReg |= (uint32_t)(pConfig->Mode << (CurrentPin * 2));
            pConfig->pPort->MODER = TempReg;

            if (pConfig->Mode == GPIO_MODE_OUTPUT || pConfig->Mode == GPIO_MODE_ALTFN)
            {
                /**
                 * @brief: Configuring GPIO Output Speed
                 */
                TempReg = (uint32_t)pConfig->pPort->OSPEEDR;
                CLEAR_REG_TWO_BITS(TempReg, CurrentPin * 2);
                TempReg |= (uint32_t)(pConfig->Ospeed << (CurrentPin * 2));
                pConfig->pPort->OSPEEDR = TempReg;

                /**
                 * @brief: Configuring GPIO Output Type
                 */
                TempReg = (uint32_t)(pConfig->pPort->OTYPER);
                CLEAR_REG_ONE_BITS(TempReg, CurrentPin);
                TempReg |= (uint32_t)(pConfig->Otype << CurrentPin);
                pConfig->pPort->OTYPER = TempReg;
            }
            if (pConfig->Mode != GPIO_MODE_ANALOG)
            {
                /**
                 * @brief: Configuring GPIO Pull Up Down
                 */
                TempReg = pConfig->pPort->PUPDR;
                CLEAR_REG_TWO_BITS(TempReg, CurrentPin * 2);
                TempReg |= (uint32_t)(pConfig->Pupd << (CurrentPin * 2));
                pConfig->pPort->PUPDR = TempReg;
            }
            if (pConfig->Mode == GPIO_MODE_ALTFN)
            {
                /**
                 * @brief: Configuring GPIO Alternate Function
                 */
                AfrIndex = (CurrentPin >> 3);
                TempReg = pConfig->pPort->AFR[AfrIndex];
                CLEAR_REG_FOUR_BITS(TempReg, ((CurrentPin % 8) * 4U));
                TempReg |= pConfig->AFn << ((CurrentPin % 8) * 4U);
                pConfig->pPort->AFR[AfrIndex] = TempReg;
            }
        }
    }
}
