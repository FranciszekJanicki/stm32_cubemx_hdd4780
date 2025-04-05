add_library(hdd4780 STATIC)

target_sources(hdd4780 PRIVATE 
    "hdd4780.cpp"
)

target_include_directories(hdd4780 PUBLIC 
    ${CMAKE_SOURCE_DIR}/app/stm32_utility
)

target_link_libraries(hdd4780 PRIVATE
    stm32_utility
    stm32cubemx
)

target_compile_options(hdd4780 PUBLIC
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
