#include "I2C.h"

void read_i2c_bytes(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t start_address, uint8_t *data, uint16_t length)
{
    HAL_I2C_Master_Transmit(hi2c, (device_address << 1), &start_address, 1, HAL_MAX_DELAY);
    HAL_I2C_Master_Receive(hi2c, (device_address << 1) + 0x01, data, length, HAL_MAX_DELAY);
}

uint8_t read_i2c_reg_8(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address)
{
    uint8_t data = 0;
    read_i2c_bytes(hi2c, device_address, reg_address, &data, 1);
    return data;
}

uint16_t read_i2c_reg_16(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address)
{
    uint16_t data = 0;
    read_i2c_bytes(hi2c, device_address, reg_address, (uint8_t *)&data, 2);
    return data;
}

uint32_t read_i2c_reg_32(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address)
{
    uint32_t data = 0;
    read_i2c_bytes(hi2c, device_address, reg_address, (uint8_t *)&data, 4);
    return data;
}

float read_i2c_reg_float(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address)
{
    float data = 0.f;
    read_i2c_bytes(hi2c, device_address, reg_address, (uint8_t *)&data, 4);
    return data;
}

void write_i2c_bytes(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t *data, uint16_t length)
{
    HAL_I2C_Master_Transmit(hi2c, (device_address << 1), data, length, HAL_MAX_DELAY);
}

void write_i2c_reg_8(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address, uint8_t data)
{
    uint8_t d[2];

    d[0] = reg_address;
    d[1] = data;

    HAL_I2C_Master_Transmit(hi2c, (device_address << 1), d, 2, HAL_MAX_DELAY);
}

void write_i2c_reg_16(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address, uint16_t data)
{
    uint8_t d[3];

    d[0] = reg_address;
    d[1] = (data >> 8);
    d[2] = (data & 0xFF);

    HAL_I2C_Master_Transmit(hi2c, (device_address << 1), d, 3, HAL_MAX_DELAY);
}

void write_i2c_reg_32(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address, uint32_t data)
{
    uint8_t d[5];

    d[0] = reg_address;
    d[1] = (data >> 24);
    d[2] = (data >> 16);
    d[3] = (data >> 8);
    d[4] = (data & 0xFF);

    HAL_I2C_Master_Transmit(hi2c, (device_address << 1), d, 5, HAL_MAX_DELAY);
}

void write_i2c_reg_float(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address, float data)
{
    uint32_t float_as_int = *(uint32_t *)&data;
    write_i2c_reg_32(hi2c, device_address, reg_address, float_as_int);
}

void i2c_scan(I2C_HandleTypeDef *hi2c, uint8_t *addresses, uint8_t length)
{
    uint8_t found_devices = 0;
    for (uint8_t i = 1; i < 128; i++)
    {
        if (HAL_I2C_IsDeviceReady(hi2c, (i << 1), 1, HAL_MAX_DELAY) == HAL_OK)
        {
            if (found_devices < length)
            {
                addresses[found_devices++] = i;
            }
        }
    }
}