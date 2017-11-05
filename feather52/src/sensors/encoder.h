#ifndef ENCODER_H
#define ENCODER_H


#include <stdint.h>


#define ENCODER_SOURCE_ANALOG 0
#define ENCODER_SOURCE_RANDOM 1

#define ENCODER_RANGE 5798.0

class Encoder {
public:

	Encoder(uint8_t pin);

	void setup();

	void read_angle(float *angle);

private:

	uint8_t _pin;
};


#endif