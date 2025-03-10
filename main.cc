#include "stm32f446xx.h"
#include "bme68x.h"
#include "timer.h"

#define MPU_ADDR 0x77
#define MPU_WHOAMI_REG 0xD0

struct bme68x_dev device;
struct bme68x_conf conf;
struct bme68x_heatr_conf heatr_conf;
struct bme68x_data data;
uint8_t n_fields;

/*
typedef BME68X_INTF_RET_TYPE (*bme68x_read_fptr_t)(uint8_t reg_addr, uint8_t *reg_data, uint32_t length,
                                                   void *intf_ptr);
*/

int8_t bme_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr);
int8_t bme_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr);
void bme_init();
void bme_measure_temp();

void i2c_init();
void i2c_gpio_init();
void i2c_gpio_init();
void i2c_send_byte(uint8_t data);
uint8_t i2c_recv_byte();
void i2c_send_addr(uint8_t addr, uint8_t rw);
void i2c_start();
void i2c_stop();

uint8_t res;

int main()
{
    TimerInit();
    i2c_gpio_init();
    i2c_init();
    // i2c_start();
    // i2c_send_addr(MPU_ADDR, 0x0U);
    // i2c_send_byte(MPU_WHOAMI_REG);
    // i2c_stop();

    // i2c_start();
    // i2c_send_addr(MPU_ADDR, 0x1U);
    // res = i2c_recv_byte();
    // i2c_stop();
    bme_init();

    DelayMS(1000);

    while (true)
    {
        bme_measure_temp();
        DelayMS(1000);
    }

    return 0;
}
void i2c_gpio_init()
{
    /* Enable GPIOB clock */
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

    /* Configure PB8 (SCL) and PB9 (SDA) as Alternate Function */
    GPIOB->MODER &= ~(GPIO_MODER_MODE8 | GPIO_MODER_MODE9);
    GPIOB->MODER |= (GPIO_MODER_MODE8_1 | GPIO_MODER_MODE9_1); /* AF mode */

    /* Enable pull-up resistors for PB8 and PB9 */
    GPIOB->PUPDR &= ~(GPIO_PUPDR_PUPD8 | GPIO_PUPDR_PUPD9);
    GPIOB->PUPDR |= (GPIO_PUPDR_PUPD8_0 | GPIO_PUPDR_PUPD9_0); /* Pull-up */

    /* Set PB8 and PB9 as open-drain */
    GPIOB->OTYPER |= (GPIO_OTYPER_OT8 | GPIO_OTYPER_OT9);

    /* Set high speed for PB8 and PB9 */
    GPIOB->OSPEEDR |= (GPIO_OSPEEDER_OSPEEDR8 | GPIO_OSPEEDER_OSPEEDR9);

    /* Set PB8 and PB9 to AF4 (I2C1) */
    GPIOB->AFR[1] &= ~((0xF << GPIO_AFRH_AFSEL8_Pos) | (0xF << GPIO_AFRH_AFSEL9_Pos));
    GPIOB->AFR[1] |= ((0x4 << GPIO_AFRH_AFSEL8_Pos) | (0x4 << GPIO_AFRH_AFSEL9_Pos));
}

void i2c_init()
{
    RCC->APB1ENR |= RCC_APB1ENR_I2C1EN; /*Enabling I2C clock*/

    /*Reseting I2C peripheral*/
    I2C1->CR1 |= I2C_CR1_SWRST;
    I2C1->CR1 &= ~I2C_CR1_SWRST;

    /*Disabling I2C Peripheral*/
    I2C1->CR1 &= ~I2C_CR1_PE;

    /*Setting the Bus Frequency*/
    I2C1->CR2 |= 16U << I2C_CR2_FREQ_Pos;

    /*Setting CCR value*/
    I2C1->CCR = 80U;

    /*Setting TRISE*/
    I2C1->TRISE = 17;

    /*Enabling I2C Peripheral*/
    I2C1->CR1 |= I2C_CR1_PE;

    /*Enabling ACK*/
    I2C1->CR1 |= I2C_CR1_ACK;
}

void i2c_start()
{
    /* Generate START condition */
    I2C1->CR1 |= I2C_CR1_START;

    /* Wait until START condition is generated */
    while (!(I2C1->SR1 & I2C_SR1_SB))
        ;
}

void i2c_send_byte(uint8_t data)
{
    while (!(I2C1->SR1 & I2C_SR1_TXE))
        ;
    I2C1->DR = data;
}

void i2c_send_addr(uint8_t addr, uint8_t rw)
{
    /* Send the 7-bit address + Read/Write bit */
    I2C1->DR = (addr << 1U) | (rw & 0x1U);

    /* Wait until address is acknowledged */
    while (!(I2C1->SR1 & I2C_SR1_ADDR))
        ;

    /* Clear ADDR flag by reading SR1 and SR2 */
    (void)I2C1->SR1;
    (void)I2C1->SR2;
}

void i2c_stop()
{

    I2C1->CR1 |= I2C_CR1_STOP;
}

uint8_t i2c_recv_byte()
{
    I2C1->CR1 &= ~I2C_CR1_ACK;
    while (!(I2C1->SR1 & I2C_SR1_RXNE))
        ;
    return I2C1->DR;
}

void bme_delay_us(uint32_t period, void *intf_ptr)
{
    DelayUS(period);
}

void bme_init()
{
    device.intf = BME68X_I2C_INTF;
    device.amb_temp = 25;
    device.read = bme_read;
    device.write = bme_write;
    device.intf_ptr = static_cast<void *>(I2C1);
    device.delay_us = bme_delay_us;
    bme68x_init(&device);

    conf.filter = BME68X_FILTER_OFF;
    conf.odr = BME68X_ODR_NONE;
    conf.os_hum = BME68X_OS_16X;
    conf.os_pres = BME68X_OS_1X;
    conf.os_temp = BME68X_OS_2X;
    bme68x_set_conf(&conf, &device);

    heatr_conf.enable = BME68X_ENABLE;
    heatr_conf.heatr_temp = 300;
    heatr_conf.heatr_dur = 100;
    bme68x_set_heatr_conf(BME68X_FORCED_MODE, &heatr_conf, &device);
}

int8_t bme_write(uint8_t reg_addr, const uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
    i2c_start();
    i2c_send_addr(0x77, 0x0);
    i2c_send_byte(reg_addr);
    for (int i = 0; i < length; i++)
    {
        i2c_send_byte(*reg_data);
        reg_data++;
    }
    i2c_stop();
    return 0;
}
int8_t bme_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t length, void *intf_ptr)
{
    /* Step 1: Send Register Address */
    I2C1->CR1 |= I2C_CR1_ACK;
    i2c_start();
    i2c_send_addr(0x77, 0);  /* Write mode (0x77 << 1 | 0) */
    i2c_send_byte(reg_addr); /* Send the register address */

    /* Step 2: Restart & Read Data */
    i2c_start();
    i2c_send_addr(0x77, 1); /* Read mode (0x77 << 1 | 1) */

    /* Read Data */
    for (int i = 0; i < length; i++)
    {
        if (i == length - 1) /* Before reading last byte */
        {
            I2C1->CR1 &= ~I2C_CR1_ACK; /* Clear ACK (Send NACK on last byte) */
        }

        while (!(I2C1->SR1 & I2C_SR1_RXNE))
            ;                   /* Wait for data */
        reg_data[i] = I2C1->DR; /* Read data */
    }

    i2c_stop(); /* Generate STOP condition */
    return 0;
}

void bme_measure_temp()
{
    uint32_t del_period;

    bme68x_set_op_mode(BME68X_FORCED_MODE, &device);

    /* Calculate delay period in microseconds */
    del_period = bme68x_get_meas_dur(BME68X_FORCED_MODE, &conf, &device) + (heatr_conf.heatr_dur * 1000);
    device.delay_us(del_period, device.intf_ptr);

    /* Check if rslt == BME68X_OK, report or handle if otherwise */
    bme68x_get_data(BME68X_FORCED_MODE, &data, &n_fields, &device);
}