#ifndef _TOFLIB_H_
#define _TOFLIB_H_
/*
 * VL53L0X Library Fork
 * Based on work by Pololu, bitbank2, and danjperron.
 * * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 */

#include <stdio.h>
#include <string.h>
#include "pico/stdlib.h"
#include "pico/binary_info.h"
#include "hardware/i2c.h"

typedef struct tof_i2c_ops {
    int (*i2c_read)(void *ctx, uint8_t addr, uint8_t *data, size_t len);
    int (*i2c_write)(void *ctx, uint8_t addr, const uint8_t *data, size_t len);
    void *user_ctx; // Pointer to user-defined context (e.g., hardware handle)
} tof_i2c_ops_t;

typedef struct tof_device {
    tof_i2c_ops_t *i2c_ops;
    uint8_t addr;
} tof_device_t;
//
// Read the model and revision of the
// tof sensor
//
int tofGetModel(i2c_inst_t *i2c, uint8_t addr, int *model, int *revision);

//
// Read the current distance in mm
//
uint16_t tofReadDistance(i2c_inst_t *i2c, uint8_t addr);

//
// Opens a file system handle to the I2C device
// sets the device continous capture mode
//
int tofInit(i2c_inst_t *i2c, uint8_t addr, int bLongRange);

#endif // _TOFLIB_H
