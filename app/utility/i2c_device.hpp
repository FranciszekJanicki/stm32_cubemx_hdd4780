#ifndef I2C_DEVICE_HPP
#define I2C_DEVICE_HPP

#include "common.hpp"
#include "utility.hpp"

namespace Utility {

    struct I2CDevice {
    public:
        I2CDevice() noexcept = default;
        I2CDevice(I2CHandle const i2c_bus, std::uint16_t const dev_address) noexcept;

        I2CDevice(I2CDevice const& other) = delete;
        I2CDevice(I2CDevice&& other) noexcept = default;

        I2CDevice& operator=(I2CDevice const& other) = delete;
        I2CDevice& operator=(I2CDevice&& other) noexcept = default;

        ~I2CDevice() noexcept = default;

        template <std::size_t SIZE>
        void transmit_dwords(std::array<std::uint32_t, SIZE> const& dwords) const noexcept;
        void transmit_dword(std::uint32_t const dword) const noexcept;

        template <std::size_t SIZE>
        void transmit_words(std::array<std::uint16_t, SIZE> const& words) const noexcept;
        void transmit_word(std::uint16_t const word) const noexcept;

        template <std::size_t SIZE>
        void transmit_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept;
        void transmit_byte(std::uint8_t const byte) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint32_t, SIZE> receive_dwords() const noexcept;
        std::uint32_t receive_dword() const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint16_t, SIZE> receive_words() const noexcept;
        std::uint16_t receive_word() const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> receive_bytes() const noexcept;
        std::uint8_t receive_byte() const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint32_t, SIZE> read_dwords(std::uint8_t const reg_address) const noexcept;
        std::uint32_t read_dword(std::uint8_t const reg_address) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint16_t, SIZE> read_words(std::uint8_t const reg_address) const noexcept;
        std::uint16_t read_word(std::uint8_t const reg_address) const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> read_bytes(std::uint8_t const reg_address) const noexcept;
        std::uint8_t read_byte(std::uint8_t const reg_address) const noexcept;

        template <std::size_t SIZE>
        void write_dwords(std::uint8_t const reg_address, std::array<std::uint32_t, SIZE> const& dwords) const noexcept;
        void write_dword(std::uint8_t const reg_address, std::uint32_t const dword) const noexcept;

        template <std::size_t SIZE>
        void write_words(std::uint8_t const reg_address, std::array<std::uint16_t, SIZE> const& words) const noexcept;
        void write_word(std::uint8_t const reg_address, std::uint16_t const word) const noexcept;

        template <std::size_t SIZE>
        void write_bytes(std::uint8_t const reg_address, std::array<std::uint8_t, SIZE> const& bytes) const noexcept;
        void write_byte(std::uint8_t const reg_address, std::uint8_t const byte) const noexcept;

        std::uint16_t dev_address() const noexcept;

    private:
        static constexpr std::uint32_t TIMEOUT{100U};
        static constexpr std::uint32_t SCAN_RETRIES{10U};

        void initialize() noexcept;

        bool initialized_{false};

        I2CHandle i2c_bus_{nullptr};
        std::uint16_t dev_address_{};
    };

    template <std::size_t SIZE>
    void I2CDevice::transmit_dwords(std::array<std::uint32_t, SIZE> const& dwords) const noexcept
    {
        this->transmit_bytes(Utility::dwords_to_bytes(dwords));
    }

    template <std::size_t SIZE>
    void I2CDevice::transmit_words(std::array<std::uint16_t, SIZE> const& words) const noexcept
    {
        this->transmit_bytes(Utility::words_to_bytes(words));
    }

    template <std::size_t SIZE>
    void I2CDevice::transmit_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        std::array<std::uint8_t, SIZE> transmit{bytes};
        if (this->initialized_) {
            HAL_I2C_Master_Transmit(this->i2c_bus_, this->dev_address_ << 1, transmit.data(), transmit.size(), TIMEOUT);
        }
    }

    template <std::size_t SIZE>
    std::array<std::uint32_t, SIZE> I2CDevice::receive_dwords() const noexcept
    {
        return Utility::bytes_to_dwords(this->receive_bytes<4 * SIZE>());
    }

    template <std::size_t SIZE>
    std::array<std::uint16_t, SIZE> I2CDevice::receive_words() const noexcept
    {
        return Utility::bytes_to_words(this->receive_bytes<2 * SIZE>());
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> I2CDevice::receive_bytes() const noexcept
    {
        std::array<std::uint8_t, SIZE> receive{};
        if (this->initialized_) {
            HAL_I2C_Master_Receive(this->i2c_bus_, this->dev_address_ << 1, receive.data(), receive.size(), TIMEOUT);
        }
        return receive;
    }

    template <std::size_t SIZE>
    std::array<std::uint32_t, SIZE> I2CDevice::read_dwords(std::uint8_t const reg_address) const noexcept
    {
        return Utility::bytes_to_dwords(this->read_bytes<4 * SIZE>(reg_address));
    }

    template <std::size_t SIZE>
    std::array<std::uint16_t, SIZE> I2CDevice::read_words(std::uint8_t const reg_address) const noexcept
    {
        return Utility::bytes_to_words(this->read_bytes<2 * SIZE>(reg_address));
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> I2CDevice::read_bytes(std::uint8_t const reg_address) const noexcept
    {
        std::array<std::uint8_t, SIZE> read{};
        if (this->initialized_) {
            HAL_I2C_Mem_Read(this->i2c_bus_,
                             this->dev_address_ << 1,
                             reg_address,
                             sizeof(reg_address),
                             read.data(),
                             read.size(),
                             TIMEOUT);
        }
        return read;
    }

    template <std::size_t SIZE>
    void I2CDevice::write_dwords(std::uint8_t const reg_address,
                                 std::array<std::uint32_t, SIZE> const& dwords) const noexcept
    {
        this->write_bytes(reg_address, Utility::dwords_to_bytes(dwords));
    }

    template <std::size_t SIZE>
    void I2CDevice::write_words(std::uint8_t const reg_address,
                                std::array<std::uint16_t, SIZE> const& words) const noexcept
    {
        this->write_bytes(reg_address, Utility::words_to_bytes(words));
    }

    template <std::size_t SIZE>
    void I2CDevice::write_bytes(std::uint8_t const reg_address,
                                std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        if (this->initialized_) {
            std::array<std::uint8_t, SIZE> write{bytes};
            HAL_I2C_Mem_Write(this->i2c_bus_,
                              this->dev_address_ << 1,
                              reg_address,
                              sizeof(reg_address),
                              write.data(),
                              write.size(),
                              TIMEOUT);
        }
    }

}; // namespace Utility

#endif // I2C_DEVICE_HPP
