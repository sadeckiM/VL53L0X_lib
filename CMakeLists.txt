cmake_minimum_required(VERSION 3.13)
add_library(VL53L0X_lib STATIC)
target_sources(VL53L0X_lib PRIVATE
    src/VL53L0X_lib.c
)
target_include_directories(VL53L0X_lib PUBLIC 
    inc
)
target_link_libraries(VL53L0X_lib PUBLIC
    pico_stdlib
    hardware_i2c
)
