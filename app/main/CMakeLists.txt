add_executable(main)

target_sources(main PRIVATE 
    "main.cpp"
)

target_include_directories(main PRIVATE 
    ${CMAKE_SOURCE_DIR}/app/hdd4780
    ${CMAKE_SOURCE_DIR}/cmake/stm32cubemx
)

target_link_libraries(main PRIVATE
    stm32cubemx
    hdd4780
    stm32_utility
)

target_compile_options(main PUBLIC
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
