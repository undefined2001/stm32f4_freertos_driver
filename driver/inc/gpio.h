#ifndef __GPIO_H__
#define __GPIO_H__

/**
 * @brief: Definitions for Some Utility Macros
 */
#define IS_PIN_VALID(pin) ()

#define CLEAR_REG_ONE_BITS(REG, POS) ((REG) &= (uint32_t)~(0x1U << (POS)))
#define CLEAR_REG_TWO_BITS(REG, POS) ((REG) &= (uint32_t)~(0x3U << (POS)))
#define CLEAR_REG_FOUR_BITS(REG, POS) ((REG) &= (uint32_t)~(0xFU << (POS)))
/**
 * @brief: Definitions for GPIO Pins
 */
#define GPIO_PIN0 0x0001
#define GPIO_PIN1 0x0002
#define GPIO_PIN2 0x0004
#define GPIO_PIN3 0x0008
#define GPIO_PIN4 0x0010
#define GPIO_PIN5 0x0020
#define GPIO_PIN6 0x0040
#define GPIO_PIN7 0x0080
#define GPIO_PIN8 0x0100
#define GPIO_PIN9 0x0200
#define GPIO_PIN10 0x0400
#define GPIO_PIN11 0x0800
#define GPIO_PIN12 0x1000
#define GPIO_PIN13 0x2000
#define GPIO_PIN14 0x4000
#define GPIO_PIN15 0x8000

/**
 * @brief: Definitions for GPIO Modes
 */
#define GPIO_MODE_INPUT 0x00U
#define GPIO_MODE_OUTPUT 0x01U
#define GPIO_MODE_ALTFN 0x02U
#define GPIO_MODE_ANALOG 0x03U
#define GPIO_MODE_IT 0x04U

/**
 * @brief: Definitions for GPIO OType
 */
#define GPIO_OTYPE_PP 0x00U
#define GPIO_OTYPE_OD 0x01U

/**
 * @brief: Definitions for GPIO Ospeed
 */
#define GPIO_OSPEED_LOW 0x00U
#define GPIO_OSPEED_MEDIUM 0x01U
#define GPIO_OSPEED_FAST 0x02U
#define GPIO_OSPEED_HIGH 0x03U

/**
 * @brief: Definitions for GPIO Ospeed
 */
#define GPIO_PUPD_NONE 0x00U
#define GPIO_PUPD_PULLUP 0x01U
#define GPIO_PUPD_PULLDOWN 0x02U

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f446xx.h"

    typedef struct GPIOConfig
    {
        GPIO_TypeDef *pPort;
        uint32_t Pin;
        uint32_t Mode;
        uint32_t Ospeed;
        uint32_t Pupd;
        uint32_t Otype;
        uint32_t AFn;
    } GPIOConfig_t;

    typedef enum Error
    {
        ERR = -1,
        OK = 0
    } Error_t;

    Error_t GPIO_Init(GPIOConfig_t *pGPIOx);
    Error_t GPIO_WritePin(GPIO_TypeDef *pGPIOx, uint32_t Pin, uint32_t State);
    Error_t GPIO_WritePort(GPIO_TypeDef *pGPIOx, uint16_t Value);
    uint32_t GPIO_ReadPin(GPIO_TypeDef *pGPIOx, uint32_t Pin);
    uint32_t GPIO_ReadPort(GPIO_TypeDef *pGPIOx);

#ifdef __cplusplus
}
#endif
#endif