cmake_minimum_required(VERSION 3.13)
add_library(VL53L0X_pico STATIC)
target_sources(VL53L0X_pico PRIVATE
    src/VL53L0X_pico.c
)
target_include_directories(VL53L0X_pico PUBLIC 
    inc
)
target_link_libraries(VL53L0X_pico PUBLIC
    pico_stdlib
    hardware_i2c
)
