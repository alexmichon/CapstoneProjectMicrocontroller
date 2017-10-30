#include "i2c.h"
#include <Wire.h>



void i2c_write(uint8_t address, uint8_t reg, uint8_t data) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}



void i2c_read(int address, uint8_t reg, uint8_t* data, int16_t len) {
     int i = 0;
    
     Wire.beginTransmission(address);
     Wire.write(reg);
     Wire.endTransmission();

     Wire.beginTransmission(address);
     Wire.requestFrom(address, len);
     
     while(Wire.available()) {
       char c = Wire.read();
       data[i] = c;
       i++;
     }
     
     Wire.endTransmission();
}