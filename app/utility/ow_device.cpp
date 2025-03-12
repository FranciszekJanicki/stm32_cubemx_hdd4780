#include "ow_device.hpp"

namespace Utility {

    OWDevice::OWDevice(TIMHandle const timer, GPIO const dev_pin, std::uint64_t const dev_address) noexcept :
        timer_{timer}, dev_pin_{dev_pin}, dev_address_{dev_address}
    {
        this->initialize();
    }

    OWDevice::~OWDevice() noexcept
    {
        this->deinitialize();
    }

    void OWDevice::transmit_dword(std::uint32_t const dword) const noexcept
    {
        this->transmit_dwords(std::array<std::uint32_t, 1UL>{dword});
    }

    void OWDevice::transmit_word(std::uint16_t const word) const noexcept
    {
        this->transmit_words(std::array<std::uint16_t, 1UL>{word});
    }

    void OWDevice::transmit_byte(std::uint8_t const byte) const noexcept
    {
        this->transmit_bytes(std::array<std::uint8_t, 1UL>{byte});
    }

    std::uint32_t OWDevice::receive_dword() const noexcept
    {
        return this->receive_dwords<1UL>()[0];
    }

    std::uint16_t OWDevice::receive_word() const noexcept
    {
        return this->receive_words<1UL>()[0];
    }

    std::uint8_t OWDevice::receive_byte() const noexcept
    {
        return this->receive_bytes<1UL>()[0];
    }

    std::uint32_t OWDevice::read_dword(std::uint8_t const reg_address) const noexcept
    {
        return this->read_dwords<1UL>(reg_address)[0];
    }

    std::uint16_t OWDevice::read_word(std::uint8_t const reg_address) const noexcept
    {
        return this->read_words<1UL>(reg_address)[0];
    }

    std::uint8_t OWDevice::read_byte(std::uint8_t const reg_address) const noexcept
    {
        return this->read_bytes<1UL>(reg_address)[0];
    }

    void OWDevice::write_dword(std::uint8_t const reg_address, std::uint32_t const dword) const noexcept
    {
        this->write_dwords(reg_address, std::array<std::uint32_t, 1UL>{dword});
    }

    void OWDevice::write_word(std::uint8_t const reg_address, std::uint16_t const word) const noexcept
    {
        this->write_words(reg_address, std::array<std::uint16_t, 1UL>{word});
    }

    void OWDevice::write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept
    {
        this->write_bytes(reg_address, std::array<std::uint8_t, 1UL>{byte});
    }

    std::uint64_t OWDevice::dev_address() const noexcept
    {
        return this->dev_address_;
    }

    void OWDevice::initialize() noexcept
    {
        if (this->timer_ != nullptr) {
            this->initialized_ = true;
        }
    }

    void OWDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            this->initialized_ = true;
        }
    }

}; // namespace Utility