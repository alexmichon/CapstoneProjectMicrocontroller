#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Accel_Unified accel2 = Adafruit_LSM303_Accel_Unified(54322);
/* Assign a unique ID to this sensor at the same time */
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
Adafruit_L3GD20_Unified gyro2 = Adafruit_L3GD20_Unified(21);
#define PIN 7
#define TCAADDR 0x70
//int counter = 0;
//int state = 0;
//int laststate = 0; 
//double lastdegree = 0;

int sensorValue = 0;        // value read from the pot
double degree;
double range = 5798.0;


 
void tcaselect(uint8_t i) {
  if (i > 7) return;
 
  Wire.beginTransmission(TCAADDR);
  Wire.write(1 << i);
  Wire.endTransmission();  
}

void setup(void)
{
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  Wire.begin();
  pinMode(PIN, INPUT);
  Serial.begin(9600);
  /* Enable auto-ranging */
  gyro.enableAutoRange(true);

  /* Initialise the sensor */
  tcaselect(1);
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  if(!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
    while(1);
  }
  tcaselect(2);
  if(!accel2.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 second detected ... Check your wiring!");
    while(1);
  }
  if(!gyro2.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("Ooops, no L3GD20 second detected ... Check your wiring!");
    while(1);
  }
}


void loop(void)
{
  /* Delay before the next sample */
    sensors_event_t event;
    sensors_event_t event2;
    sensorValue = pulseIn(PIN,HIGH); 
    
    degree = ((double)sensorValue/range)*360;
    if (range < sensorValue) {
      range = sensorValue;
    }
    /* Display the results (acceleration is measured in m/s^2) */
    tcaselect(1);
    accel.getEvent(&event);
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.print("m/s^2 ");Serial.print("       ");
    gyro.getEvent(&event2);
    Serial.print("X: "); Serial.print(event2.gyro.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event2.gyro.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event2.gyro.z); Serial.print("  ");
    tcaselect(2);
    accel2.getEvent(&event);
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.print("m/s^2 ");Serial.print("       ");
    gyro2.getEvent(&event2);
    Serial.print("X: "); Serial.print(event2.gyro.x); Serial.print("  ");
    Serial.print("Y: "); Serial.print(event2.gyro.y); Serial.print("  ");
    Serial.print("Z: "); Serial.print(event2.gyro.z); Serial.print("  ");
    Serial.print("rad/s "); Serial.print("  ");   
    Serial.print("degree =   ");    
    Serial.println(degree);

    delay(100);
    
}


