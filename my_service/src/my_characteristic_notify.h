#ifndef MY_CHARACTERISTIC_NOTIFY_H
#define MY_CHARACTERISTIC_NOTIFY_H

#include <bluefruit.h>

#define UUID128_CHAR_NOTIFY 0xde, 0x70, 0xd8, 0x93, 0xc6, 0x96, 0x46, 0xfa, 0xaf, 0x2b, 0x16, 0x63, 0x22, 0x22, 0x82, 0xe0


class MyCharacteristicNotify : public BLECharacteristic {
	
public:

	MyCharacteristicNotify();

	err_t begin();

	static void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value);
};


#endif