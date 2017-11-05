#include "ble_characteristic_imu.h"


static void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value);

BLECharacteristicImu::BLECharacteristicImu() : BLECharacteristic(UUID128_CHAR_IMU) {
	setProperties(CHR_PROPS_NOTIFY);
  	setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  	setCccdWriteCallback(cccd_callback);
  	setFixedLen(20);
}


err_t BLECharacteristicImu::notify(const struct ImuMeasurement meas) {
	return BLECharacteristic::notify((const void*) &meas, (uint16_t) sizeof(meas));
}


err_t BLECharacteristicImu::notify(const uint16_t sensor_id, const uint16_t type, const float data_x, const float data_y, const float data_z) {
	struct ImuMeasurement meas {
		sensor_id, type, millis(), data_x, data_y, data_z
	};

	return BLECharacteristicImu::notify(meas);
}

static void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value) {
	Serial.println("[IMU] CCCD Callback");
}