#ifndef ENCODER_H
#define ENCODER_H


#include <stdint.h>


#define ENCODER_SOURCE_ANALOG 0
#define ENCODER_SOURCE_RANDOM 1

#define ENCODER_RANGE 3975.0

class Encoder {
public:

	Encoder(uint8_t pin);
	Encoder(uint8_t pin, uint8_t source);

	void setup();

	void read_raw(int16_t *angle);
	void read_angle(float *angle);

private:

	uint8_t _source;
	uint8_t _pin;
};


#endif