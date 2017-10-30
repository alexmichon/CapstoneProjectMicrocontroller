#ifndef I2C_H
#define I2C_H

#include <stdint.h>

void i2c_write(uint8_t address, uint8_t reg, uint8_t data);
void i2c_read(int address, uint8_t reg, uint8_t* data, int16_t len); 

#endif