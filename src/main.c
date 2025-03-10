
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"

#include "gpio.h"
#include "rcc.h"

void xSystemClockConfig();
void xGPIO_Config()
{
    RCC_EnableGPIOClock(GPIOA);

    GPIO_Handle_t UserLed1;
    UserLed1.pGPIOx = GPIOA;
    UserLed1.Pin = 5;
    UserLed1.Mode = GPIO_MODE_OUTPUT;
    UserLed1.Otype = GPIO_OTYPE_PUSHPULL;

    GPIO_Handle_t UserLed2;
    UserLed2.pGPIOx = GPIOA;
    UserLed2.Pin = 0;
    UserLed2.Mode = GPIO_MODE_OUTPUT;
    UserLed2.Otype = GPIO_OTYPE_PUSHPULL;

    if (GPIO_Init(&UserLed1) != GPIO_OK)
    {
        printf("GPIO_Init failed for Pin %d\n", UserLed1.Pin);
    }

    if (GPIO_Init(&UserLed2) != GPIO_OK)
    {
        printf("GPIO_Init failed for Pin %d\n", UserLed2.Pin);
    }
}

void xTaskLed1(void *pvParams)
{
    while (1)
    {
        GPIO_WritePin(GPIOA, 5, GPIO_STATE_HIGH);
        vTaskDelay(pdMS_TO_TICKS(500));

        GPIO_WritePin(GPIOA, 5, GPIO_STATE_LOW);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void xTaskLed2(void *pvParams)
{
    while (1)
    {
        GPIO_WritePin(GPIOA, 0, GPIO_STATE_HIGH);
        vTaskDelay(pdMS_TO_TICKS(250));

        GPIO_WritePin(GPIOA, 0, GPIO_STATE_LOW);
        vTaskDelay(pdMS_TO_TICKS(250));
    }
}

int main()
{
    // xSystemClockConfig();
    xGPIO_Config();

    xTaskCreate(xTaskLed1, "xTaskLed1", 256, NULL, 1, NULL);
    xTaskCreate(xTaskLed2, "xTaskLed2", 256, NULL, 1, NULL);

    vTaskStartScheduler();

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

void xSystemClockConfig()
{
    // Enabling PWR Clock
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    // Setting Power Scaling to 3
    PWR->CR |= PWR_CR_VOS;

    // Setting Flash Latency, Enabling Data and Instruction Cache and prefetching
    FLASH->ACR |= FLASH_ACR_DCEN | FLASH_ACR_ICEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

    RCC_Config_t Config;

    Config.ahb1_pre = RCC_AHBPRE_DIV1;
    Config.apb1_pre = RCC_APBPRE_DIV4;
    Config.apb2_pre = RCC_APBPRE_DIV2;
    Config.clk_src = RCC_CLK_SRC_PLLP;
    Config.hse_mode = RCC_HSE_NO_BYPASS;
    Config.pllm = 4;
    Config.plln = 180;
    Config.pllp = 0;
    Config.pllsrc = RCC_PLLSRC_HSE;
    RCC_SetSystemClock(&Config);
}