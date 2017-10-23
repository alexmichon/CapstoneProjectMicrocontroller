#include "my_service.h"



MyService::MyService() : BLEService(new uint8_t[16] {UUID128_MY_SERVICE}),
	readCharacteristic(MyCharacteristicRead()),
	sendCharacteristic(MyCharacteristicSend()),
	notifyCharacteristic(MyCharacteristicNotify())
{
	
}




err_t MyService::begin() {
	Serial.println("My service begins");
	err_t e = BLEService::begin();
	if (e) { return e; }

	e = notifyCharacteristic.begin();
	if (e) { return e; }

	e = readCharacteristic.begin();
	if (e) { return e; }

	e = sendCharacteristic.begin();
	if (e) { return e; }

	return e;
}


MyCharacteristicRead MyService::getCharacteristicRead() {
	return readCharacteristic;
}

MyCharacteristicSend MyService::getCharacteristicSend() {
	return sendCharacteristic;
}

MyCharacteristicNotify MyService::getCharacteristicNotify() {
	return notifyCharacteristic;
}