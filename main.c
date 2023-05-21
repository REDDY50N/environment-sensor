// Standard Libs
#include <stdio.h> // for some simple printf debugging
//#include <cstdio>  // C++ lib
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// PICO SDK Libs
#include "pico/stdlib.h"    // ==> need to include pico sdk path in CMake file
#include "hardware/gpio.h"
#include "hardware/i2c.h"   // BME280

// External HW Libs
#include "lib/bmp280_i2c/bmp280_i2c.h"      
//#include "lib/bme280/bme280.h"                  // Bosch-API: https://github.com/BoschSensortec/BME280_driver


// ==============================================
// CONSTANTS
// ==============================================
const uint LED_PIN = PICO_DEFAULT_LED_PIN; // Pin25

// ==============================================
// FUNCTIONS
// ==============================================
void blink() 
{
    //! LED Blink
    printf("Blinking!\r\n");
    sleep_ms(1000); // set processor in low power mode
    gpio_put(LED_PIN, true);
    sleep_ms(500);
    gpio_put(LED_PIN, false);
}





// ==============================================
// MAIN
// ==============================================


int main()
{
    // init UART for printf debugging
    stdio_init_all();

    // initialize LED Pin
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // DHT22
    //stdio_init_all();
    //gpio_init(DHT_PIN);


#if !defined(i2c_default) || !defined(PICO_DEFAULT_I2C_SDA_PIN) || !defined(PICO_DEFAULT_I2C_SCL_PIN)
    #warning i2c / bmp280_i2c example requires a board with I2C pins
        puts("Default I2C pins were not defined");
#else
    // useful information for picotool
    bi_decl(bi_2pins_with_func(PICO_DEFAULT_I2C_SDA_PIN, PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C));
    bi_decl(bi_program_description("BMP280 I2C example for the Raspberry Pi Pico"));

    printf("Hello, BMP280! Reading temperaure and pressure values from sensor...\n");

    // I2C is "open drain", pull ups to keep signal high when no data is being sent
    i2c_init(i2c_default, 100 * 1000);
    gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
    gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
    gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
    gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);

    // configure BMP280
    bmp280_init();

    // retrieve fixed compensation params
    struct bmp280_calib_param *params;
    params = (struct bmp280_calib_param*)malloc(sizeof(struct bmp280_calib_param));
    bmp280_get_calib_params(&params);

    int32_t raw_temperature;
    int32_t raw_pressure;

    sleep_ms(250); // sleep so that data polling and register update don't collide

    // endless
    while (true) 
    {


        bmp280_read_raw(&raw_temperature, &raw_pressure);
        int32_t temperature = bmp280_convert_temp(raw_temperature, &params);
        int32_t pressure = bmp280_convert_pressure(raw_pressure, raw_temperature, &params);
        printf("Pressure = %.3f kPa\n", pressure / 1000.f);
        printf("Temp. = %.2f C\n", temperature / 100.f);
        // poll every 500ms
        sleep_ms(500);
    
    }
    sleep_ms(2000);
#endif
    return 0;
}