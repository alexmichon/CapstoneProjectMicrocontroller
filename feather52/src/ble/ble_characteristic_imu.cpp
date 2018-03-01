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


err_t BLECharacteristicImu::notify(const uint8_t sensor_id, const uint8_t type, const uint16_t batch, const float data_x, const float data_y, const float data_z) {
	struct ImuMeasurement meas;
	meas.sensor_id = sensor_id;
	meas.data_type = type;
	meas.batch = batch;
	meas.took_at = millis();
	meas.data_x = data_x;
	meas.data_y = data_y;
	meas.data_z = data_z;

	return BLECharacteristicImu::notify(meas);
}

static void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value) {
	
}