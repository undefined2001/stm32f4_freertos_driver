
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"
#include "rcc.h"

void xGPIO_Config()
{
    RCC_EnableGPIOClock(GPIOA);
    RCC_EnableGPIOClock(GPIOC);

    GPIOA->MODER |= 2 << 10;
    GPIOA->AFR[0] |= 0xF << 20;

    GPIOConfig_t Config;
    Config.Pin = GPIO_PIN5;
    Config.Mode = GPIO_MODE_ALTFN;
    Config.AFn = 5;
    Config.pPort = GPIOA;
    Config.Ospeed = GPIO_OSPEED_LOW;
    GPIO_Init(&Config);
}

void xLedBlinkTask(void *pvParams)
{
    while (1)
    {
        // GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_STATE_HIGH);
        GPIOA->ODR ^= 1 << 5;
        vTaskDelay(pdTICKS_TO_MS(1000));
        // for (int i = 0; i < 1000000; i++)
        //     ;

        // GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_STATE_LOW);
        // vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

int main()
{

    xGPIO_Config();

    uint32_t val = 0;

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
