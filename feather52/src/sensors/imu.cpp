#include "imu.h"
#include <Arduino.h>

//#define SIMULATION

IMU::IMU(int _tca) {
	bno = Adafruit_BNO055(55+_tca);
	tca = _tca;
}



bool IMU::begin() {
#ifndef SIMULATION
	tca_select();

	return bno.begin();

#else
    return true;
#endif
}



void IMU::read(float *acc, float *gyr, float *mag) {
#ifndef SIMULATION

    tca_select();

    // sensors_event_t event;
    // get_event(&event);

    // Serial.println(tca);

    imu::Vector<3> vecAcc = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);

    acc[0] = vecAcc.x();
    acc[1] = vecAcc.y();
    acc[2] = vecAcc.z();

    // Serial.print(" Acc X: "); Serial.print(acc[0]);
    // Serial.print(" Acc Y: "); Serial.print(acc[1]);
    // Serial.print(" Acc Z: "); Serial.print(acc[2]);
    // Serial.println();

    // tca_select();
    imu::Vector<3> vecGyr = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);

    gyr[0] = vecGyr.x();
    gyr[1] = vecGyr.y();
    gyr[2] = vecGyr.z();

    // Serial.print(" Gyr X: "); Serial.print(gyr[0], 4);
    // Serial.print(" Gyr Y: "); Serial.print(gyr[1], 4);
    // Serial.print(" Gyr Z: "); Serial.print(gyr[2], 4);
    // Serial.println();

    // tca_select();
    imu::Vector<3> vecMag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);

    mag[0] = vecMag.x();
    mag[1] = vecMag.y();
    mag[2] = vecMag.z();

    // Serial.print(" Mag X: "); Serial.print(mag[0]);
    // Serial.print(" Mag Y: "); Serial.print(mag[1]);
    // Serial.print(" Mag Z: "); Serial.print(mag[2]);
    // Serial.println();

#else
    acc[0] = float(random(100)) / 100.0;
    acc[1] = float(random(100)) / 100.0;
    acc[2] = float(random(100)) / 100.0;
    gyr[0] = float(random(100)) / 100.0;
    gyr[1] = float(random(100)) / 100.0;
    gyr[2] = float(random(100)) / 100.0;
    mag[0] = float(random(100)) / 100.0;
    mag[1] = float(random(100)) / 100.0;
    mag[2] = float(random(100)) / 100.0;
#endif
}



void IMU::read_acc(float *acc) {
#ifndef SIMULATION
    sensors_event_t event;
    get_event(&event);
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
    get_event(&event);
    gyr[0] = event.gyro.x;
    gyr[1] = event.gyro.y;
    gyr[2] = event.gyro.z;
#else
    gyr[0] = float(random(100)) / 100.0;
    gyr[1] = float(random(100)) / 100.0;
    gyr[2] = float(random(100)) / 100.0;
#endif
}

void IMU::read_mag(float *mag) {
#ifndef SIMULATION
    sensors_event_t event; 
    get_event(&event);
    mag[0] = event.magnetic.x;
    mag[1] = event.magnetic.y;
    mag[2] = event.magnetic.z;
#else
    mag[0] = float(random(100)) / 100.0;
    mag[1] = float(random(100)) / 100.0;
    mag[2] = float(random(100)) / 100.0;
#endif    
}

void IMU::read_orientation(float *orientation) {
#ifndef SIMULATION
    sensors_event_t event; 
    get_event(&event);
    orientation[0] = event.orientation.x;
    orientation[1] = event.orientation.y;
    orientation[2] = event.orientation.z;
#else
    orientation[0] = float(random(100)) / 100.0;
    orientation[1] = float(random(100)) / 100.0;
    orientation[2] = float(random(100)) / 100.0;
#endif    
}


void IMU::read_euler(float *euler) {
#ifndef SIMULATION

    tca_select();
    imu::Vector<3> vecEuler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);

    euler[0] = vecEuler.x();
    euler[1] = vecEuler.y();
    euler[2] = vecEuler.z();

    // Serial.print(" Euler X: "); Serial.print(euler[0]);
    // Serial.print(" Euler Y: "); Serial.print(euler[1]);
    // Serial.print(" Euler Z: "); Serial.print(euler[2]);
    // Serial.println();

#else
    euler[0] = float(random(100)) / 100.0;
    euler[1] = float(random(100)) / 100.0;
    euler[2] = float(random(100)) / 100.0;
#endif    
}


void IMU::read_quaternion(float *quaternion) {
#ifndef SIMULATION
    tca_select();
    imu::Quaternion quat = bno.getQuat();

    quaternion[0] = quat.w();
    quaternion[1] = quat.x();
    quaternion[2] = quat.y();
    quaternion[3] = quat.z();

    // Serial.print(" Quaternion W: "); Serial.print(quaternion[0]);
    // Serial.print(" Quaternion X: "); Serial.print(quaternion[1]);
    // Serial.print(" Quaternion Y: "); Serial.print(quaternion[2]);
    // Serial.print(" Quaternion Z: "); Serial.print(quaternion[3]);
    // Serial.println();

#else
    quaternion[0] = float(random(100)) / 100.0;
    quaternion[1] = float(random(100)) / 100.0;
    quaternion[2] = float(random(100)) / 100.0;
    quaternion[3] = float(random(100)) / 100.0;
#endif
}



void IMU::tca_select() {
    if (tca > 7) return;
 
    Wire.beginTransmission(TCAADDR);
    Wire.write(1 << tca);
    Wire.endTransmission(); 
}


void IMU::get_event(sensors_event_t *event) {
    tca_select();
    bno.getEvent(event);
}