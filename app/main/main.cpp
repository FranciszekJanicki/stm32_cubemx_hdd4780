#include "main.h"
#include "../utility/i2c_device.hpp"
#include "gpio.h"
#include "i2c.h"
#include "pcf8574_config.hpp"
#include "usart.h"
#include <cstdio>

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    auto i2c_device = Utility::I2CDevice{&hi2c1, PCF8574::DEVICE_ADDRESS};

    while (true) {
    }

    return 0;
}
