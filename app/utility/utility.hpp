#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <algorithm>
#include <array>
#include <bit>
#include <bitset>
#include <cassert>
#include <cmath>
#include <concepts>
#include <cstdint>
#include <cstring>
#include <numbers>
#include <type_traits>
#include <utility>

namespace Utility {

    template <typename T>
    concept Trivial = std::is_trivial_v<T>;

    template <typename T>
    concept Arithmetic = std::is_arithmetic_v<T>;

    template <std::floating_point T>
    T differentiate(T const value,
                    T const prev_value,
                    T const sampling_time,
                    T const prev_derivative,
                    T const time_constant)
    {
        if (time_constant + sampling_time == static_cast<T>(0)) {
            assert(true);
        }
        return (value - prev_value + prev_derivative * time_constant) / (time_constant + sampling_time);
    }

    template <std::floating_point T>
    T differentiate(T const value, T const prev_value, T const sampling_time)
    {
        if (sampling_time == static_cast<T>(0)) {
            assert(true);
        }
        return (value - prev_value) / sampling_time;
    }

    template <std::floating_point T>
    T integrate(T const value, T const prev_value, T const sampling_time) noexcept
    {
        return (value + prev_value) * static_cast<T>(0.5F) * sampling_time;
    }

    template <std::floating_point T>
    T degrees_to_radians(T const degrees) noexcept
    {
        return degrees * std::numbers::pi_v<T> / static_cast<T>(360.0);
    }

    template <std::floating_point T>
    T radians_to_degrees(T const radians) noexcept
    {
        return radians * static_cast<T>(360.0) / std::numbers::pi_v<T>;
    }

    template <Trivial Value>
    std::array<std::uint8_t, sizeof(Value)> value_to_bytes(Value const& value) noexcept
    {
        std::array<std::uint8_t, sizeof(Value)> bytes{};
        std::memcpy(bytes.data(), std::addressof(value), sizeof(Value));
        return bytes;
    }

    template <Trivial Value>
    Value bytes_to_value(std::array<std::uint8_t, sizeof(Value)> const& bytes) noexcept
    {
        Value value{};
        std::memcpy(std::addressof(value), bytes.data(), sizeof(Value));
        return value;
    }

    template <std::unsigned_integral UInt>
    inline void write_bits(UInt& data,
                           UInt const write_data,
                           std::uint8_t const write_size,
                           std::uint8_t const write_position) noexcept
    {
        UInt mask = ((1U << write_size) - 1U) << (write_position - write_size + 1U);
        UInt temp = (write_data << (write_position - write_size + 1U)) & mask;
        data &= ~mask;
        data |= temp;
    }

    template <std::unsigned_integral UInt>
    inline void write_bit(UInt& data, bool const write_data, std::uint8_t const write_position) noexcept
    {
        write_data ? (data |= (1U << write_position)) : (data &= ~(1U << write_position));
    }

    template <std::unsigned_integral UInt>
    inline UInt read_bits(UInt data, std::uint8_t const read_size, std::uint8_t const read_position) noexcept
    {
        UInt mask = ((1U << read_size) - 1U) << (read_position - read_size + 1U);
        data &= mask;
        data >>= (read_position - read_size + 1U);
        return data;
    }

    template <std::unsigned_integral UInt>
    inline bool read_bit(UInt data, std::uint8_t const read_position) noexcept
    {
        return (data & (1U << read_position)) ? true : false;
    }

    inline std::uint16_t big_endian_bytes_to_word(std::array<std::uint8_t, 2UL> const bytes) noexcept
    {
        return static_cast<std::uint16_t>(bytes[0UL] << 8UL) | static_cast<std::uint16_t>(bytes[1UL]);
    }

    inline std::uint16_t little_endian_bytes_to_word(std::array<std::uint8_t, 2UL> const bytes) noexcept
    {
        return static_cast<std::uint16_t>(bytes[0UL]) | static_cast<std::uint16_t>(bytes[1UL] << 8UL);
    }

    inline std::array<std::uint8_t, 2UL> word_to_big_endian_bytes(std::uint16_t const word) noexcept
    {
        return {static_cast<std::uint8_t>(word >> 8UL), static_cast<std::uint8_t>(word)};
    }

    inline std::array<std::uint8_t, 2UL> word_to_little_endian_bytes(std::uint16_t const word) noexcept
    {
        return {static_cast<std::uint8_t>(word), static_cast<std::uint8_t>(word >> 8UL)};
    }

    inline std::uint32_t big_endian_bytes_to_dword(std::array<std::uint8_t, 4UL> const bytes) noexcept
    {
        return static_cast<std::uint32_t>(bytes[0UL] << 24UL) | static_cast<std::uint32_t>(bytes[1UL] << 16UL) |
               static_cast<std::uint32_t>(bytes[2UL] << 8UL) | static_cast<std::uint16_t>(bytes[3UL]);
    }

    inline std::uint32_t little_endian_bytes_to_dword(std::array<std::uint8_t, 4UL> const bytes) noexcept
    {
        return static_cast<std::uint32_t>(bytes[0UL]) | static_cast<std::uint32_t>(bytes[1UL] << 8UL) |
               static_cast<std::uint32_t>(bytes[2UL] << 16UL) | static_cast<std::uint32_t>(bytes[3UL] << 24UL);
    }

    inline std::array<std::uint8_t, 4UL> dword_to_big_endian_bytes(std::uint32_t const dword) noexcept
    {
        return {static_cast<std::uint8_t>(dword >> 24UL),
                static_cast<std::uint8_t>(dword >> 16UL),
                static_cast<std::uint8_t>(dword >> 8UL),
                static_cast<std::uint8_t>(dword)};
    }

    inline std::array<std::uint8_t, 4UL> dword_to_little_endian_bytes(std::uint32_t const dword) noexcept
    {
        return {static_cast<std::uint8_t>(dword),
                static_cast<std::uint8_t>(dword >> 8UL),
                static_cast<std::uint8_t>(dword >> 16UL),
                static_cast<std::uint8_t>(dword >> 24UL)};
    }

    template <std::size_t SIZE>
    inline std::array<std::uint16_t, SIZE / 2>
    big_endian_bytes_to_words(std::array<std::uint8_t, SIZE> const& bytes) noexcept
    {
        static_assert(SIZE % 2 == 0);
        std::array<std::uint16_t, SIZE / 2> words{};
        for (std::size_t i{}; i < words.size(); ++i) {
            words[i] = static_cast<std::uint16_t>(bytes[2 * i] << 8) | static_cast<std::uint16_t>(bytes[2 * i + 1]);
        }
        return words;
    }

    template <std::size_t SIZE>
    inline std::array<std::uint16_t, SIZE / 2>
    little_endian_bytes_endian_to_words(std::array<std::uint8_t, SIZE> const& bytes) noexcept
    {
        static_assert(SIZE % 2 == 0);
        std::array<std::uint16_t, SIZE / 2> words{};
        for (std::size_t i{}; i < words.size(); ++i) {
            words[i] = static_cast<std::uint16_t>(bytes[2 * i]) | static_cast<std::uint16_t>(bytes[2 * i + 1] << 8);
        }
        return words;
    }

    template <std::size_t SIZE>
    inline std::array<std::uint16_t, SIZE / 2> bytes_to_words(std::array<std::uint8_t, SIZE> const& bytes,
                                                              std::endian const endian = std::endian::big) noexcept
    {
        return endian == std::endian::little ? little_endian_bytes_endian_to_words(bytes)
                                             : big_endian_bytes_to_words(bytes);
    }

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, 2 * SIZE>
    words_to_big_endian_bytes(std::array<std::uint16_t, SIZE> const& words) noexcept
    {
        std::array<std::uint8_t, 2 * SIZE> bytes{};
        for (std::size_t i{}; i < words.size(); ++i) {
            bytes[2 * i] = static_cast<std::uint8_t>(words[i] >> 8);
            bytes[2 * i + 1] = static_cast<std::uint8_t>(words[i]);
        }
        return bytes;
    }

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, 2 * SIZE>
    words_to_little_endian_bytes(std::array<std::uint16_t, SIZE> const& words) noexcept
    {
        std::array<std::uint8_t, 2 * SIZE> bytes{};
        for (std::size_t i{}; i < words.size(); ++i) {
            bytes[2 * i] = static_cast<std::uint8_t>(words[i]);
            bytes[2 * i + 1] = static_cast<std::uint8_t>(words[i] >> 8);
        }
        return bytes;
    }

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, 2 * SIZE> words_to_bytes(std::array<std::uint16_t, SIZE> const& words,
                                                             std::endian const endian = std::endian::big) noexcept
    {
        return endian == std::endian::little ? words_to_little_endian_bytes(words) : words_to_big_endian_bytes(words);
    }

    template <std::size_t SIZE>
    inline std::array<std::uint32_t, SIZE / 4>
    big_endian_bytes_to_dwords(std::array<std::uint8_t, SIZE> const& bytes) noexcept
    {
        static_assert(SIZE % 4 == 0);
        std::array<std::uint32_t, SIZE / 4> dwords{};
        for (std::size_t i{}; i < dwords.size(); ++i) {
            dwords[i] =
                static_cast<std::uint32_t>(bytes[2 * i] << 24) | static_cast<std::uint32_t>(bytes[2 * i + 1] << 16) |
                static_cast<std::uint32_t>(bytes[2 * i + 2] << 8) | static_cast<std::uint32_t>(bytes[2 * i + 3]);
        }
        return dwords;
    }

    template <std::size_t SIZE>
    inline std::array<std::uint32_t, SIZE / 4>
    little_endian_bytes_endian_to_dwords(std::array<std::uint8_t, SIZE> const& bytes) noexcept
    {
        static_assert(SIZE % 4 == 0);
        std::array<std::uint32_t, SIZE / 4> dwords{};
        for (std::size_t i{}; i < dwords.size(); ++i) {
            dwords[i] = static_cast<std::uint32_t>(bytes[2 * i]) | static_cast<std::uint32_t>(bytes[2 * i + 1] << 8) |
                        static_cast<std::uint32_t>(bytes[2 * i + 2] << 16) |
                        static_cast<std::uint32_t>(bytes[2 * i + 3] << 24);
        }
        return dwords;
    }

    template <std::size_t SIZE>
    inline std::array<std::uint32_t, SIZE / 4> bytes_to_dwords(std::array<std::uint8_t, SIZE> const& bytes,
                                                               std::endian const endian = std::endian::big) noexcept
    {
        return endian == std::endian::little ? little_endian_bytes_endian_to_dwords(bytes)
                                             : big_endian_bytes_to_dwords(bytes);
    }

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, 4 * SIZE>
    dwords_to_big_endian_bytes(std::array<std::uint32_t, SIZE> const& dwords) noexcept
    {
        std::array<std::uint8_t, 4 * SIZE> bytes{};
        for (std::size_t i{}; i < dwords.size(); ++i) {
            bytes[2 * i] = static_cast<std::uint8_t>(dwords[i] >> 24);
            bytes[2 * i + 1] = static_cast<std::uint8_t>(dwords[i] >> 16);
            bytes[2 * i + 2] = static_cast<std::uint8_t>(dwords[i] >> 8);
            bytes[2 * i + 3] = static_cast<std::uint8_t>(dwords[i]);
        }
        return bytes;
    }

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, 4 * SIZE>
    dwords_to_little_endian_bytes_endian(std::array<std::uint32_t, SIZE> const& dwords) noexcept
    {
        std::array<std::uint8_t, 4 * SIZE> bytes{};
        for (std::size_t i{}; i < dwords.size(); ++i) {
            bytes[2 * i] = static_cast<std::uint8_t>(dwords[i]);
            bytes[2 * i + 1] = static_cast<std::uint8_t>(dwords[i] >> 8);
            bytes[2 * i + 2] = static_cast<std::uint8_t>(dwords[i] >> 16);
            bytes[2 * i + 3] = static_cast<std::uint8_t>(dwords[i] >> 24);
        }
        return bytes;
    }

    template <std::size_t SIZE>
    inline std::array<std::uint8_t, 4 * SIZE> dwords_to_bytes(std::array<std::uint32_t, SIZE> const& dwords,
                                                              std::endian const endian = std::endian::big) noexcept
    {
        return endian == std::endian::little ? dwords_to_little_endian_bytes_endian(dwords)
                                             : dwords_to_big_endian_bytes(dwords);
    }

    template <Arithmetic From, Arithmetic To>
    inline To
    rescale(From const from_value, From const from_min, From const from_max, To const to_min, To const to_max) noexcept
    {
        return (std::clamp(from_value, from_min, from_max) - from_min) * (to_max - to_min) / (from_max - from_min) +
               to_min;
    }

    template <std::unsigned_integral UInt>
    inline UInt reflection(UInt const data) noexcept
    {
        UInt reflection{};
        for (std::uint8_t i{}; i < std::bit_width(data); ++i) {
            write_bit(reflection, read_bit(data, i), std::bit_width(data) - 1U - i);
        }
        return reflection;
    }

    template <std::unsigned_integral UInt, std::size_t SIZE>
    inline UInt calculate_crc(std::array<std::uint8_t, SIZE> const& data,
                              UInt const init,
                              UInt const polynomial,
                              UInt const xor_out,
                              bool const reflect_in,
                              bool const reflect_out) noexcept
    {
        UInt crc{init};
        UInt msb_mask{1U << (std::bit_width(crc) - 1U)};
        UInt crc_mask{(1U << std::bit_width(crc)) - 1U};

        for (std::uint8_t byte : data) {
            if (reflect_in) {
                byte = reflection(byte);
            }
            crc ^= byte << (std::bit_width(crc) - 8U);

            for (std::uint8_t bit{}; bit < 8U; ++bit) {
                if (crc & msb_mask) {
                    crc = (crc << 1U) ^ polynomial;
                } else {
                    crc <<= 1U;
                }
            }
        }

        if (reflect_out) {
            crc = reflect(crc);
        }
        crc ^= xor_out;
        return crc & crc_mask;
    }

    inline std::uint32_t count_to_freq_hz(std::uint32_t const count,
                                          std::uint32_t const prescaler,
                                          std::uint32_t const clock_frequency,
                                          std::uint32_t const clock_divider = 0UL) noexcept
    {
        return clock_frequency / (count + 1UL) / (prescaler + 1UL) / (clock_divider + 1UL);
    }

    inline std::uint32_t count_to_time_ms(std::uint32_t const count,
                                          std::uint32_t const prescaler,
                                          std::uint32_t const clock_frequency,
                                          std::uint32_t const clock_divider = 0UL) noexcept
    {
        return 1000UL / count_to_freq_hz(count, prescaler, clock_frequency, clock_divider);
    }

    inline std::uint32_t freq_hz_to_count(std::uint32_t const frequency_hz,
                                          std::uint32_t const prescaler,
                                          std::uint32_t const clock_frequency_hz,
                                          std::uint32_t const clock_divider = 0UL) noexcept
    {
        return clock_frequency_hz / (prescaler + 1UL) / (clock_divider + 1UL) / frequency_hz - 1UL;
    }

    inline std::uint32_t time_ms_to_count(std::uint32_t const time_ms,
                                          std::uint32_t const prescaler,
                                          std::uint32_t const clock_frequency_hz,
                                          std::uint32_t const clock_divider = 0UL) noexcept
    {
        return freq_hz_to_count(1000UL / time_ms, prescaler, clock_frequency_hz, clock_divider);
    }

}; // namespace Utility

#endif // UTILITY_HPP