#include "ble_service_sensors.h"
#include "ble_characteristic_startstop.h"



static void write_callback(BLECharacteristic& chr, uint8_t* data, uint16_t len, uint16_t offset);

BLECharacteristicStartStop::BLECharacteristicStartStop() : BLECharacteristic(UUID128_CHAR_STARTSTOP) {
	
}


err_t BLECharacteristicStartStop::begin() {
	setProperties(CHR_PROPS_WRITE);
	setPermission(SECMODE_NO_ACCESS, SECMODE_OPEN);
	setFixedLen(1);

	//setStringDescriptor("Start / Stop characteristic");

	setWriteCallback(write_callback);

	Serial.println("[STARTSTOP] begin");
	VERIFY_STATUS( BLECharacteristic::begin() );

	return ERROR_NONE;
}


static void write_callback(BLECharacteristic& chr, uint8_t* data, uint16_t len, uint16_t offset) {
	Serial.print("[STARTSTOP] Received value: ");
	for (int i = offset; i < len; i++) {
		Serial.print(*(data+i));
	}
	Serial.println("");
	BLEServiceSensors& parent = (BLEServiceSensors&) chr.parentService();
	parent.enable(data);
}