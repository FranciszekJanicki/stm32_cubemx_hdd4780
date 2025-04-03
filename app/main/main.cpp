#include "main.h"
#include "font5x8.hpp"
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

    auto font = Font{.char_height = 8U, .char_width = 5U, .font_bitmap = Fonts::font_bitmap};

    auto hdd4780 = HDD4780::HDD4780{std::move(i2c_device), config, font};

    hdd4780.send_function_set_command(DL::BITS_8, N::LINES_1, F::DOTS_5x8);
    hdd4780.send_display_on_off_control_command(true, true, true);
    hdd4780.send_entry_mode_set_command(false, false);

    while (1) {
    }

    return 0;
}
