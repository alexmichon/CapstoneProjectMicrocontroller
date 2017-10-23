#include "my_characteristic_read.h"


#define READ_DATA 0x0F


MyCharacteristicRead::MyCharacteristicRead() : BLECharacteristic(new uint8_t[16]{UUID128_CHAR_READ}) {
	// Configure the Body Sensor Location characteristic
	// See: https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.characteristic.body_sensor_location.xml
	// Permission = Read
	// Min Len    = 1
	// Max Len    = 1
	//    B0      = UINT8 - Body Sensor Location
	//      0     = Other
	//      1     = Chest
	//      2     = Wrist
	//      3     = Finger
	//      4     = Hand
	//      5     = Ear Lobe
	//      6     = Foot
	//      7:255 = Reserved
	setProperties(CHR_PROPS_READ);
	setPermission(SECMODE_OPEN, SECMODE_NO_ACCESS);
	setFixedLen(1);
}


err_t MyCharacteristicRead::begin() {
	Serial.println("[READ] begin");
	err_t e = BLECharacteristic::begin();
	if (e) { return e; }

	write(2);    // Set the characteristic to 'Wrist' (2)

	return e;
}