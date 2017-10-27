#include "ble_characteristic_imu.h"


static void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value);

BLECharacteristicImu::BLECharacteristicImu() : BLECharacteristic(UUID128_CHAR_IMU) {
	setProperties(CHR_PROPS_NOTIFY);
  	setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  	setCccdWriteCallback(cccd_callback);
  	setFixedLen(10);
}



err_t BLECharacteristicImu::begin() {
	Serial.println("[IMU] begin");

	VERIFY_STATUS( BLECharacteristic::begin() );
  	
  	return ERROR_NONE;
}


err_t BLECharacteristicImu::notify(const struct ImuMeasurement meas) {
	return BLECharacteristic::notify((const void*) &meas, (uint16_t) sizeof(meas));
}


err_t BLECharacteristicImu::notify(int16_t acc_x, int16_t acc_y, int16_t acc_z) {
	struct ImuMeasurement meas {
		millis(),
		acc_x,
		acc_y,
		acc_z
	};

	return BLECharacteristicImu::notify(meas);
}

static void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value) {
	Serial.println("[IMU] CCCD Callback");
}