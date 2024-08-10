#ifndef _V_I2C_H
#define _V_I2C_H

// Use the following flags for compiling the right library, e.g.: -D STM32F1
#if defined(STM32F0)
#include "stm32f0xx_hal.h"
#elif defined(STM32F1)
#include "stm32f1xx_hal.h"
#elif defined(STM32F2)
#include "stm32f2xx_hal.h"
#elif defined(STM32F3)
#include "stm32f3xx_hal.h"
#elif defined(STM32F4)
#include "stm32f4xx_hal.h"
#elif defined(STM32F7)
#include "stm32f7xx_hal.h"
#else
#error "Unsupported STM32 microcontroller. Make sure you build with -D STM32F1 for example!"
#endif

#include <stdint.h>

#ifndef HAL_MAX_DELAY
#define HAL_MAX_DELAY 100
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    void read_i2c_bytes(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t start_address, uint8_t *data, uint16_t length);
    uint8_t read_i2c_reg_8(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address);
    uint16_t read_i2c_reg_16(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address);
    uint32_t read_i2c_reg_32(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address);
    float read_i2c_reg_float(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address);

    void write_i2c_bytes(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t start_address, uint8_t *data, uint16_t length);
    void write_i2c_reg_8(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address, uint8_t data);
    void write_i2c_reg_16(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address, uint16_t data);
    void write_i2c_reg_32(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address, uint32_t data);
    void write_i2c_reg_float(I2C_HandleTypeDef *hi2c, uint8_t device_address, uint8_t reg_address, float data);

#ifdef __cplusplus
}
#endif

#endif // _V_I2C_H
