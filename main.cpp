// Standard Libs
#include <stdio.h> // for some simple printf debugging
#include <cstdio>  // C++ lib
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// PICO SDK Libs
#include "pico/stdlib.h"    // ==> need to include pico sdk path in CMake file
#include "hardware/gpio.h"
#include "hardware/i2c.h"   // BME280

// External HW Libs
#include "lib/pico-onewire/api/one_wire.h"      
#include "lib/bme280/bme280.h"                  // Bosch-API: https://github.com/BoschSensortec/BME280_driver


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
// BME280
// ==============================================

// Prototypes
void print_sensor_data(struct bme280_data *comp_data);


struct bme280_  dev dev;
int8_t rslt = BME280_OK;
uint8_t dev_addr = BME280_I2C_ADDR_PRIM;

 void user_delay_ms(uint32_t period, void *intf_ptr)
{
    /*
     * Return control or wait,
     * for a period amount of milliseconds
     */
}


int8_t user_i2c_read(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter intf_ptr can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Stop       | -                   |
     * | Start      | -                   |
     * | Read       | (reg_data[0])       |
     * | Read       | (....)              |
     * | Read       | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

    return rslt;
}

int8_t user_i2c_write(uint8_t reg_addr, uint8_t *reg_data, uint32_t len, void *intf_ptr)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

    /*
     * The parameter intf_ptr can be used as a variable to store the I2C address of the device
     */

    /*
     * Data on the bus should be like
     * |------------+---------------------|
     * | I2C action | Data                |
     * |------------+---------------------|
     * | Start      | -                   |
     * | Write      | (reg_addr)          |
     * | Write      | (reg_data[0])       |
     * | Write      | (....)              |
     * | Write      | (reg_data[len - 1]) |
     * | Stop       | -                   |
     * |------------+---------------------|
     */

    return rslt;
}

int8_t stream_sensor_data_normal_mode(struct bme280_dev *dev)
{
	int8_t rslt;
	uint8_t settings_sel;
	struct bme280_data comp_data;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	printf("Temperature, Pressure, Humidity\r\n");
	while (1) 
    {
		/* Delay while the sensor completes a measurement */
		dev->delay_us(70, dev->intf_ptr);
		rslt = bme280_get_sensor_data(BME280_ALL, &comp_data, dev);
		print_sensor_data(&comp_data);
	}

	return rslt;
}

void print_sensor_data(struct bme280_data *comp_data)
{
#ifdef BME280_FLOAT_ENABLE
        printf("%0.2f, %0.2f, %0.2f\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#else
        printf("%ld, %ld, %ld\r\n",comp_data->temperature, comp_data->pressure, comp_data->humidity);
#endif
}




// ==============================================
// MAIN
// ==============================================


int main()
{


    
    // initialize LED Pin
    gpio_init(LED_PIN);
    gpio_set_dir(LED_PIN, GPIO_OUT);

    // DHT22
    //stdio_init_all();
    //gpio_init(DHT_PIN);

    stdio_init_all();
    One_wire one_wire(10); //GP10 (s. Pico board on back)
    one_wire.init();
    rom_address_t address{};

    // endless
    while (true) 
    {

        // BME280
        dev.intf_ptr = &dev_addr;
        dev.intf = BME280_I2C_INTF;
        dev.read = user_i2c_read;
        dev.write = user_i2c_write;
        dev.delay_us = user_delay_ms;
        rslt = bme280_init(&dev);

        
        // DS18B20
        one_wire.single_device_read_rom(address);
        printf("Device Address: %02x%02x%02x%02x%02x%02x%02x%02x\n", address.rom[0], address.rom[1], address.rom[2], address.rom[3], address.rom[4], address.rom[5], address.rom[6], address.rom[7]);
        one_wire.convert_temperature(address, true, false);
        printf("Temperature: %3.1foC\n", one_wire.temperature(address));
        sleep_ms(1000);
        blink();

        

        // DHT22
        /*
        dht_reading reading;
        read_from_dht(&reading);
        float fahrenheit = (reading.temp_celsius * 9 / 5) + 32;
        printf("Humidity = %.1f%%, Temperature = %.1fC (%.1fF)\n",
                reading.humidity, reading.temp_celsius, fahrenheit);
        */
    
    }
    sleep_ms(2000);
    return 0;
}