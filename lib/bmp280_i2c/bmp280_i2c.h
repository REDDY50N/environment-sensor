#ifndef BMP280_I2C_H
#define BMP280_I2C_H

#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"

struct bmp280_calib_param;

void bmp280_init();
void bmp280_read_raw(int32_t* temp, int32_t* pressure);

void bmp280_reset();
int32_t bmp280_convert(int32_t temp, struct bmp280_calib_param* params);

int32_t bmp280_convert_temp(int32_t temp, struct bmp280_calib_param* params);

int32_t bmp280_convert_pressure(int32_t pressure, int32_t temp, struct bmp280_calib_param* params);

void bmp280_get_calib_params(struct bmp280_calib_param* params);

#endif //BMP280_I2C_H