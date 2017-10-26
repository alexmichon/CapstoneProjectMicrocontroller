#include "ble_service_sensors.h"



BLEServiceSensors::BLEServiceSensors() : BLEService(new uint8_t[16] {UUID128_BLE_SERVICE_SENSORS}),
	startStopCharacteristic(BLECharacteristicStartStop()),
	imuCharacteristic(BLECharacteristicImu()),
	encoderCharacteristic(BLECharacteristicEncoder()),
	enabled(false)
{
	
}




err_t BLEServiceSensors::begin() {
	Serial.println("[BLE_SERVICE_SENSORS] begin");
	err_t e = BLEService::begin();
	if (e) { return e; }

	e = startStopCharacteristic.begin();
	if (e) { return e; }

	e = imuCharacteristic.begin();
	if (e) { return e; }

	e = encoderCharacteristic.begin();
	if (e) { return e; }

	return e;
}


BLECharacteristicStartStop BLEServiceSensors::getStartStopCharacteristic() {
	return startStopCharacteristic;
}

BLECharacteristicImu BLEServiceSensors::getImuCharacteristic() {
	return imuCharacteristic;
}

BLECharacteristicEncoder BLEServiceSensors::getEncoderCharacteristic() {
	return encoderCharacteristic;
}


bool BLEServiceSensors::notifyImu(uint16_t value) {
	if (enabled) {
		return imuCharacteristic.notify(value);
	}
}

bool BLEServiceSensors::notifyEncoder(uint16_t value) {
	if (enabled) {
		return encoderCharacteristic.notify(value);
	}
}


void BLEServiceSensors::enable(bool value) {
	enabled = value;
}
