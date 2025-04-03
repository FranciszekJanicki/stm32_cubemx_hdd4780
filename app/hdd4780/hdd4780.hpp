#ifndef HDD4780_HPP
#define HDD4780_HPP

#include "hdd4780_commands.hpp"
#include "hdd4780_config.hpp"
#include <optional>

namespace HDD4780 {

    struct HDD4780 {
    public:
        HDD4780() noexcept = default;

        HDD4780(I2CDevice&& i2c_device, Config const& config, Font const& font) noexcept;

        HDD4780(HDD4780 const& other) = delete;
        HDD4780(HDD4780&& other) noexcept = default;

        HDD4780& operator=(HDD4780 const& other) = delete;
        HDD4780& operator=(HDD4780&& other) noexcept = default;

        ~HDD4780() noexcept;

    private:
        std::uint8_t receive_byte() const noexcept;

        template <std::size_t SIZE>
        std::array<std::uint8_t, SIZE> receive_bytes() const noexcept;

        template <std::size_t SIZE>
        void transmit_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept;

        void transmit_byte(std::uint8_t const byte) const noexcept;

        void initialize(Config const& config) noexcept;
        void deinitialize() noexcept;

        void send_clear_display_command() const noexcept;

        void send_return_home_command() const noexcept;

        void send_entry_mode_set_command(bool const ddram_increment, bool const display_shift) const noexcept;

        void
        send_display_on_off_control_command(bool const display, bool const cursor, bool const blinking) const noexcept;

        void send_cursor_or_display_shift_command(bool const shift_cursor, bool const right_left) const noexcept;

        void send_function_set_command(bool const data_length,
                                       bool const display_lines,
                                       bool const character_font) const noexcept;

        void send_set_cgram_address_command(std::uint8_t const cgram_address) const noexcept;

        void send_set_ddram_address_command(std::uint8_t const ddram_address) const noexcept;

        bool initialized_{false};

        I2CDevice i2c_device_{};

        Font font_{};
    };

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, SIZE> HDD4780::receive_bytes() const noexcept
    {
        return this->i2c_device_.receive_bytes<SIZE>();
    }

    template <std::size_t SIZE>
    inline void HDD4780::transmit_bytes(std::array<std::uint8_t, SIZE> const& bytes) const noexcept
    {
        this->i2c_device_.transmit_bytes(bytes);
    }

}; // namespace HDD4780

#undef PACKED

#endif // HDD4780_HPP