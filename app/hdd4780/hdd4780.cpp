#include "hdd4780.hpp"
#include "utility.hpp"

namespace HDD4780 {

    HDD4780::HDD4780(I2CDevice&& i2c_device, Config const& config) noexcept :
        i2c_device_{std::forward<I2CDevice>(i2c_device)}
    {
        this->initialize(config);
    }

    HDD4780::~HDD4780() noexcept
    {
        this->deinitialize();
    }

    std::uint8_t HDD4780::receive_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->i2c_device_.receive_byte();
    }

    void HDD4780::transmit_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->i2c_device_.transmit_byte(byte);
    }

    void HDD4780::initialize(Config const& config) noexcept
    {
        this->initialized_ = true;
    }

    void HDD4780::deinitialize() noexcept
    {
        this->initialized_ = false;
    }

}; // namespace HDD4780