#include "my_characteristic_send.h"

MyCharacteristicSend::MyCharacteristicSend() : BLECharacteristic(new uint8_t[16] {UUID128_CHAR_SEND}) {
	setProperties(CHR_PROPS_WRITE & CHR_PROPS_WRITE_WO_RESP & CHR_PROPS_INDICATE);
	setPermission(SECMODE_OPEN, SECMODE_OPEN);
	setFixedLen(1);
	setWriteCallback(&MyCharacteristicSend::write_callback);
	setWriteAuthorizeCallbak(&MyCharacteristicSend::write_authorization_callback);
	setCccdWriteCallback(&MyCharacteristicSend::write_cccd_callback);
}


err_t MyCharacteristicSend::begin() {
	Serial.println("My characteristic send begins");
	err_t e = BLECharacteristic::begin();
	if (e) { return e; }
	
	return e;
}


void MyCharacteristicSend::write_callback(BLECharacteristic& chr, uint8_t* data, uint16_t len, uint16_t offset) {
	Serial.println("Write callback");
	for (int i = offset; i < len; i++) {
		Serial.print(*(data+i));
	}
	Serial.println("");
}

void MyCharacteristicSend::write_authorization_callback(BLECharacteristic& chr, ble_gatts_evt_write_t *request) {
	Serial.println("Write authorization callback");
}

void MyCharacteristicSend::write_cccd_callback(BLECharacteristic& chr, uint16_t value) {
	Serial.println("Write cccd callback");
}