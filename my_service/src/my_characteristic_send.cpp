#include "my_characteristic_send.h"

MyCharacteristicSend::MyCharacteristicSend() : BLECharacteristic(new uint8_t[16] {UUID128_CHAR_SEND}) {
	setProperties(CHR_PROPS_WRITE);
	setPermission(SECMODE_OPEN, SECMODE_OPEN);
	setFixedLen(1);
	setWriteCallback(&MyCharacteristicSend::write_callback);
}


err_t MyCharacteristicSend::begin() {
	Serial.println("[SEND] begin");
	err_t e = BLECharacteristic::begin();
	if (e) { return e; }

	uint8_t value;
  	read(&value);
	
	return e;
}


void MyCharacteristicSend::write_callback(BLECharacteristic& chr, uint8_t* data, uint16_t len, uint16_t offset) {
	Serial.print("[SEND] Received value: ");
	for (int i = offset; i < len; i++) {
		Serial.print(*(data+i));
	}
	Serial.println("");
}