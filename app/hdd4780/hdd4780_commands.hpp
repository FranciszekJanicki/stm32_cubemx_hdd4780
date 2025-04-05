#ifndef HDD4780_COMMANDS_HPP
#define HDD4780_COMMANDS_HPP

#include <cstdint>

#define PACKED __attribute__((__packed__))

namespace HDD4780 {

    struct CLEAR_DISPLAY {
        std::uint8_t reserved : 8 = 0b00000001;
    } PACKED;

    struct RETURN_HOME {
        std::uint8_t reserved : 8 = 0b00000010;
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

    struct FUNCTION_SET {
        std::uint8_t reserved : 3 = 0b001;
        std::uint8_t dl : 1;
        std::uint8_t n : 1;
        std::uint8_t f : 1;
        std::uint8_t : 2;
    } PACKED;

    struct SET_CGRAM_ADDRESS {
        std::uint8_t reserved : 2 = 0b01;
        std::uint8_t acg : 6;
    } PACKED;

    struct SET_DDRAM_ADDRESS {
        std::uint8_t reserved : 1 = 0b1;
        std::uint8_t add : 7;
    } PACKED;

    struct READ_BUSY_FLAG_AND_ADDRESS {
        std::uint8_t bf : 1;
        std::uint8_t ac : 7;
    } PACKED;

}; // namespace HDD4780

#undef PACKED

#endif // HDD4780_COMMANDS_HPP