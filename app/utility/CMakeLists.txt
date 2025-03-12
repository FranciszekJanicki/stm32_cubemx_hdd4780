add_library(utility STATIC)

target_sources(utility PRIVATE 
    "gpio.hpp"
    "i2c_device.hpp" 
    "i2c_device.cpp"
    "spi_device.hpp" 
    "spi_device.cpp"
    "ow_device.hpp" 
    "ow_device.cpp"
    "pwm_device.cpp"
    "cnt_device.cpp"
    "vector3d.hpp"
    "quaternion3d.hpp"
    "utility.hpp"
)

target_include_directories(utility PUBLIC 
    "."
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(utility PRIVATE
    stm32cubemx
)

target_compile_options(utility PUBLIC
    -std=c++23
    -Wall
    -Wextra
    -Wconversion
    -Wshadow
    -Wpedantic
    -Wnarrowing
    -Waddress
    -pedantic
    -Wdeprecated
    -Wsign-conversion
    -Wduplicated-cond
    -Wduplicated-branches
    -Wlogical-op
    -Wnull-dereference
    -Wdouble-promotion
    -Wimplicit-fallthrough
    -Wcast-align
    -fconcepts
)
