#ifndef BLE_CHARACTERISTIC_IMU_H
#define BLE_CHARACTERISTIC_IMU_H

#include <bluefruit.h>

const uint8_t UUID128_CHAR_IMU[16] = 
{ 
	0xde, 0x70, 0xd8, 0x93, 0xc6, 0x96, 0x46, 0xfa,
	0xaf, 0x2b, 0x16, 0x63, 0x22, 0x22, 0x82, 0xe0
};

class BLECharacteristicImu : public BLECharacteristic {
	
public:

	BLECharacteristicImu();

	err_t begin();
};


#endif