// Standard Libs
#include <stdio.h> // for some simple printf debugging
#include <cstdio>  // C++ lib

// Pico Libs
#include "pico/stdlib.h" // ==> need to include pico sdk path in CMake file


// Sensors Libs
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "lib/pico-onewire/api/one_wire.h"




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
        
        one_wire.single_device_read_rom(address);
        printf("Device Address: %02x%02x%02x%02x%02x%02x%02x%02x\n", address.rom[0], address.rom[1], address.rom[2], address.rom[3], address.rom[4], address.rom[5], address.rom[6], address.rom[7]);
        one_wire.convert_temperature(address, true, false);
        printf("Temperature: %3.1foC\n", one_wire.temperature(address));
        sleep_ms(1000);
    }


    // DHT22
    /*
    dht_reading reading;
    read_from_dht(&reading);
    float fahrenheit = (reading.temp_celsius * 9 / 5) + 32;
    printf("Humidity = %.1f%%, Temperature = %.1fC (%.1fF)\n",
            reading.humidity, reading.temp_celsius, fahrenheit);
    */

    sleep_ms(2000);
    return 0;
}