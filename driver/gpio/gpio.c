#include "gpio.h"

/**
 * @brief  Initializes the GPIO pin with the given configuration.
 *
 * @param  pGPIOHandle Pointer to GPIO handle structure containing configuration.
 * @retval GPIO_Error_t Error code indicating success or failure.
 */
GPIO_Error_t GPIO_Init(GPIO_Handle_t *pGPIOHandle)
{
    // Validate input parameters
    if (pGPIOHandle->Mode > GPIO_MODE_MAX_VAL)
    {
        return GPIO_ERR_INVALID_MODE;
    }
    if (pGPIOHandle->Pin > 15) // No need to check < 0 since it's an unsigned value
    {
        return GPIO_ERR_INVALID_PIN;
    }

    if (pGPIOHandle->Otype > GPIO_OTYPE_MAX_VAL)
    {
        return GPIO_ERR_INVALID_OTYPE;
    }

    /**
     * GPIO Mode Configuration
     * ------------------------
     * Each GPIO pin has 2 bits in the MODER register:
     * - 00: Input Mode
     * - 01: Output Mode
     * - 10: Alternate Function Mode
     * - 11: Analog Mode
     *
     * Example:
     * For Pin 5, MODER bits are located at positions [11:10] → (5 * 2).
     */
    if (pGPIOHandle->Mode <= GPIO_MODE_ANALOG)
    {
        // Clear mode bits to avoid unexpected behavior due to garbage values
        pGPIOHandle->pGPIOx->MODER &= ~(0x3U << (pGPIOHandle->Pin * 2U));

        // Set the mode value for the given pin
        pGPIOHandle->pGPIOx->MODER |= (pGPIOHandle->Mode << (pGPIOHandle->Pin * 2));
    }
    else
    {
        // Configure Interrupt Here
    }

    /**
     * GPIO Output Type Configuration
     * ------------------------------
     * Each GPIO pin has 1 bit in the OTYPER register:
     * - 0: Output Push-Pull
     * - 1: Output Open-Drain
     */
    // Clear Otype Bit to avoid unexpected behavior due to garbage values
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1U << pGPIOHandle->Pin);

    // Setting Otype Value for the given pin
    pGPIOHandle->pGPIOx->OTYPER |= (pGPIOHandle->Otype << pGPIOHandle->Pin);

    /**
     * GPIO Pull-up/Pull-down Configuration
     * ------------------------------------
     * Each GPIO pin has 2 bits in the PUPDR register:
     * - 00: No pull-up, no pull-down
     * - 01: Pull-up
     * - 10: Pull-down
     * - 11: Reserved
     */

    // Clearing Bits for PUPDR to avoid unexpected behavious due to garbage values
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3U << (pGPIOHandle->Pin * 2));

    // Setting Pullup/down
    pGPIOHandle->pGPIOx->PUPDR |= ~(pGPIOHandle->PuPd << (pGPIOHandle->Pin * 2));

    return GPIO_OK; // Return success
}

GPIO_Error_t GPIO_WritePin(GPIO_TypeDef *pGPIOx, uint32_t Pin, uint32_t value)
{
    if (value == GPIO_STATE_HIGH)
    {
        pGPIOx->BSRR |= 0x1U << Pin;
    }
    else
    {
        pGPIOx->BSRR |= 0x1U << (Pin + 16U);
    }
    return GPIO_OK;
}