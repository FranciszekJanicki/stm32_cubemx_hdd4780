#ifndef PCF8574_CONFIG_HPP
#define PCF8574_CONFIG_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace PCF8574 {

    constexpr auto DEVICE_ADDRESS = 0x27;

    struct CLEAR_DISPLAY {
        std::uint8_t reserved : 8 = 1;
    } PACKED;

    struct RETURN_HOME {
        std::uint8_t reserved : 8 = 2;
    } PACKED;

    struct ENTRY_MODE_SET {
        std::uint8_t reserved : 6 = 0b000001;
        std::uint8_t id : 1;
        std::uint8_t s : 1;
    } PACKED;

    struct DISPLAY_ON_OFF_CONTROL {
        std::uint8_t reserved : 5 = 0b00001;
        std::uint8_t d : 1;
        std::uint8_t c : 1;
        std::uint8_t b : 1;
    } PACKED;

    struct CURSOR_OR_DISPLAY_SHIFT {
        std::uint8_t reserved : 4 = 0b0001;
        std::uint8_t sc : 1;
        std::uint8_t rl : 1;
        std::uint8_t : 2;
    } PACKED;

    struct Config {};

}; // namespace PCF8574

#undef PACKED

#endif // PCF8574_CONFIG_HPP