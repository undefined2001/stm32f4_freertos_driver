#include "stm32f446xx.h"

int main()
{
    // Enable GPIOA clock
    RCC->AHB1ENR |= (1 << 0);

    // Configure PA5 as output
    GPIOA->MODER &= ~(3 << 10); // Clear bits 11:10
    GPIOA->MODER |= (1 << 10);  // Set bit 10 (Output mode)

    while (1)
    {
        GPIOA->ODR ^= (1 << 5); // Toggle PA5

        // Simple delay
        for (volatile int i = 0; i < 500000; i++);
    }

    return 0;
}

void vApplicationStackOverflowHook()
{
}
