#ifndef PCF8574_HPP
#define PCF8574_HPP

#include "../utility/i2c_device.hpp"
#include "pcf8574_config.hpp"
#include <optional>

namespace PCF8574 {

    struct PCF8574 {
    public:
        using I2CDevice = Utility::I2CDevice;

        PCF8574() noexcept = default;

        PCF8574(I2CDevice&& i2c_device, Config const& config) noexcept;

        PCF8574(PCF8574 const& other) = delete;
        PCF8574(PCF8574&& other) noexcept = default;

        PCF8574& operator=(PCF8574 const& other) = delete;
        PCF8574& operator=(PCF8574&& other) noexcept = default;

        ~PCF8574() noexcept;

    private:
        std::uint8_t receive_byte(std::uint8_t const reg_address) const noexcept;

        void transmit_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept;

        void initialize(Config const& config) noexcept;
        void deinitialize() noexcept;

        bool initialized_{false};

        I2CDevice i2c_device_{};
    };

}; // namespace PCF8574

#undef PACKED

#endif // PCF8574_HPP