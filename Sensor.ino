#include <Wire.h>

void i2c_write(int address, byte reg, byte data) {
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(data);
  Wire.endTransmission();
}

void i2c_read(int address, byte reg, int count, byte* data) {
     int i = 0;
    
     Wire.beginTransmission(address);
     Wire.write(reg);
     Wire.endTransmission();
     Wire.beginTransmission(address);
     Wire.requestFrom(address,count);
     while(Wire.available())
     {
       char c = Wire.read();
       data[i] = c;
       i++;
     }
     Wire.endTransmission();
}

#define outputA A0
#define ADXL345_ADDRESS (0xA6 >> 1)
#define ADXL345_REGISTER_XLSB (0x32)
#define ADXL_REGISTER_PWRCTL (0x2D)
#define ADXL_PWRCTL_MEASURE (1 << 3)
#define ITG3200_ADDRESS (0xD0 >> 1)
#define ITG3200_REGISTER_XMSB (0x1D)
#define ITG3200_REGISTER_DLPF_FS (0x16)
#define ITG3200_FULLSCALE (0x03 << 3)
#define ITG3200_42HZ (0x03)
#define HMC5843_ADDRESS (0x3C >> 1)
#define HMC5843_REGISTER_XMSB (0x03)
#define HMC5843_REGISTER_MEASMODE (0x02)
#define HMC5843_MEASMODE_CONT (0x00)

//IMU
int accelerometer_data[3];
int gyro_data[3];
int magnetometer_data[3];

//encoder
int sensorValue = 0;        // value read from the pot
double degree;
double range = 3975.0;

void init_acce() {
      byte data = 0; 
      i2c_write(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, ADXL_PWRCTL_MEASURE);
      i2c_read(ADXL345_ADDRESS, ADXL_REGISTER_PWRCTL, 1, &data);
      Serial.println((unsigned int)data);
}

void init_mag() {
      byte data = 0;
      i2c_write(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, HMC5843_MEASMODE_CONT);
      i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_MEASMODE, 1, &data);
      Serial.println((unsigned int)data);
}

void init_pos() {
      byte data = 0;  
      i2c_write(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, ITG3200_FULLSCALE | ITG3200_42HZ);
      i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_DLPF_FS, 1, &data);
      Serial.println((unsigned int)data);
}



void read_acce() {
       byte bytes[6];
       memset(bytes,0,6); //initialization     

       i2c_read(ADXL345_ADDRESS, ADXL345_REGISTER_XLSB, 6, bytes);     
       for (int i=0;i<3;++i) {
          accelerometer_data[i] = (int)bytes[2*i] + (((int)bytes[2*i + 1]) << 8);
       }
}

void read_pos() {
        byte bytes[6];
        memset(bytes,0,6);
        
        i2c_read(ITG3200_ADDRESS, ITG3200_REGISTER_XMSB, 6, bytes);  //now unpack the bytes
        for (int i=0;i<3;++i) {
            gyro_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
        }
}

void read_mag() {
        byte bytes[6];
        memset(bytes,0,6);
        
        i2c_read(HMC5843_ADDRESS, HMC5843_REGISTER_XMSB, 6, bytes);
        for (int i=0;i<3;++i) {
            magnetometer_data[i] = (int)bytes[2*i + 1] + (((int)bytes[2*i]) << 8);
        }
}


void setup() {
      Wire.begin();
      Serial.begin(9600);
      pinMode (outputA,INPUT);
      for(int i = 0; i < 3; ++i) {
        accelerometer_data[i] = magnetometer_data[i] = gyro_data[i] = 0;
      }//initailization
    
      init_acce();
      init_mag();
      init_pos();
}



void loop() {
   read_acce();
   Serial.print("Acce: ");
   Serial.print(accelerometer_data[0]);Serial.print("\t");
   Serial.print(accelerometer_data[1]);Serial.print("\t");
   Serial.print(accelerometer_data[2]);Serial.print("\t"); 
   Serial.print("\t"); 
   Serial.print("\t"); 
   
   read_mag();
   Serial.print("Mag: ");
   Serial.print(magnetometer_data[0]);Serial.print("\t"); 
   Serial.print(magnetometer_data[1]);Serial.print("\t"); 
   Serial.print(magnetometer_data[2]);Serial.print("\t"); 
   Serial.print("\t");
   Serial.print("\t");  
   
   read_pos();
   Serial.print("Gyro: ");
   Serial.print(gyro_data[0]);Serial.print("\t");
   Serial.print(gyro_data[1]);Serial.print("\t");
   Serial.print(gyro_data[2]);Serial.print("\t");
   Serial.print("\t");   

   sensorValue = pulseIn(outputA,HIGH);
   degree = ((double)sensorValue/range)*360;
   Serial.print("    Degree = ");
   Serial.println(degree);
   delay(100); //Sample rate
}



