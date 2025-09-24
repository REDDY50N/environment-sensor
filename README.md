# Gardening Environment Sensor

A Raspberry Pi Pico-based environment sensor for monitoring temperature, humidity, soil moisture, and air quality in your garden. Perfect for hobbyist gardeners and IoT enthusiasts looking to optimize plant care.

---

## Features
- **Temperature Monitoring**: Measure ambient temperature with [sensor model, e.g., DHT11].
- **Humidity Monitoring**: Track air humidity for optimal plant conditions.
- **Soil Moisture Sensing**: Monitor soil moisture to ensure proper irrigation.
- **Air Quality Detection**: Assess air quality for a healthy garden environment.
- Compact and low-cost solution using the Raspberry Pi Pico.
- Easy integration with IoT platforms for data logging (if applicable).


## Hardware Requirements
- Raspberry Pi Pico
- Sensors:
  - [e.g., DHT11/DHT22 for temperature and humidity]
  - [e.g., Capacitive Soil Moisture Sensor]
  - [e.g., MQ-135 for air quality]
- Breadboard and jumper wires
- USB cable for power and programming
- Optional: Display module (e.g., OLED for real-time data)


## Software Requirements
- Raspberry Pi Pico C/C++ SDK


## Setup Instructions
1. **Install the Raspberry Pi Pico SDK**:
   - Follow the official [Raspberry Pi Pico C/C++ SDK guide](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html).
   - Ensure `pico-sdk` is properly configured on your system.
2. **Clone the Repository**:
   ```bash
   git clone https://github.com/REDDY50N/environment-sensor.git
    ```

3. **Build**
   ```bash
   ./build.sh
    ```