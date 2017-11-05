#ifndef IMU_H
#define IMU_H

#include <stdint.h>

#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>


#define ADXL345_ADDRESS 			(0xA6 >> 1)
#define ADXL345_REGISTER_XLSB 		(0x32)
#define ADXL_REGISTER_PWRCTL 		(0x2D)
#define ADXL_PWRCTL_MEASURE 		(1 << 3)
#define ITG3200_ADDRESS 			(0xD0 >> 1)
#define ITG3200_REGISTER_XMSB 		(0x1D)
#define ITG3200_REGISTER_DLPF_FS 	(0x16)
#define ITG3200_FULLSCALE 			(0x03 << 3)
#define ITG3200_42HZ 				(0x03)
#define HMC5843_ADDRESS 			(0x3C >> 1)
#define HMC5843_REGISTER_XMSB 		(0x03)
#define HMC5843_REGISTER_MEASMODE 	(0x02)
#define HMC5843_MEASMODE_CONT 		(0x00)


#define IMU_SOURCE_I2C 0
#define IMU_SOURCE_RANDOM 1


#define IMU_DATA_ACC 0
#define IMU_DATA_GYR 1
#define IMU_DATA_MAG 2


#define ACCELEROMETER_ID 1
#define GYROSCOPE_ID 2


class IMU {
public:

	IMU();

	void setup();

	void read_acc(float *acc);
	void read_gyr(float *gyr);

private:

	Adafruit_LSM303_Accel_Unified accel;
	Adafruit_L3GD20_Unified gyro;
};

#endif