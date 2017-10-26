#include "ble_characteristic_imu.h"

BLECharacteristicImu::BLECharacteristicImu() : BLECharacteristic(new uint8_t[16]{UUID128_CHAR_IMU}) {
	// Note: You must call .begin() on the BLEService before calling .begin() on
	// any characteristic(s) within that service definition.. Calling .begin() on
	// a BLECharacteristic will cause it to be added to the last BLEService that
	// was 'begin()'ed!

	// Configure the Heart Rate Measurement characteristic
	// See: https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.heart_rate_measurement.xml
	// Permission = Notify
	// Min Len    = 1
	// Max Len    = 8
	//    B0      = UINT8  - Flag (MANDATORY)
	//      b5:7  = Reserved
	//      b4    = RR-Internal (0 = Not present, 1 = Present)
	//      b3    = Energy expended status (0 = Not present, 1 = Present)
	//      b1:2  = Sensor contact status (0+1 = Not supported, 2 = Supported but contact not detected, 3 = Supported and detected)
	//      b0    = Value format (0 = UINT8, 1 = UINT16)
	//    B1      = UINT8  - 8-bit heart rate measurement value in BPM
	//    B2:3    = UINT16 - 16-bit heart rate measurement value in BPM
	//    B4:5    = UINT16 - Energy expended in joules
	//    B6:7    = UINT16 - RR Internal (1/1024 second resolution)
	setProperties(CHR_PROPS_NOTIFY);
  	setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
  	setFixedLen(2);

  	setStringDescriptor("IMU characteristic");
}



err_t BLECharacteristicImu::begin() {
	Serial.println("[NOTIFY] begin");
  	uint8_t data1[2] = { 0b00000110, 0x40 }; // Set the characteristic to use 8-bit values, with the sensor connected and detected
	
	err_t e = BLECharacteristic::begin();
	if (e) { return e; }
	
  	notify(data1, 2);                   // Use .notify instead of .write!

  	return e;
}