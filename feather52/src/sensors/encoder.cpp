#include "encoder.h"
#include <Arduino.h>

Encoder::Encoder(uint8_t pin) :
	_pin(pin),
	_source(ENCODER_SOURCE_ANALOG)
{

}

Encoder::Encoder(uint8_t pin, uint8_t source) :
	_pin(pin),
	_source(source)
{

}


void Encoder::setup() {

}


void Encoder::read_raw(int16_t *angle) {
	switch(_source) {
		case ENCODER_SOURCE_ANALOG:
			//*angle = pulseIn(_pin, HIGH);
			*angle = random(-32767, 32767);
			break;
		case ENCODER_SOURCE_RANDOM:
			*angle = random(-32767, 32767);
			break;
	}
}

void Encoder::read_angle(float *angle) {
	int16_t raw;
	read_raw(&raw);
	*angle = float(raw * 360) / ENCODER_RANGE;
}