#ifndef IMU6050_H
#define IMU6050_H

#define IMU_REG_PWR_MGMT_1 0x6B
#define IMU_REG_GYRO_CONFIG 0x1B
#define IMU_REG_GYRO_DATA 0x43
#define IMU_REG_ACCEL_CONFIG 0x1C
#define IMU_REG_ACCEL_DATA 0x3B

#ifdef __cplusplus
extern "C"
{
#endif
#include "stm32f446xx.h"

    typedef void (*imu_func_t)(uint8_t address, uint8_t *data, uint8_t size);

    typedef struct
    {
        uint8_t address;
        imu_func_t read;
        imu_func_t write;
    } imu6050;

    void imu_init(imu6050 *dev, uint8_t address, imu_func_t _r, imu_func_t _w);
    uint8_t imu_whoami(imu6050 *dev);
    void imu_read_gyro(imu6050 *dev, float *data);
    void imu_read_accel(imu6050 *dev, float *data);

    // Your code here

#ifdef __cplusplus
}
#endif

#endif // IMU6050_H