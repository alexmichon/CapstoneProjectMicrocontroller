#ifndef BLE_CHARACTERISTIC_STARTSTOP_H
#define BLE_CHARACTERISTIC_STARTSTOP_H

#include <bluefruit.h>

#define UUID128_CHAR_STARTSTOP 0x65, 0x5a, 0x2e, 0xc6, 0x15, 0x16, 0x48, 0xcd, 0xb0, 0x51, 0xd9, 0xd5, 0x3c, 0xd8, 0x17, 0x41


class BLECharacteristicStartStop : public BLECharacteristic {

public:

	BLECharacteristicStartStop();

	err_t begin();

	static void write_callback(BLECharacteristic& chr, uint8_t *data, uint16_t len, uint16_t offset);

};

#endif