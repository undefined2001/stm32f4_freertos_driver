
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"
#include "rcc.h"
#include "i2c.h"
#include "imu6050.h"

void imu_write_data(uint8_t address, uint8_t *data, uint8_t size)
{
    I2C_MasterSendData(I2C1, address, (uint8_t *)data, size);
}

void imu_read_data(uint8_t address, uint8_t *data, uint8_t size)
{
    I2C_MasterReceiveData(I2C1, address, data, size);
}

float gyro_data[3];
float accel_data[3];
imu6050 imu;

void xGPIO_Config()
{
    RCC_EnableGPIOClock(GPIOB);
    GPIOConfig_t Config;
    Config.pPort = GPIOB;
    Config.Pin = GPIO_PIN8 | GPIO_PIN9;
    Config.Mode = GPIO_MODE_ALTFN;
    Config.Otype = GPIO_OTYPE_OD;
    Config.Pupd = GPIO_PUPD_PULLUP;
    Config.Ospeed = GPIO_OSPEED_HIGH;
    Config.AFn = 4;
    GPIO_Init(&Config);
}

int main()
{
    xGPIO_Config();
    I2C_Init();

    imu_init(&imu, 0x68, imu_read_data, imu_write_data);

    uint8_t reg = 0x75;
    uint8_t res = imu_whoami(&imu);
    if (res == 0x70)
    {
        imu_read_gyro(&imu, gyro_data);
        imu_read_accel(&imu, accel_data);
    }

    volatile int a = 0;

    while (1)
    {
    }

    return 0;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("Stack overflow detected in task: %s\n", pcTaskName);
    while (1)
        ; // Halt execution
}
