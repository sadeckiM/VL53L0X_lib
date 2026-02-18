#ifndef VL53L0X_LIB_H_
#define VL53L0X_LIB_H_
/*
 * VL53L0X Library Fork
 * Based on work by Pololu, bitbank2, and danjperron.
 * * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 */
/**
 * \file VL53L0X_lib.h
 * \brief Header file for VL53L0X Time-of-Flight sensor library
 */

#include "hardware/i2c.h"
#include "pico/binary_info.h"
#include "pico/stdlib.h"
#include <stdio.h>
#include <string.h>

/**
 * struct tof_i2c_ops - Abstraction for I2C read/write operations to allow for
 * different hardware implementations
 */
typedef struct tof_i2c_ops {
    int32_t (*i2c_read)(void* ctx, uint8_t addr, uint8_t* data, size_t len,
                        bool nostop);
    int32_t (*i2c_write)(void* ctx, uint8_t addr, const uint8_t* data,
                         size_t len, bool nostop);
    void* user_ctx; // Pointer to user-defined context (e.g., hardware handle)
} tof_i2c_ops_t;

/**
 * struct tof_device - Represents a VL53L0X Time-of-Flight sensor device
 */
typedef struct tof_device {
    tof_i2c_ops_t* i2c_ops;
    uint8_t addr;
    int32_t long_range_mode;
} tof_device_t;

/**
 * \brief Create a default ToF device instance with Pico SDK I2C operations
 *
 * \return A tof_device_t instance with default values
 */
tof_device_t tofCreateDefaultDevice(void);

/**
 * \brief Set a new I2C address for the ToF sensor
 * IMPORTANT: This function will change the I2C address of the sensor, so it
 * falls to the caller to ensure only one sensor is present on the I2C bus when
 * this function is called.
 *
 * \param[in] dev Pointer to the ToF device instance (THIS FUNCTION WILL MODIFY THE DEVICE'S ADDRESS)
 * \param[in] new_addr The new I2C address to set for the sensor (must be a
 * valid 7-bit address)
 * \return 1 on success, or 0 on failure, -1 on invalid address (e.g., out of range or reserved address)
 */
int32_t tofSetAddress(tof_device_t* dev, uint8_t new_addr);

/**
 * \brief Get the model and revision information from the ToF sensor
 *
 * \param[in] dev Pointer to the ToF device instance
 * \param[in,out] model Pointer to an integer where the model ID will be stored
 * \param[in,out] revision Pointer to an integer where the revision ID will be
 * stored
 * \return 1    TODO: return actually useful value
 */
int32_t tofGetModel(tof_device_t* dev, int32_t* model, int32_t* revision);

/**
 * \brief Read the current distance measurement from the ToF sensor in
 * millimeters
 *
 * \param[in] dev Pointer to the ToF device instance
 * \return Distance in millimeters, or -1 on error (e.g., timeout or sensor
 * failure)
 */
uint16_t tofReadDistance(tof_device_t* dev);
/**
 * \brief Initialize the ToF sensor device by reading calibration data and
 * setting it into continuous capture mode
 *
 * \param[in] dev Pointer to the ToF device instance to initialize
 * \return 1 on success, or a 0 on failure (e.g., calibration data is invalid)
 */
int32_t tofInit(tof_device_t* dev);

#endif // VL53L0X_LIB_H_
