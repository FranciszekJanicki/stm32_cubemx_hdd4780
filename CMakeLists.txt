cmake_minimum_required(VERSION 3.28)

include("cmake/gcc-arm-none-eabi.cmake")

project(devcontainer-stm32-cubemx-pcf8574 LANGUAGES C CXX ASM)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build type: ${CMAKE_BUILD_TYPE}")

set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

add_subdirectory(cmake/stm32cubemx)
add_subdirectory(app/main)
add_subdirectory(app/utility)
add_subdirectory(app/pcf8574)

target_compile_options(stm32cubemx INTERFACE 
    -w
)
