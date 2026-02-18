# VL53L0X Library with a Hardware Abstraction Layer

A high-performance C static library for the VL53L0X Time-of-Flight (ToF) distance sensor. 
This library is an abstracted implementation designed to be separate from the underlying I2C communication, allowing you to provide your own I2C read/write functions. 
It was first intended for use with Raspberry Pi Pico SDK and is licensed under the GNU General Public License v3.0 (GPLv3).

## 📜 Lineage & Credits
This library is the result of a collaborative open-source chain. By using this fork, you benefit from the work of:
1. **Pololu Corporation**: The original Arduino library structure.
2. **Larry Bank (bitbank2)**: Simplification and port to Linux systems.
3. **Daniel Perron (danjperron)**: Basic integration with the Pico SDK.
4. **Michał Sadecki (sadeckiM), Maksymilian Książka (maxksiazka)**: Abstracted I2C operations, added support for multiple addresses and buses, enhanced documentation and improved error handling.

## ⚖️ License
This project is licensed under the **GNU General Public License v3.0 (GPLv3)**. 

Because this fork is derived from code licensed under the GPLv3 by Larry Bank, the license remains "reciprocal." You are free to use and modify this code, but any distributions of the software must also be licensed under the GPLv3. 

**Note:** The underlying STMicroelectronics API constants and low-level communication logic remain subject to their original BSD-style notice (see `LICENSE` file for full details).

---

## 🛠 Integration (Pico SDK & CMake)

This library is intended to be used as a **linked static library** in your project.

### 1. Project Structure
Place this library into your project's library directory:
```text
my_project/
├── lib/
│   └── VL53L0X_lib/     <-- This library
├── CMakeLists.txt
└── main.c
```
### 2. Top level CMakeLists.txt
Add the following to your top-level `CMakeLists.txt`:
```cmake
add_subdirectory(lib)
target_link_libraries(<EXECUTABLE_NAME> PRIVATE VL53L0X_lib)
```

## 😑 Code example
```c
#include "VL53L0X_lib.h"
// other includes...
tof_i2c_ops_t i2c_ops = {
    .i2c_write = my_i2c_write_function,
    .i2c_read = my_i2c_read_function,
    .user_ctx = i2c0 // bus context, e.g., pointer to i2c instance
};
tof_device_t your_tof_device = tofCreateDefaultDevice();
your_tof_device.i2c_ops = &i2c_ops;
// Initialize and use the device as needed
```
---
## 🚧 Project Status

This library is currently in **active development**. The core functionality for basic distance measurement is implemented and (not yet)tested, 
but additional features (such as error handling) are still being refined.

Contributions and feedback are welcome!
