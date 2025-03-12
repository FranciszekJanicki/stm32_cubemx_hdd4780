#ifndef CNT_DEVICE_HPP
#define CNT_DEVICE_HPP

#include "common.hpp"
#include "utility.hpp"
#include <optional>

namespace Utility {

    struct CNTDevice {
    public:
        CNTDevice() noexcept = default;
        CNTDevice(TIMHandle const timer, std::uint32_t const counter_period) noexcept;

        CNTDevice(CNTDevice const& other) = delete;
        CNTDevice(CNTDevice&& other) noexcept = default;

        CNTDevice& operator=(CNTDevice const& other) = delete;
        CNTDevice& operator=(CNTDevice&& other) noexcept = default;

        ~CNTDevice() noexcept;

        [[nodiscard]] std::optional<std::uint32_t> get_count() const noexcept;
        [[nodiscard]] std::optional<std::uint32_t> get_count_difference() const noexcept;

    private:
        std::uint32_t get_current_count() const noexcept;

        void initialize() noexcept;
        void deinitialize() noexcept;

        bool initialized_{false};

        TIMHandle timer_{nullptr};
        std::uint32_t counter_period_{};

        std::uint32_t mutable count_{};
    };

}; // namespace Utility

#endif // CNT_DEVICE_HPP