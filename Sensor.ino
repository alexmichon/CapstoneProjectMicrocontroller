#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
/* Assign a unique ID to this sensor at the same time */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(54321);
/* Assign a unique ID to this sensor at the same time */
Adafruit_L3GD20_Unified gyro = Adafruit_L3GD20_Unified(20);
#define PIN 7
int counter = 0;
int state = 0;
int laststate = 0; 
double lastdegree = 0;

void setup(void)
{
#ifndef ESP8266
  while (!Serial);     // will pause Zero, Leonardo, etc until serial console opens
#endif
  pinMode(PIN, INPUT);
  Serial.begin(115200);
  Serial.println("Accelerometer Test"); Serial.println("");
  Serial.println("Gyroscope Test"); Serial.println("");
  /* Enable auto-ranging */
  gyro.enableAutoRange(true);

  /* Initialise the sensor */
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
}


void loop(void)
{
  /* Delay before the next sample */
  state = digitalRead(PIN);
  if(state != laststate) {   
    if (state == HIGH) {
          /* Get a new sensor event */
          sensors_event_t event;
          accel.getEvent(&event);

          /* Display the results (acceleration is measured in m/s^2) */
          Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print("  ");
          Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print("  ");
          Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print("  ");Serial.print("m/s^2 ");Serial.print("       ");
          Serial.print("X: "); Serial.print(event.gyro.x); Serial.print("  ");
          Serial.print("Y: "); Serial.print(event.gyro.y); Serial.print("  ");
          Serial.print("Z: "); Serial.print(event.gyro.z); Serial.print("  ");
          Serial.print("rad/s ");
          Serial.print("degree = ");
          Serial.println(counter);
          //do operations here
          counter = 0;
    } 
    laststate = state; 
  } 
  if(state == HIGH) {
    if(counter < 361) {
    counter++;
    }
  }
//  delay(50);
}
