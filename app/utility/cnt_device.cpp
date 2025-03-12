#include "cnt_device.hpp"

namespace Utility {

    CNTDevice::CNTDevice(TIMHandle const timer, std::uint32_t const counter_period) noexcept :
        timer_{timer}, counter_period_{counter_period}
    {
        this->initialize();
    }

    CNTDevice::~CNTDevice() noexcept
    {
        this->deinitialize();
    }

    std::optional<std::uint32_t> CNTDevice::get_count() const noexcept
    {
        if (!this->initialized_) {
            return std::optional<std::uint32_t>{std::nullopt};
        }
        this->count_ = this->get_current_count() % this->counter_period_;
        return std::optional<std::uint32_t>{this->count_};
    }

    std::optional<std::uint32_t> CNTDevice::get_count_difference() const noexcept
    {
        auto prev_count{this->count_};
        return this->get_count().transform([prev_count](std::uint32_t const count) { return count - prev_count; });
    }

    void CNTDevice::initialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_Encoder_Start(this->timer_, TIM_CHANNEL_ALL) == HAL_OK) {
                this->initialized_ = true;
            }
        }
    }

    void CNTDevice::deinitialize() noexcept
    {
        if (this->timer_ != nullptr) {
            if (HAL_TIM_Encoder_Stop(this->timer_, TIM_CHANNEL_ALL) == HAL_OK) {
                this->initialized_ = false;
            }
        }
    }

    std::uint32_t CNTDevice::get_current_count() const noexcept
    {
        return static_cast<std::uint32_t>(__HAL_TIM_GetCounter(this->timer_));
    }

}; // namespace Utility