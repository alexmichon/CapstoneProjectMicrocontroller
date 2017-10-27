#ifndef BLE_SERVICE_SENSORS_H
#define BLE_SERVICE_SENSORS_H


#include <bluefruit.h>

#include "ble_characteristic_imu.h"
#include "ble_characteristic_encoder.h" 


const uint8_t UUID128_BLE_SERVICE_SENSORS[16] = 
{
	0x72, 0xcb, 0xa5, 0xa9, 0x87, 0x38, 0x48, 0xab, 
	0xb6, 0xe0, 0x34, 0x1a, 0x93, 0x16, 0x95, 0x7f
};


class BLEServiceSensors : public BLEService {

public:

	BLEServiceSensors();

	err_t begin();

	BLECharacteristicImu getImuCharacteristic();
	BLECharacteristicEncoder getEncoderCharacteristic();

	//bool notifyImu(const void *data, uint16_t len);
	//bool notifyEncoder(const void *data, uint16_t len);

private:

	BLECharacteristicImu imuCharacteristic;
	BLECharacteristicEncoder encoderCharacteristic;

};


#endif