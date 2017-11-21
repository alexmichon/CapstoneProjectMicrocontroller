#include "ble_characteristic_encoder.h"

static void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value);

BLECharacteristicEncoder::BLECharacteristicEncoder() : BLECharacteristic(UUID128_CHAR_ENCODER) {
	setProperties(CHR_PROPS_NOTIFY);
  	setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  	setCccdWriteCallback(cccd_callback);
  	setFixedLen(8);
}



err_t BLECharacteristicEncoder::begin() {
	Serial.println("[Encoder] begin");
	
	VERIFY_STATUS( BLECharacteristic::begin() );
	
  	return ERROR_NONE;
}

err_t BLECharacteristicEncoder::notify(const struct EncoderMeasurement2 meas) {
	
	return BLECharacteristic::notify((const void*) &meas, (uint16_t) 8);
}

err_t BLECharacteristicEncoder::notify(const uint16_t sensor_id, const float angle) {
	struct EncoderMeasurement2 meas;

	//meas.sensor_id = sensor_id;
	meas.took_at = millis();
	meas.angle = angle;
	
	return BLECharacteristicEncoder::notify(meas);
}

static void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value) {
	Serial.println("[Encoder] CCCD Callback");
}