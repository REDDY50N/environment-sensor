#include "pico/stdlib.h" // ==> need to include pico sdk path in CMake file

int main()
{
    const uint led_pin = 25;

    // initialize LED Pin
    gpio_init(led_pin);
    gpio_set_dir(led_pin, GPIO_OUT);

    while(true)
    {
        // LED Blink
        gpio_put(led_pin, true);
        sleep_ms(3000); // set processor in low power mode
        gpio_put(led_pin, false);
        sleep_ms(3000);
    }
}