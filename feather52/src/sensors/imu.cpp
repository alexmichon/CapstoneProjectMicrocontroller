#include "imu.h"
#include <Arduino.h>

#define SIMULATION


IMU::IMU() {
	accel = Adafruit_LSM303_Accel_Unified(ACCELEROMETER_ID);
	gyro  = Adafruit_L3GD20_Unified(GYROSCOPE_ID);
}



void IMU::setup() {
#ifndef SIMULATION
	gyro.enableAutoRange(true);
	if(!accel.begin()) {
	    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
	    while(1);
	}
  	if(!gyro.begin()) {
	    Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
    	while(1);
	}
#endif
}



void IMU::read_acc(float *acc) {
#ifndef SIMULATION
    sensors_event_t event;
    accel.getEvent(&event);
    acc[0] = event.acceleration.x;
    acc[1] = event.acceleration.y;
    acc[2] = event.acceleration.z;
#else
    acc[0] = float(random(100)) / 100.0;
    acc[1] = float(random(100)) / 100.0;
    acc[2] = float(random(100)) / 100.0;
#endif
}

void IMU::read_gyr(float *gyr) {
#ifndef SIMULATION	
	sensors_event_t event; 
    gyro.getEvent(&event);
    gyr[0] = event.gyro.x;
    gyr[1] = event.gyro.y;
    gyr[2] = event.gyro.z;
#else
    gyr[0] = float(random(100)) / 100.0;
    gyr[1] = float(random(100)) / 100.0;
    gyr[2] = float(random(100)) / 100.0;
#endif
}
