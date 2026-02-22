#ifndef VL53L0X_LIB_H_
#define VL53L0X_LIB_H_

/**
 * \file VL53L0X_lib.h
 * \brief Header file for VL53L0X Time-of-Flight sensor library
 */
/*
 * VL53L0X Library Fork
 * Based on work by Pololu, bitbank2, and danjperron.
 * * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 */
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

/**
 * struct tof_i2c_ops - Abstraction for I2C read/write operations to allow for
 * different hardware implementations
 */
typedef struct tof_i2c_ops {
    /**
     * \brief Pointer to function for reading data from the I2C bus. 
     * The function should read 'len' bytes from the device at 'addr' into the 'data' buffer. If 'nostop' is true, the function should not send a stop condition after the read operation, allowing for a repeated start if needed.
     * 
     *
     * \param[in] ctx Pointer to user-defined context (e.g., hardware handle)
     * \param[in] addr Address of the I2C device to read from (7-bit address)
     * \param[in] data Pointer to a buffer where the read data will be stored
     * \param[in] len Amount of bytes to read from the device
     * \param[in] nostop If true, the function should not send a stop condition after the read operation (useful for repeated start conditions)
     * \return Number of bytes read on success, or a negative value on error (e.g., I2C communication failure)
     */
    int32_t (*i2c_read)(void* ctx, uint8_t addr, uint8_t* data, size_t len,
                        bool nostop);

    /**
     * \brief Pointer to function for writing data to the I2C bus.
     * The function should write 'len' bytes from the 'data' buffer to the device at 'addr'. If 'nostop' is true, the function should not send a stop condition after the write operation, allowing for a repeated start if needed.
     *
     *
     * \param[in] ctx Pointer to user-defined context (e.g., hardware handle)
     * \param[in] addr Address of the I2C device to write to (7-bit address)
     * \param[in] data Pointer to a buffer containing data to be written
     * \param[in] len Amount of bytes to write to the device
     * \param[in] nostop If true, the function should not send a stop condition after the write operation (useful for repeated start conditions)
     * \return Number of bytes written on success, or a negative value on error (e.g., I2C communication failure)
     */
    int32_t (*i2c_write)(void* ctx, uint8_t addr, const uint8_t* data,
                         size_t len, bool nostop);
    /**
     * \brief Pointer to function for introducing a delay in microseconds.
     *
     * \param[in] microseconds amount of time to delay in microseconds
     * \return 0 on success, or a negative value on error (e.g., if the delay function is not implemented or fails to execute properly)
     */
    int32_t (*tof_delay_us)(uint32_t microseconds);
    void* user_ctx; // Pointer to user-defined context (e.g., hardware handle)
} tof_i2c_ops_t;

/**
 * struct tof_device - Represents a VL53L0X Time-of-Flight sensor device
 */
typedef struct tof_device {
    tof_i2c_ops_t* i2c_ops;
    uint8_t addr;
    bool long_range_mode;
} tof_device_t;

/**
 * \brief Create a default ToF device instance with uninitialized I2C operations
 *
 * The returned device has its fields set to library defaults (for example,
 * a default I2C address and range mode), but the \c i2c_ops pointer is
 * intentionally left as NULL. The caller must assign a valid ::tof_i2c_ops_t
 * implementation to \c dev->i2c_ops (and, if needed, \c user_ctx) before
 * calling any functions that perform I2C communication (such as ::tofInit
 * or ::tofReadDistance).
 *
 * \return A ::tof_device_t instance with default configuration and
 *         \c i2c_ops set to NULL.
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
 * \return Distance in millimeters, or 65535 (0xFFFF) on timeout or error
 * (e.g., sensor failure)
 */
uint16_t tofReadDistance(tof_device_t* dev);
/**
 * \brief Initialize the ToF sensor device by reading calibration data and
 * setting it into continuous capture mode
 *
 * \param[in] dev Pointer to the ToF device instance to initialize
 * \return 1 on success; 0 if initialization fails for any reason (e.g., I2C
 *         operations are not initialized, sensor communication fails, or
 *         calibration data is invalid)
 */
int32_t tofInit(tof_device_t* dev);

#endif // VL53L0X_LIB_H_
