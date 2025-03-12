#include "i2c_device.hpp"

namespace Utility {

    I2CDevice::I2CDevice(I2CHandle const i2c_bus, std::uint16_t const dev_address) noexcept :
        i2c_bus_{i2c_bus}, dev_address_{dev_address}
    {
        this->initialize();
    }

    void I2CDevice::transmit_dword(std::uint32_t const dword) const noexcept
    {
        this->transmit_dwords(std::array<std::uint32_t, 1UL>{dword});
    }

    void I2CDevice::transmit_word(std::uint16_t const word) const noexcept
    {
        this->transmit_words(std::array<std::uint16_t, 1UL>{word});
    }

    void I2CDevice::transmit_byte(std::uint8_t const byte) const noexcept
    {
        this->transmit_bytes(std::array<std::uint8_t, 1UL>{byte});
    }

    std::uint32_t I2CDevice::receive_dword() const noexcept
    {
        return this->receive_dwords<1UL>()[0];
    }

    std::uint16_t I2CDevice::receive_word() const noexcept
    {
        return this->receive_words<1UL>()[0];
    }

    std::uint8_t I2CDevice::receive_byte() const noexcept
    {
        return this->receive_bytes<1UL>()[0];
    }

    std::uint32_t I2CDevice::read_dword(std::uint8_t const reg_address) const noexcept
    {
        return this->read_dwords<1UL>(reg_address)[0];
    }

    std::uint16_t I2CDevice::read_word(std::uint8_t const reg_address) const noexcept
    {
        return this->read_words<1UL>(reg_address)[0];
    }

    std::uint8_t I2CDevice::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->read_bytes<1UL>(reg_address)[0];
    }

    void I2CDevice::write_dword(std::uint8_t const reg_address, std::uint32_t const dword) const noexcept
    {
        this->write_dwords(reg_address, std::array<std::uint32_t, 1UL>{dword});
    }

    void I2CDevice::write_word(std::uint8_t const reg_address, std::uint16_t const word) const noexcept
    {
        this->write_words(reg_address, std::array<std::uint16_t, 1UL>{word});
    }

    void I2CDevice::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->write_bytes(reg_address, std::array<std::uint8_t, 1UL>{byte});
    }

    std::uint16_t I2CDevice::dev_address() const noexcept
    {
        return this->dev_address_;
    }

    void I2CDevice::initialize() noexcept
    {
        if (this->i2c_bus_ != nullptr) {
            // if (HAL_I2C_IsDeviceReady(this->i2c_bus_, this->dev_address_ << 1, SCAN_RETRIES, TIMEOUT) == HAL_OK) {
            //     this->initialized_ = true;
            //     while (1) {
            //         printf("DUPA\n\r");
            //     }
            // }

            for (auto i = 0U; i < 128U; ++i) {
                auto error = HAL_I2C_IsDeviceReady(this->i2c_bus_, i << 1U, 10, 100);
                if (error = HAL_OK) {
                    std::printf("NICE BABY %d\n\r", i);
                }
            }
        }
    }

}; // namespace Utility
