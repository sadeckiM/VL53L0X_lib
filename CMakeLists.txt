cmake_minimum_required(VERSION 3.13)
add_library(VL53L0X_lib STATIC)
target_sources(VL53L0X_lib PRIVATE
    src/VL53L0X_lib.c
    src/tof_register_functions_internal.c
)
target_include_directories(VL53L0X_lib PUBLIC 
    inc
)
# Note: Do not link platform-specific libraries here to keep VL53L0X_lib platform-independent.
# Platform or application targets should link pico_stdlib, hardware_i2c, etc. as needed.
