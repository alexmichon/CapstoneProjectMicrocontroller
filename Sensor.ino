#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>

#define TCAADDR 0x70
#define PIN 7

/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified acce1 = Adafruit_LSM303_Accel_Unified(54321);
Adafruit_LSM303_Accel_Unified acce2 = Adafruit_LSM303_Accel_Unified(54322);

Adafruit_L3GD20_Unified gyro1 = Adafruit_L3GD20_Unified(20);
Adafruit_L3GD20_Unified gyro2 = Adafruit_L3GD20_Unified(21);

int sensorValue = 0;       
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
  pinMode(PIN, INPUT);
  Wire.begin();
  Serial.begin(9600);
  /* Enable auto-ranging */
  gyro1.enableAutoRange(true);
  gyro2.enableAutoRange(true);

  /* Initialise the sensor */
  tcaselect(2);
  if(!acce1.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  if(!gyro1.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("Ooops, no L3GD20 detected ... Check your wiring!");
    while(1);
  }

  
  tcaselect(1);
  if(!acce2.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println("Ooops, no LSM303 2st detected ... Check your wiring!");
    while(1);
  }
  if(!gyro2.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.println("Ooops, no L3GD20 2st detected ... Check your wiring!");
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
    
    tcaselect(2);   
    acce1.getEvent(&event); 
    gyro1.getEvent(&event2);
    /* Display the results (acceleration is measured in m/s^2) */
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");Serial.print("m/s^2");Serial.print("    ");
    Serial.print("Wx: "); Serial.print(event2.gyro.x); Serial.print(" ");
    Serial.print("Wy: "); Serial.print(event2.gyro.y); Serial.print(" ");
    Serial.print("Wz: "); Serial.print(event2.gyro.z); Serial.print(" ");

    tcaselect(1);
    acce2.getEvent(&event);
    gyro2.getEvent(&event2);
    Serial.print("      Sensor2 X: "); Serial.print(event.acceleration.x); Serial.print(" ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");Serial.print("m/s^2 ");Serial.print("    ");
    Serial.print("Wx: "); Serial.print(event2.gyro.x); Serial.print(" ");
    Serial.print("Wy: "); Serial.print(event2.gyro.y); Serial.print(" ");
    Serial.print("Wz: "); Serial.print(event2.gyro.z); Serial.print("      "); 
       
    Serial.print("degree =   ");    
    Serial.println(degree);

    
}
