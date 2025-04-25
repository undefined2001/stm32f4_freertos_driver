#include "imu6050.h"

void imu_init(imu6050 *dev, uint8_t address, imu_func_t _r, imu_func_t _w)
{
    dev->address = address;
    dev->read = _r;
    dev->write = _w;

    uint8_t pwr_commands[] = {IMU_REG_PWR_MGMT_1, 0x00};
    dev->write(address, pwr_commands, sizeof(pwr_commands));

    uint8_t gyro_config_commands[] = {IMU_REG_GYRO_CONFIG, 0x18};
    dev->write(address, gyro_config_commands, sizeof(gyro_config_commands));

    uint8_t accel_config_commands[] = {IMU_REG_ACCEL_CONFIG, 0x18};
    dev->write(address, gyro_config_commands, sizeof(accel_config_commands));
}

uint8_t imu_whoami(imu6050 *dev)
{
    uint8_t res, reg = 0x75;
    dev->write(dev->address, &reg, 1);
    dev->read(dev->address, &res, 1);
    return res;
}

void imu_read_gyro(imu6050 *dev, float *data)
{
    uint8_t raw_data[6] = {0};
    uint8_t reg = IMU_REG_GYRO_DATA;
    dev->write(dev->address, &reg, 1);
    dev->read(dev->address, raw_data, 6);

    int16_t raw_gyro_x = (int16_t)((raw_data[0] << 8) | raw_data[1]);
    int16_t raw_gyro_y = (int16_t)((raw_data[2] << 8) | raw_data[3]);
    int16_t raw_gyro_z = (int16_t)((raw_data[4] << 8) | raw_data[5]);

    data[0] = raw_gyro_x / 16.4f;
    data[1] = raw_gyro_y / 16.4f;
    data[2] = raw_gyro_z / 16.4f;
}

void imu_read_accel(imu6050 *dev, float *data)
{
    uint8_t raw_data[6] = {0};
    uint8_t reg = IMU_REG_ACCEL_DATA;
    dev->write(dev->address, &reg, 1);
    dev->read(dev->address, raw_data, 6);

    int16_t raw_accel_x = (int16_t)((raw_data[0] << 8) | raw_data[1]);
    int16_t raw_accel_y = (int16_t)((raw_data[2] << 8) | raw_data[3]);
    int16_t raw_accel_z = (int16_t)((raw_data[4] << 8) | raw_data[5]);

    data[0] = raw_accel_x / 2048.0f;
    data[1] = raw_accel_y / 2048.0f;
    data[2] = raw_accel_z / 2048.0f;
}