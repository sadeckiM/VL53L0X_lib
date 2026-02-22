#define __TOF_LIBRARY_INTERNAL__
#include "VL53L0X_internal.h"

//
// Read a single register value from I2C device
//
uint8_t readReg(tof_device_t* dev, uint8_t reg_addr) {
    uint8_t reg_buf;
    dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, &reg_addr, 1,
                            true);
    dev->i2c_ops->i2c_read(dev->i2c_ops->user_ctx, dev->addr, &reg_buf, 1,
                           false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, &ucAddr, 1, true);
    // i2c_read_blocking(i2c, addr, &ucTemp, 1, false);

    return reg_buf;
} /* ReadReg() */
//
// Write a single register/value pair
//
int32_t writeReg(tof_device_t* dev, uint8_t reg_addr, uint8_t reg_val) {
    uint8_t payload[2];

    payload[0] = reg_addr;
    payload[1] = reg_val;

    int ret = dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr,
                                      payload, 2, false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, ucTemp, 2, false);

    return ret;
}

uint16_t readReg16(tof_device_t* dev, uint8_t reg_addr) {
    uint8_t payload[2];

    dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, &reg_addr, 1,
                            true);
    dev->i2c_ops->i2c_read(dev->i2c_ops->user_ctx, dev->addr, payload, 2, false);
    // Replaces:
    // i2c_write_blocking(i2c_port, addr, &ucAddr, 1, true);
    // i2c_read_blocking(i2c_port, addr, ucTemp, 2, false);
    return (uint16_t)((payload[0] << 8) + payload[1]);
} /* readReg16() */
//
// Write a 16-bit value to a register
//
int32_t writeReg16(tof_device_t* dev, uint8_t reg_addr, uint16_t reg_val) {
    uint8_t ucTemp[4];

    ucTemp[0] = reg_addr;
    ucTemp[1] = (uint8_t)(reg_val >> 8); // MSB first
    ucTemp[2] = (uint8_t)reg_val;

    int32_t ret = dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr,
                                          ucTemp, 3, false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, ucTemp, 3, false);
    return ret;

} /* writeReg16() */
//
// Write a list of register/value pairs to the I2C device
//
int32_t writeRegList(tof_device_t* dev, uint8_t* reg_addr_val_pair_list) {
    uint8_t count = *reg_addr_val_pair_list++; // count is the first element in the list
    int32_t bytes_sent = 0;
    while (count) {
        int32_t ret = dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, reg_addr_val_pair_list, 2,
                                false);
        if (ret != 2) {
            // Handle error (e.g., log it, retry, etc.)
            // For now, we just break the loop on error
            break;
        }
        bytes_sent += ret;
        // Replaces:
        // i2c_write_blocking(i2c, addr, ucList, 2, false);
        reg_addr_val_pair_list += 2;
        count--;
    }
    return bytes_sent;
}

void readMulti(tof_device_t* dev, uint8_t ucAddr, uint8_t* pBuf, int iCount) {
    dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, &ucAddr, 1,
                            true);
    dev->i2c_ops->i2c_read(dev->i2c_ops->user_ctx, dev->addr, pBuf, iCount,
                           false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, &ucAddr, 1, true);
    // i2c_read_blocking(i2c, addr, pBuf, iCount, false);
} /* readMulti() */

int32_t writeMulti(tof_device_t* dev, uint8_t reg_addr, uint8_t* buffer, int count) {
    uint8_t temp[16];
    int rc;

    temp[0] = reg_addr;
    memcpy(&temp[1], buffer, count);
    int32_t ret = dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, temp,
                            count + 1, false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, ucTemp, iCount + 1, false);
    return ret;
} /* writeMulti() */
