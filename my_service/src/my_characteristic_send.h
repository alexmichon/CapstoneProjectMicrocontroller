#ifndef MY_CHARACTERISTIC_SEND_H
#define MY_CHARACTERISTIC_SEND_H

#include <bluefruit.h>

#define UUID128_CHAR_SEND 0x65, 0x5a, 0x2e, 0xc6, 0x15, 0x16, 0x48, 0xcd, 0xb0, 0x51, 0xd9, 0xd5, 0x3c, 0xd8, 0x17, 0x41


class MyCharacteristicSend : public BLECharacteristic {

public:

	MyCharacteristicSend();

	err_t begin();

	static void write_callback(BLECharacteristic& chr, uint8_t *data, uint16_t len, uint16_t offset);
	static void write_authorization_callback(BLECharacteristic& chr, ble_gatts_evt_write_t *request);
	static void write_cccd_callback(BLECharacteristic& chr, uint16_t value);

};

#endif