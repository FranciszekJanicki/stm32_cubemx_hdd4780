#ifndef COMMON_HPP
#define COMMON_HPP

#include "stm32l4xx.h"
#include "stm32l4xx_hal.h"
#include "stm32l4xx_hal_gpio.h"
#include "stm32l4xx_hal_i2c.h"
#include "stm32l4xx_hal_spi.h"
#include "stm32l4xx_hal_tim.h"
#include "stm32l4xx_hal_usart.h"

namespace Utility {

    using SPIHandle = SPI_HandleTypeDef*;
    using TIMHandle = TIM_HandleTypeDef*;
    using GPIOHandle = GPIO_TypeDef*;
    using UARTHandle = UART_HandleTypeDef*;
    using I2CHandle = I2C_HandleTypeDef*;

}; // namespace Utility

#endif // COMMON_HPP