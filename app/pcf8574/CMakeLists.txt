add_library(pcf8574 STATIC)

target_sources(pcf8574 PRIVATE 
    "pcf8574.cpp"
)

target_include_directories(pcf8574 PUBLIC 
    "."
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(pcf8574 PRIVATE
    utility
    stm32cubemx
)

target_compile_options(pcf8574 PUBLIC
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
