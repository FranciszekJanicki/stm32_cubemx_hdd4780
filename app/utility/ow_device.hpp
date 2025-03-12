#ifndef OW_DEVICE_HPP
#define OW_DEVICE_HPP

#include "common.hpp"
#include "gpio.hpp"
#include "utility.hpp"

namespace Utility {

    struct OWDevice {
    public:
        OWDevice() noexcept = default;
        OWDevice(TIMHandle const timer, GPIO const dev_pin, std::uint64_t const dev_address) noexcept;

        OWDevice(OWDevice const& other) = delete;
        OWDevice(OWDevice&& other) noexcept = default;

        OWDevice& operator=(OWDevice const& other) = delete;
        OWDevice& operator=(OWDevice&& other) noexcept = default;

        ~OWDevice() noexcept;

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

        std::uint64_t dev_address() const noexcept;

    private:
        static std::uint64_t get_counter_microseconds(TIMHandle const timer) noexcept
        {
            return 1000ULL * get_counter_miliseconds(timer);
        }

        static std::uint64_t get_counter_miliseconds(TIMHandle const timer) noexcept
        {
            return 1000ULL * __HAL_TIM_GetCounter(timer) / HAL_GetTickFreq() / __HAL_TIM_GetClockDivision(timer);
        }

        static void delay_microseconds(TIMHandle const timer, std::uint64_t const delay) noexcept
        {
            if (timer != nullptr) {
                HAL_TIM_Base_Start(timer);
                while (get_counter_miliseconds(timer) < delay) {
                }
            }
        }

        static constexpr std::uint32_t TIMEOUT{100U};
        static constexpr std::uint32_t DELAY_80_US{80U};
        static constexpr std::uint32_t DELAY_320_US{320U};

        void initialize() noexcept;
        void deinitialize() noexcept;

        bool initialized_{false};

        TIMHandle timer_{nullptr};

        GPIO dev_pin_{};
        std::uint64_t dev_address_{};
    };

    template <std::size_t SIZE>
    void OWDevice::transmit_dwords(std::array<std::uint32_t, SIZE> const& dwords) const noexcept
    {
        this->transmit_bytes(Utility::dwords_to_bytes(dwords));
    }

    template <std::size_t SIZE>
    void OWDevice::transmit_words(std::array<std::uint16_t, SIZE> const& words) const noexcept
    {
        this->transmit_bytes(Utility::words_to_bytes(words));
    }

    template <std::size_t SIZE>
    void OWDevice::transmit_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        if (this->initialized_) {
        }
    }

    template <std::size_t SIZE>
    std::array<std::uint32_t, SIZE> OWDevice::receive_dwords() const noexcept
    {
        return Utility::bytes_to_dwords(this->receive_bytes<4 * SIZE>());
    }

    template <std::size_t SIZE>
    std::array<std::uint16_t, SIZE> OWDevice::receive_words() const noexcept
    {
        return Utility::bytes_to_words(this->receive_bytes<2 * SIZE>());
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> OWDevice::receive_bytes() const noexcept
    {
        std::array<std::uint8_t, SIZE> receive{};
        if (this->initialized_) {
        }
        return receive;
    }

    template <std::size_t SIZE>
    std::array<std::uint32_t, SIZE> OWDevice::read_dwords(std::uint8_t const reg_address) const noexcept
    {
        return Utility::bytes_to_dwords(this->read_bytes<4 * SIZE>(reg_address));
    }

    template <std::size_t SIZE>
    std::array<std::uint16_t, SIZE> OWDevice::read_words(std::uint8_t const reg_address) const noexcept
    {
        return Utility::bytes_to_words(this->read_bytes<2 * SIZE>(reg_address));
    }

    template <std::size_t SIZE>
    std::array<std::uint8_t, SIZE> OWDevice::read_bytes(std::uint8_t const reg_address) const noexcept
    {
        std::array<std::uint8_t, SIZE> read{};
        if (this->initialized_) {
        }
        return read;
    }

    template <std::size_t SIZE>
    void OWDevice::write_dwords(std::uint8_t const reg_address,
                                std::array<std::uint32_t, SIZE> const& dwords) const noexcept
    {
        this->write_bytes(reg_address, Utility::dwords_to_bytes(dwords));
    }

    template <std::size_t SIZE>
    void OWDevice::write_words(std::uint8_t const reg_address,
                               std::array<std::uint16_t, SIZE> const& words) const noexcept
    {
        this->write_bytes(reg_address, Utility::words_to_bytes(words));
    }

    template <std::size_t SIZE>
    void OWDevice::write_bytes(std::uint8_t const reg_address,
                               std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        if (this->initialized_) {
        }
    }

}; // namespace Utility

#endif // OW_DEVICE_HPP