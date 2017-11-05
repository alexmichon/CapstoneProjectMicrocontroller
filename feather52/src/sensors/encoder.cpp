#include "encoder.h"
#include <Arduino.h>

#define SIMULATION

Encoder::Encoder(uint8_t pin) : _pin(pin) {

}


void Encoder::setup() {

}

void Encoder::read_angle(float *angle) {
#ifndef SIMULATION
	int16_t raw = pulseIn(_pin, HIGH);
	*angle = float(raw * 360) / ENCODER_RANGE;
#else
	*angle = float(random(360));
#endif
}