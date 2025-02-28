
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"
#include "rcc.h"

void xGPIO_Config()
{
    RCC_EnableGPIOClock(GPIOA);
    RCC_EnableGPIOClock(GPIOC);

    GPIO_Handle_t UserBtn1;
    UserBtn1.pGPIOx = GPIOC;
    UserBtn1.Pin = 13;
    UserBtn1.Mode = GPIO_MODE_INPUT;
    UserBtn1.PuPd = GPIO_PUPD_PULLUP;

    GPIO_Handle_t UserLed1;
    UserLed1.pGPIOx = GPIOA;
    UserLed1.Pin = 5;
    UserLed1.Mode = GPIO_MODE_OUTPUT;
    UserLed1.Otype = GPIO_OTYPE_PUSHPULL;

    if (GPIO_Init(&UserLed1) != GPIO_OK)
    {
        printf("GPIO_Init failed for Pin %d\n", UserLed1.Pin);
    }

    if (GPIO_Init(&UserBtn1) != GPIO_OK)
    {
        printf("GPIO_Init failed for Pin %d\n", UserBtn1.Pin);
    }
}

int main()
{
    xGPIO_Config();

    uint32_t val = 0;

    while (1)
    {
        val = GPIO_ReadPin(GPIOC, 13);
        GPIO_WritePin(GPIOA, 5, !val);
    }

    return 0;
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    printf("Stack overflow detected in task: %s\n", pcTaskName);
    while (1)
        ; // Halt execution
}
