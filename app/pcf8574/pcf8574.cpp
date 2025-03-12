#include "pcf8574.hpp"
#include "utility.hpp"

namespace PCF8574 {

    PCF8574::PCF8574(I2CDevice&& i2c_device, Config const& config) noexcept :
        i2c_device_{std::forward<I2CDevice>(i2c_device)}
    {
        this->initialize(config);
    }

    PCF8574::~PCF8574() noexcept
    {
        this->deinitialize();
    }

    std::uint8_t PCF8574::receive_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.receive_byte();
    }

    void PCF8574::transmit_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->i2c_device_.transmit_byte(byte);
    }

    void PCF8574::initialize(Config const& config) noexcept
    {
        this->initialized_ = true;
    }

    void PCF8574::deinitialize() noexcept
    {
        this->initialized_ = false;
    }

}; // namespace PCF8574