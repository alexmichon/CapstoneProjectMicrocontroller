#ifndef MY_CHARACTERISTIC_READ_H
#define MY_CHARACTERISTIC_READ_H

#include <bluefruit.h>

#define UUID128_CHAR_READ 0xb8, 0xb9, 0xca, 0xba, 0xd0, 0x29, 0x43, 0xdc, 0x87, 0x1c, 0x79, 0x8b, 0x5a, 0x31, 0xe2, 0x02


class MyCharacteristicRead : public BLECharacteristic {
	
public:

	MyCharacteristicRead();

	err_t begin();

};


#endif