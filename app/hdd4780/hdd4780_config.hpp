#ifndef HDD4780_CONFIG_HPP
#define HDD4780_CONFIG_HPP

#include "hdd4780_commands.hpp"
#include "i2c_device.hpp"
#include <cstdint>

namespace HDD4780 {

    using I2CDevice = STM32_Utility::I2CDevice;

    enum ID : std::uint8_t {
        INCREMENT = 0x01,
        DECREMENT = 0x00,
    };

    enum SC : std::uint8_t {
        DISPLAY_SHIFT = 0x01,
        CURSOR_MOVE = 0x00,
    };

    enum RL : std::uint8_t {
        SHIFT_RIGHT = 0x01,
        SHIFT_LEFT = 0x00,
    };

    enum DL : std::uint8_t {
        BITS_8 = 0x01,
        BITS_4 = 0x00,
    };

    enum N : std::uint8_t {
        LINES_2 = 0x01,
        LINES_1 = 0x00,
    };

    enum F : std::uint8_t {
        DOTS_5x10 = 0x01,
        DOTS_5x8 = 0x00,
    };

    enum BF : std::uint8_t {
        INTERNALLY_OPERATING = 0x01,
        INSTRUCTIONS_ACCEPTABLE = 0x00,
    };

    constexpr auto DEVICE_ADDRESS = 0x27;

    struct Config {};

    struct Font {
        std::uint8_t char_height;
        std::uint8_t char_width;
        std::uint8_t* font_bitmap;
    };

    constexpr auto LINE_WIDTH = 16U * 5U;
    constexpr auto LINE_HEIGHT = 8U;
    constexpr auto NUM_LINES = 2U;

    constexpr auto FRAME_BUF_SIZE = NUM_LINES * LINE_WIDTH * LINE_HEIGHT / 8U;

}; // namespace HDD4780

#endif // HDD4780_CONFIG_HPP