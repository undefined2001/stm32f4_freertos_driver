#ifndef __I2C_H__
#define __I2C_H__

#define I2C_MODE_

#ifdef __cplusplus
extern "C"
{
#endif

#include "stm32f446xx.h"

    typedef struct
    {
        I2C_TypeDef *I2Cx;
        uint32_t ClockSpeed;
        uint32_t OwnAddress1;
        uint32_t AddressingMode;
        uint32_t DualAddressMode;
        uint32_t OwnAddress2;
        uint32_t GeneralCallMode;
        uint32_t NoStretchMode;
    } I2C_Config_t;

    void I2C_Init();
    // void I2C_Init(I2C_Config_t *I2C_Config);
    void I2C_MasterSendData(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t *pTxBuffer, uint32_t Len);
    void I2C_MasterReceiveData(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t *pRxBuffer, uint32_t Len);

#ifdef __cplusplus
}
#endif

#endif // I2C_H