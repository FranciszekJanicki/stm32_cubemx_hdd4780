#include "spi_device.hpp"

namespace Utility {

    SPIDevice::SPIDevice(SPIHandle const spi_bus, GPIO const chip_select) noexcept :
        chip_select_{chip_select}, spi_bus_{spi_bus}
    {
        this->initialize();
    }

    void SPIDevice::transmit_dword(std::uint32_t const dword) const noexcept
    {
        this->transmit_dwords(std::array<std::uint32_t, 1UL>{dword});
    }

    void SPIDevice::transmit_word(std::uint16_t const word) const noexcept
    {
        this->transmit_words(std::array<std::uint16_t, 1UL>{word});
    }

    void SPIDevice::transmit_byte(std::uint8_t const byte) const noexcept
    {
        this->transmit_bytes(std::array<std::uint8_t, 1UL>{byte});
    }

    std::uint32_t SPIDevice::receive_dword() const noexcept
    {
        return this->receive_dwords<1UL>()[0];
    }

    std::uint16_t SPIDevice::receive_word() const noexcept
    {
        return this->receive_words<1UL>()[0];
    }

    std::uint8_t SPIDevice::receive_byte() const noexcept
    {
        return this->receive_bytes<1UL>()[0];
    }

    std::uint32_t SPIDevice::read_dword(std::uint8_t const reg_address) const noexcept
    {
        return this->read_dwords<1UL>(reg_address)[0];
    }

    std::uint16_t SPIDevice::read_word(std::uint8_t const reg_address) const noexcept
    {
        return this->read_words<1UL>(reg_address)[0];
    }

    std::uint8_t SPIDevice::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->read_bytes<1UL>(reg_address)[0];
    }

    void SPIDevice::write_dword(std::uint8_t const reg_address, std::uint32_t const dword) const noexcept
    {
        this->write_dwords(reg_address, std::array<std::uint32_t, 1UL>{dword});
    }

    void SPIDevice::write_word(std::uint8_t const reg_address, std::uint16_t const word) const noexcept
    {
        this->write_words(reg_address, std::array<std::uint16_t, 1UL>{word});
    }

    void SPIDevice::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->write_bytes(reg_address, std::array<std::uint8_t, 1UL>{byte});
    }

    std::uint8_t SPIDevice::reg_address_to_read_command(std::uint8_t const reg_address) noexcept
    {
        return reg_address & ~(1U << (std::bit_width(reg_address) - 1U));
    }

    std::uint8_t SPIDevice::reg_address_to_write_command(std::uint8_t const reg_address) noexcept
    {
        return reg_address | (1U << (std::bit_width(reg_address) - 1U));
    }

    void SPIDevice::initialize() noexcept
    {
        if (this->spi_bus_ != nullptr) {
            gpio_write_pin(this->chip_select_, GPIO_PIN_SET);
            this->initialized_ = true;
        }
    }

    void SPIDevice::deinitialize() noexcept
    {
        if (this->spi_bus_ != nullptr) {
            gpio_write_pin(this->chip_select_, GPIO_PIN_RESET);
            this->initialized_ = false;
        }
    }

}; // namespace Utility