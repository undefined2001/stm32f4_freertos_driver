#ifndef IMU6050_H
#define IMU6050_H

/** Here Goes All the Configuration Macros */

/** IMU6050 Digital Low Pass Filter Configuration */
#define IMU6050_REG_CONFIG 0x1AU
#define IMU6050_DLPF_CFG_0 0x0U
#define IMU6050_DLPF_CFG_1 0x1U
#define IMU6050_DLPF_CFG_2 0x2U
#define IMU6050_DLPF_CFG_3 0x3U
#define IMU6050_DLPF_CFG_4 0x4U
#define IMU6050_DLPF_CFG_5 0x5U
#define IMU6050_DLPF_CFG_6 0x6U
#define IMU6050_DLPF_CFG_7 0x7U

/** Gyroscope Full Scale Range */
#define MPU6050_REG_GYRO_CONFIG 0x1BU
#define IMU6050_GFS_SEL_0 0x0U
#define IMU6050_GFS_SEL_1 0x1U
#define IMU6050_GFS_SEL_2 0x2U
#define IMU6050_GFS_SEL_3 0x3U

/** Accelerometer Full Scale Range */
#define MPU6050_REG_ACCEL_CONFIG 0x1CU
#define IMU6050_AFS_SEL_0 0x0U
#define IMU6050_AFS_SEL_1 0x1U
#define IMU6050_AFS_SEL_2 0x2U
#define IMU6050_AFS_SEL_3 0x3U

/** MPU6050 FIFO EN Registers Config*/
#define MPU6050_REG_FIFO_EN 0x23U
#define MPU6050_TEMP_FIFO_EN 0x80U
#define MPU6050_XG_FIFO_EN 0x40U
#define MPU6050_YG_FIFO_EN 0x20U
#define MPU6050_ZG_FIFO_EN 0x10U
#define MPU6050_ACCEL_FIFO_EN 0x08U
#define MPU6050_SLV2_FIFO_EN 0x04U
#define MPU6050_SLV1_FIFO_EN 0x02U
#define MPU6050_SLV0_FIFO_EN 0x01U


/** MPU6050 Data Out Reg */
#define MPU6050_REG_ACCEL_DATA_OUT 0x38U
#define MPU6050_REG_TEMP_DATA_OUT 0x41U
#define MPU6050_REG_GYRO_DATA_OUT 0x43U

/**MPU6050 Power Management Register 1 */
#define IMU6050_REG_PWR_MGMT_1 0x6BU

/**MPU6050 Power Management Register 2 */
#define IMU6050_REG_PWR_MGMT_1 0x6CU




#define MPU6050_REG_I2C_MST_CTRL 0x24U

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