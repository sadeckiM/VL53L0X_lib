#ifndef VL53L0X_INTERNAL_H
#define VL53L0X_INTERNAL_H

#ifndef __TOF_LIBRARY_INTERNAL__
#error                                                                         \
    "VL53L0X_internal.h is for internal use only. Do not include it in your code."
#endif
#include "VL53L0X_lib.h"

uint8_t readReg(tof_device_t* dev, uint8_t ucAddr);
uint16_t readReg16(tof_device_t* dev, uint8_t ucAddr);
int32_t writeReg(tof_device_t* dev, uint8_t ucAddr, uint8_t ucValue);
void writeReg16(tof_device_t* dev, uint8_t ucAddr, uint16_t usValue);
void writeRegList(tof_device_t* dev, uint8_t* ucList);
void readMulti(tof_device_t* dev, uint8_t ucAddr, uint8_t* pBuf,
               int32_t iCount);
void writeMulti(tof_device_t* dev, uint8_t ucAddr, uint8_t* pBuf,
                int32_t iCount);
#endif // VL53L0X_INTERNAL_H
