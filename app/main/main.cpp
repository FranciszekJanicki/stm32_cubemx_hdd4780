#include "main.h"
#include "gpio.h"
#include "hdd4780.hpp"
#include "hdd4780_config.hpp"
#include "i2c.h"
#include "i2c_device.hpp"
#include "usart.h"
#include <cstdio>

int main()
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART2_UART_Init();

    using namespace HDD4780;

    auto i2c_device = I2CDevice{&hi2c1, DEVICE_ADDRESS};
    i2c_device.bus_scan();

    auto config = Config{};

    auto hdd4780 = HDD4780::HDD4780{std::move(i2c_device), config};

    while (1) {
    }

    return 0;
}
