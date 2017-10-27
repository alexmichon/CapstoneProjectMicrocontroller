#include "ble_service_sensors.h"



BLEServiceSensors::BLEServiceSensors() : BLEService(UUID128_BLE_SERVICE_SENSORS),
	imuCharacteristic(BLECharacteristicImu()),
	encoderCharacteristic(BLECharacteristicEncoder())
{
	
}




err_t BLEServiceSensors::begin() {
	Serial.println("[SERVICE_SENSORS] begin");
	VERIFY_STATUS( BLEService::begin() );

	VERIFY_STATUS( imuCharacteristic.begin() 		);
	VERIFY_STATUS( encoderCharacteristic.begin() 	);

	return ERROR_NONE;
}

BLECharacteristicImu BLEServiceSensors::getImuCharacteristic() {
	return imuCharacteristic;
}

BLECharacteristicEncoder BLEServiceSensors::getEncoderCharacteristic() {
	return encoderCharacteristic;
}

/*
bool BLEServiceSensors::notifyImu() {
	if (imuCharacteristic.notifyEnabled()) {
		Serial.print("[SERVICE_SENSORS] notifying IMU: ");
		if (imuCharacteristic.notify((uint16_t) data, (uint16_t) data, (uint16_t) data)) {
			Serial.println("OK");
		}
		else {
			Serial.println("ERROR");
		}
	}
	else {
		Serial.println("IMU notifications disabled");
	}
	return true;
}

bool BLEServiceSensors::notifyEncoder(const void *data, uint16_t len) {
	if (encoderCharacteristic.notifyEnabled()) {
		Serial.print("[SERVICE_SENSORS] notifying Encoder: ");
		if (encoderCharacteristic.notify((int16_t) data)) {
			Serial.println("OK");
		}
		else {
			Serial.println("ERROR");
		}
	}
	else {
		Serial.println("Encoder notifications disabled");
	}
}
*/