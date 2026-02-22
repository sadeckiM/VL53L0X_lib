#ifndef VL53L0X_INTERNAL_H
#define VL53L0X_INTERNAL_H

#ifndef __TOF_LIBRARY_INTERNAL__
#error                                                                         \
    "VL53L0X_internal.h is for internal use only. Do not include it in your code. If you need to use it, define __TOF_LIBRARY_INTERNAL__ before including it."
#endif
#include "VL53L0X_lib.h"

uint8_t readReg(tof_device_t* dev, uint8_t reg_addr);
int32_t writeReg(tof_device_t* dev, uint8_t reg_addr, uint8_t reg_val);
uint16_t readReg16(tof_device_t* dev, uint8_t reg_addr);
int32_t writeReg16(tof_device_t* dev, uint8_t reg_addr, uint16_t reg_val);
int32_t writeRegList(tof_device_t* dev, uint8_t* reg_addr_val_pair_list);
void readMulti(tof_device_t* dev, uint8_t reg_addr, uint8_t* buffer,
               int32_t count);
int32_t writeMulti(tof_device_t* dev, uint8_t reg_addr, uint8_t* buffer,
                   int32_t count);

#endif // VL53L0X_INTERNAL_H
