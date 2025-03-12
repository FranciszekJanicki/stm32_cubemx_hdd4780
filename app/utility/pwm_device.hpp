#ifndef PWM_DEVICE_HPP
#define PWM_DEVICE_HPP

#include "common.hpp"
#include "utility.hpp"

namespace Utility {

    struct PWMDevice {
    public:
        PWMDevice() noexcept = default;

        PWMDevice(TIMHandle const timer,
                  std::uint16_t const channel_mask,
                  std::uint16_t const counter_period,
                  float const ref_voltage) noexcept;

        PWMDevice(TIMHandle const timer,
                  std::uint16_t const channel_mask,
                  std::uint16_t const min_raw,
                  std::uint16_t const max_raw,
                  float const ref_voltage) noexcept;

        PWMDevice(PWMDevice const& other) noexcept = delete;
        PWMDevice(PWMDevice&& other) noexcept = default;

        PWMDevice& operator=(PWMDevice const& other) noexcept = delete;
        PWMDevice& operator=(PWMDevice&& other) noexcept = default;

        ~PWMDevice() noexcept;

        void set_frequency(std::uint32_t const frequency) noexcept;

        void set_compare_raw(std::uint16_t const raw) const noexcept;
        void set_compare_voltage(float const voltage) const noexcept;
        void set_compare_max() const noexcept;
        void set_compare_min() const noexcept;

        [[nodiscard]] float get_ref_voltage() const noexcept;

    private:
        void initialize() noexcept;
        void deinitialize() noexcept;

        std::uint16_t voltage_to_raw(float const voltage) const noexcept;
        float raw_to_voltage(std::uint16_t const raw) const noexcept;

        bool initialized_{false};

        TIMHandle timer_{nullptr};
        std::uint16_t channel_mask_{};

        std::uint16_t min_raw_{};
        std::uint16_t max_raw_{};
        float ref_voltage_{};
    };

}; // namespace Utility

#endif // PWM_DEVICE_HPP