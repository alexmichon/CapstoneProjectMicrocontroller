#ifndef MY_SERVICE_H
#define MY_SERVICE_H


#include <bluefruit.h>

#include "my_characteristic_read.h"
#include "my_characteristic_send.h"
#include "my_characteristic_notify.h" 


#define UUID128_MY_SERVICE 0x72, 0xcb, 0xa5, 0xa9, 0x87, 0x38, 0x48, 0xab, 0xb6, 0xe0, 0x34, 0x1a, 0x93, 0x16, 0x95, 0x7f



class MyService : public BLEService {

public:

	MyService();

	err_t begin();

	MyCharacteristicRead getCharacteristicRead();
	MyCharacteristicSend getCharacteristicSend();
	MyCharacteristicNotify getCharacteristicNotify();

private:

	MyCharacteristicRead readCharacteristic;
	MyCharacteristicSend sendCharacteristic;
	MyCharacteristicNotify notifyCharacteristic;

};


#endif