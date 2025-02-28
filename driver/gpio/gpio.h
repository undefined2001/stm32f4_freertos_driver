#ifndef __GPIO_H__
#define __GPIO_H__

#include <stdint.h>
#include "stm32f446xx.h"

/*------------------------GPIO Modes-------------------------------*/
#define GPIO_MODE_INPUT 0U
#define GPIO_MODE_OUTPUT 1U
#define GPIO_MODE_ALTFN 2U
#define GPIO_MODE_ANALOG 3U
#define GPIO_MODE_IT_FT 4U
#define GPIO_MODE_IT_RT 5U
#define GPIO_MODE_IT_FRT 6U

#define GPIO_MODE_MAX_VAL GPIO_MODE_IT_FRT

/*-----------------------GPIO Output Type---------------------------*/
#define GPIO_OTYPE_PUSHPULL 0x0U
#define GPIO_OTYPE_OPENDRAIN 0x1U
#define GPIO_OTYPE_MAX_VAL GPIO_OTYPE_OPENDRAIN

/*----------------------GPIO Pullup pulldown-------------------------*/
#define GPIO_PUPD_NONE 0x0U
#define GPIO_PUPD_PULLUP 0x1U
#define GPIO_PUPD_PULLDOWN 0x2U
#define GPIO_PUPD_MAX_VAL GPIO_PUPD_PULLDOWN

/*----------------------GPIO States------------------------*/
#define GPIO_STATE_LOW 0x0U
#define GPIO_STATE_HIGH 0x1U

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum
    {
        GPIO_ERR = -1,
        GPIO_OK = 0,           // No error
        GPIO_ERR_INVALID_PIN,  // Invalid pin number
        GPIO_ERR_NULL_PTR,     // Null pointer passed
        GPIO_ERR_INVALID_MODE, // Unsupported mode
        GPIO_ERR_INVALID_OTYPE,
        GPIO_ERR_INVALID_PUPD
    } GPIO_Error_t;

    typedef struct
    {
        uint32_t Pin;
        GPIO_TypeDef *pGPIOx;
        uint32_t Mode;
        uint32_t PuPd;
        uint32_t Otype;
        uint32_t Ospeed;
        uint32_t AFn;
    } GPIO_Handle_t;

    /**
     * @brief  Initializes the GPIO peripheral
     * @param  pGPIOHandle: Pointer to GPIO handle structure
     * @retval GPIO_Error_t: Returns an error code (GPIO_OK if successful)
     */
    GPIO_Error_t GPIO_Init(GPIO_Handle_t *pGPIOHandle);
    GPIO_Error_t GPIO_WritePin(GPIO_TypeDef *pGPIOx, uint32_t Pin, uint32_t value);
    GPIO_Error_t GPIO_WritePort(GPIO_TypeDef *pGPIOx, uint16_t value);
    uint32_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx, uint32_t Pin);
    uint32_t GPIO_ReadPort(GPIO_TypeDef *pGPIOx);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_H__ */
