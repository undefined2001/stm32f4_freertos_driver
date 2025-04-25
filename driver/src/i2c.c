#include "i2c.h"

void I2C_Init()
{
    // Enabling I2C clock
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;

    // Reseting the Peripheral
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    // Disabling the Peripheral for Configuration
    I2C1->CR1 &= ~I2C_CR1_PE;

    // Configuring the FREQ bits
    I2C1->CR2 &= ~I2C_CR2_FREQ;
    I2C1->CR2 |= 16;

    // Configuring the CCR value
    I2C1->CCR = 80;

    // Setting the Trise Value
    I2C1->TRISE = 17;

    // Enabling the Peripheral
    I2C1->CR1 |= I2C_CR1_PE;
}

void I2C_MasterSendData(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t *pTxBuffer, uint32_t Len)
{
    I2Cx->CR1 |= I2C_CR1_START;

    while (!(I2Cx->SR1 & I2C_SR1_SB))
        ;

    I2Cx->DR = (Address << 1); // Send Address with write bit

    while (!(I2Cx->SR1 & I2C_SR1_ADDR))
        ;

    (void)(I2Cx->SR1);
    (void)(I2Cx->SR2); // Clear ADDR flag

    while (Len--)
    {
        while (!(I2Cx->SR1 & I2C_SR1_TXE))
            ;
        I2Cx->DR = *pTxBuffer++;
    }

    while (!(I2Cx->SR1 & I2C_SR1_BTF))
        ; // Wait for Byte Transfer Finished

    I2Cx->CR1 |= I2C_CR1_STOP;
}

void I2C_MasterReceiveData(I2C_TypeDef *I2Cx, uint8_t Address, uint8_t *pRxBuffer, uint32_t Len)
{
    I2Cx->CR1 |= I2C_CR1_ACK;
    I2Cx->CR1 |= I2C_CR1_START;

    while (!(I2Cx->SR1 & I2C_SR1_SB))
        ;

    I2Cx->DR = (Address << 1) | 1; // Send Address with write bit

    while (!(I2Cx->SR1 & I2C_SR1_ADDR))
        ;

    (void)(I2Cx->SR1);
    (void)(I2Cx->SR2); // Clear ADDR flag

    while (Len)
    {
        if (Len == 1)
        {
            I2Cx->CR1 &= ~I2C_CR1_ACK;
        }
        while (!(I2Cx->SR1 & I2C_SR1_RXNE))
            ;

        *pRxBuffer++ = I2Cx->DR;
        Len--;
    }

    I2Cx->CR1 |= I2C_CR1_STOP;
}