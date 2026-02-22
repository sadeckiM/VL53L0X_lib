#define __TOF_LIBRARY_INTERNAL__
#include "VL53L0X_internal.h"
uint16_t readReg16(tof_device_t* dev, uint8_t ucAddr) {
    uint8_t ucTemp[2];

    dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, &ucAddr, 1,
                            true);
    dev->i2c_ops->i2c_read(dev->i2c_ops->user_ctx, dev->addr, ucTemp, 2, false);
    // Replaces:
    // i2c_write_blocking(i2c_port, addr, &ucAddr, 1, true);
    // i2c_read_blocking(i2c_port, addr, ucTemp, 2, false);
    return (uint16_t)((ucTemp[0] << 8) + ucTemp[1]);
} /* readReg16() */

//
// Read a single register value from I2C device
//
uint8_t readReg(tof_device_t* dev, uint8_t ucAddr) {
    uint8_t ucTemp;
    dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, &ucAddr, 1,
                            true);
    dev->i2c_ops->i2c_read(dev->i2c_ops->user_ctx, dev->addr, &ucTemp, 1,
                           false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, &ucAddr, 1, true);
    // i2c_read_blocking(i2c, addr, &ucTemp, 1, false);

    return ucTemp;
} /* ReadReg() */

void readMulti(tof_device_t* dev, uint8_t ucAddr, uint8_t* pBuf, int iCount) {
    dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, &ucAddr, 1,
                            true);
    dev->i2c_ops->i2c_read(dev->i2c_ops->user_ctx, dev->addr, pBuf, iCount,
                           false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, &ucAddr, 1, true);
    // i2c_read_blocking(i2c, addr, pBuf, iCount, false);
} /* readMulti() */

void writeMulti(tof_device_t* dev, uint8_t ucAddr, uint8_t* pBuf, int iCount) {
    uint8_t ucTemp[16];
    int rc;

    ucTemp[0] = ucAddr;
    memcpy(&ucTemp[1], pBuf, iCount);
    dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, ucTemp,
                            iCount + 1, false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, ucTemp, iCount + 1, false);
} /* writeMulti() */
//
// Write a 16-bit value to a register
//
void writeReg16(tof_device_t* dev, uint8_t ucAddr, uint16_t usValue) {
    uint8_t ucTemp[4];
    int rc;

    ucTemp[0] = ucAddr;
    ucTemp[1] = (uint8_t)(usValue >> 8); // MSB first
    ucTemp[2] = (uint8_t)usValue;

    dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, ucTemp, 3,
                            false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, ucTemp, 3, false);

} /* writeReg16() */
//
// Write a single register/value pair
//
int32_t writeReg(tof_device_t* dev, uint8_t ucAddr, uint8_t ucValue) {
    uint8_t ucTemp[2];
    int rc;

    ucTemp[0] = ucAddr;
    ucTemp[1] = ucValue;
    int ret = dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, ucTemp,
                                      2, false);
    // Replaces:
    // i2c_write_blocking(i2c, addr, ucTemp, 2, false);

    return ret;
}

//
// Write a list of register/value pairs to the I2C device
//
void writeRegList(tof_device_t* dev, uint8_t* ucList) {
    uint8_t ucCount = *ucList++; // count is the first element in the list
    while (ucCount) {
        dev->i2c_ops->i2c_write(dev->i2c_ops->user_ctx, dev->addr, ucList, 2,
                                false);
        // Replaces:
        // i2c_write_blocking(i2c, addr, ucList, 2, false);
        ucList += 2;
        ucCount--;
    }
}
