#ifndef BLE_CHARACTERISTIC_ENCODER_H
#define BLE_CHARACTERISTIC_ENCODER_H

#include <bluefruit.h>

const uint8_t UUID128_CHAR_ENCODER[16] = 
{
	0x27, 0xd6, 0x25, 0x83, 0xae, 0xcb, 0x46, 0x69, 
	0xa3, 0xa3, 0x36, 0x66, 0x11, 0x5c, 0xe1, 0x86
};

class BLECharacteristicEncoder : public BLECharacteristic {
	
public:

	BLECharacteristicEncoder();

	err_t begin();
};


#endif