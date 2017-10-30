#include "imu.h"
#include "utils/i2c.h"
#include <Arduino.h>


IMU::IMU() : _source(IMU_SOURCE_I2C) {

}

IMU::IMU(uint8_t source) : _source(source) {

}



void IMU::setup() {
	init_acc();
	init_gyr();
	init_mag();
}


void IMU::init_acc() {
    init(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);
}

void IMU::init_gyr() {
    init(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ);
}

void IMU::init_mag() {
    init(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, HMC5843_MEASMODE_CONT);
}



void IMU::read_acc(int16_t *acc) {
    read(acc, 3, ADXL345_ADDRESS, ADXL345_REGISTER_XLSB);
}

void IMU::read_gyr(int16_t *gyr) {
	read(gyr, 3, ITG3200_ADDRESS, ITG3200_REGISTER_XMSB);  //now unpack the bytes
}

void IMU::read_mag(int16_t *mag) {
    read(mag, 3, HMC5843_ADDRESS, HMC5843_REGISTER_XMSB);
}





void IMU::init(uint8_t address, uint8_t reg, uint8_t value) {
	uint8_t data = 0;
	switch(_source) {
		case IMU_SOURCE_I2C:
			i2c_write(address, reg, value);
			i2c_read(address, reg, &data, 1);
			break;
	}
}


void IMU::read(int16_t *buffer, int16_t len, uint8_t address, uint8_t reg) {
	uint8_t *bytes = (byte *) malloc(2 * len);
	memset(bytes, 0, 6);

	switch (_source) {
		case IMU_SOURCE_I2C:
			i2c_read(address, reg, bytes, 2 * len);
			break;
		case IMU_SOURCE_RANDOM:
			for (int i = 0; i < 2 * len; i++) {
				bytes[i] = random(-255, 255);
			}
			break;
	}

	for (int i = 0; i < len; i++) {
		buffer[i] = (int16_t) (bytes[2*i+1] | (bytes[2 * i] << 8));
	}

	free(bytes);
}