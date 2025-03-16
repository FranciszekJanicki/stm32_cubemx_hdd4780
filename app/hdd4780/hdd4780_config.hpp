#ifndef HDD4780_CONFIG_HPP
#define HDD4780_CONFIG_HPP

#include "hdd4780_commands.hpp"
#include <cstdint>

namespace HDD4780 {

    auto constexpr DEVICE_ADDRESS = 0x27;

    struct Config {};

}; // namespace HDD4780

#endif // HDD4780_CONFIG_HPP