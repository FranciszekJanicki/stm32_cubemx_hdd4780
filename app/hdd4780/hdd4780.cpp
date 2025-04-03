#include "hdd4780.hpp"

namespace HDD4780 {

    HDD4780::HDD4780(I2CDevice&& i2c_device, Config const& config, Font const& font) noexcept :
        i2c_device_{std::forward<I2CDevice>(i2c_device)}, font_{font}
    {
        this->initialize(config);
    }

    HDD4780::~HDD4780() noexcept
    {
        this->deinitialize();
    }

    std::uint8_t HDD4780::receive_byte() const noexcept
    {
        return this->i2c_device_.receive_byte();
    }

    void HDD4780::transmit_byte(std::uint8_t const byte) const noexcept
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

    void HDD4780::send_clear_display_command() const noexcept
    {
        this->transmit_byte(std::bit_cast<std::uint8_t>(CLEAR_DISPLAY{}));
    }

    void HDD4780::send_return_home_command() const noexcept
    {
        this->transmit_byte(std::bit_cast<std::uint8_t>(RETURN_HOME{}));
    }

    void HDD4780::send_entry_mode_set_command(bool const ddram_increment, bool const display_shift) const noexcept
    {
        this->transmit_byte(std::bit_cast<std::uint8_t>(ENTRY_MODE_SET{.id = ddram_increment, .s = display_shift}));
    }

    void HDD4780::send_display_on_off_control_command(bool const display,
                                                      bool const cursor,
                                                      bool const blinking) const noexcept
    {
        this->transmit_byte(
            std::bit_cast<std::uint8_t>(DISPLAY_ON_OFF_CONTROL{.d = display, .c = cursor, .b = blinking}));
    }

    void HDD4780::send_cursor_or_display_shift_command(bool const shift_cursor, bool const right_left) const noexcept
    {
        this->transmit_byte(std::bit_cast<std::uint8_t>(CURSOR_OR_DISPLAY_SHIFT{.sc = shift_cursor, .rl = right_left}));
    }

    void HDD4780::send_function_set_command(bool const data_length,
                                            bool const display_lines,
                                            bool const character_font) const noexcept
    {
        this->transmit_byte(
            std::bit_cast<std::uint8_t>(FUNCTION_SET{.dl = data_length, .n = display_lines, .f = character_font}));
    }

    void HDD4780::send_set_cgram_address_command(std::uint8_t const cgram_address) const noexcept
    {
        this->transmit_byte(std::bit_cast<std::uint8_t>(SET_CGRAM_ADDRESS{.acg = cgram_address}));
    }

    void HDD4780::send_set_ddram_address_command(std::uint8_t const ddram_address) const noexcept
    {
        this->transmit_byte(std::bit_cast<std::uint8_t>(SET_DDRAM_ADDRESS{.add = ddram_address}));
    }

}; // namespace HDD4780