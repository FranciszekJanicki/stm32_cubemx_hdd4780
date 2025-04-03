#ifndef HDD4780_CONFIG_HPP
#define HDD4780_CONFIG_HPP

#include "hdd4780_commands.hpp"
#include "i2c_device.hpp"
#include <cstdint>

namespace HDD4780 {

    using I2CDevice = STM32_Utility::I2CDevice;

    auto constexpr DEVICE_ADDRESS = 0x27;

    struct Config {};

    struct Font {
        std::uint8_t char_height;
        std::uint8_t char_width;
        std::uint8_t* font_bitmap;
    };

    constexpr auto LINE_WIDTH = 16U * 5U;
    constexpr auto LINE_HEIGHT = 8U;
    constexpr auto NUM_LINES = 2U;

}; // namespace HDD4780

#endif // HDD4780_CONFIG_HPP