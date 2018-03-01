#include <bluefruit.h>
#include "src/ble/ble_service_sensors.h"

#include "src/sensors/imu.h"
#include "src/sensors/encoder.h"




//#define ENCODER_ELBOW_ID 1
#define IMU_TORSO_ARM_ID 1
#define IMU_UPPER_ARM_ID 2
#define IMU_LOWER_ARM_ID 3



//#define ENCODER_PIN 7

#define BLE_MANUFACTURER "Adafruit Industries"
#define BLE_MODEL "Bluefruit Feather52"
#define BLE_NAME "Bluefruit Alex"

//#define SIMULATION




IMU imuTorso = IMU(3);
IMU imuUpper = IMU(1);
IMU imuLower = IMU(0);
//Encoder encoder = Encoder(ENCODER_PIN);

long batch = 0;

float acc[3];
float gyr[3];
float mag[3];
float orientation[3];
float euler[3];
float quaternion[4];
//float angle;



BLEServiceSensors service = BLEServiceSensors();
BLECharacteristicImu imuChar;
//BLECharacteristicEncoder encoderChar;

BLEDis bledis;    // DIS (Device Information Service) helper class instance
BLEBas blebas;    // BAS (Battery Service) helper class instance








// Advanced function prototypes
void startAdv(void);
void setupHRM(void);
void connect_callback(uint16_t conn_handle);
void disconnect_callback(uint16_t conn_handle, uint8_t reason);
void cccd_callback(BLECharacteristic& chr, ble_gatts_evt_write_t* request);

void blink_timer_callback(TimerHandle_t xTimerID);

void setup()
{

  Wire.begin();

  Serial.begin(115200);
  Serial.println("Capstone Project Microcontroller");
  Serial.println("-----------------------\n");

  // Initialize sensors
  if(!imuTorso.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("Ooops, no IMU Torso detected ... Check your wiring or I2C ADDR!");
    while(1);
  }else{
    Serial.println(" IMU Torso detected ");
  }
  
  if(!imuUpper.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("Ooops, no IMU Upper detected ... Check your wiring or I2C ADDR!");
    while(1);
  }else{
    Serial.println(" IMU Upper detected ");
  }

  if(!imuLower.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.println("Ooops, no IMU Lower detected ... Check your wiring or I2C ADDR!");
    while(1);
  }else{
    Serial.println(" IMU Lower detected ");
  }
  Serial.println();

  // Initialize the Bluefruit module
  Serial.println("Initialise the Bluefruit nRF52 module");
  Bluefruit.begin();

  // Set the advertised device name (keep it short!)
  Serial.print("Setting Device Name: ");
  Bluefruit.setName(BLE_NAME);
  Serial.println(BLE_NAME);

  // Set the connect/disconnect callback handlers
  Bluefruit.setConnectCallback(connect_callback);
  Bluefruit.setDisconnectCallback(disconnect_callback);

  // Configure and Start the Device Information Service
  //Serial.println("Configuring the Device Information Service");
  bledis.setManufacturer(BLE_MANUFACTURER);
  bledis.setModel(BLE_MODEL);
  bledis.begin();

  // Start the BLE Battery Service and set it to 100%
  //Serial.println("Configuring the Battery Service");
  blebas.begin();
  blebas.write(100);

  // Setup the Heart Rate Monitor service using
  // BLEService and BLECharacteristic classes
  //Serial.println("Configuring the Custom Service");
  setupService();

  // Setup the advertising packet(s)
  //Serial.println("Setting up the advertising payload(s)");
  startAdv();

  Serial.println("Ready !!!");
  Serial.println("\nAdvertising");
}

void startAdv(void)
{
  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();

  // Include HRM Service UUID
  Bluefruit.Advertising.addService((BLEService&)service);

  // Include Name
  Bluefruit.Advertising.addName();
  
  /* Start Advertising
   * - Enable auto advertising if disconnected
   * - Interval:  fast mode = 20 ms, slow mode = 152.5 ms
   * - Timeout for fast mode is 30 seconds
   * - Start(timeout) with timeout = 0 will advertise forever (until connected)
   * 
   * For recommended advertising interval
   * https://developer.apple.com/library/content/qa/qa1931/_index.html   
   */
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds  
}

void setupService(void)
{
  service.begin();
  imuChar = service.getImuCharacteristic();
  //encoderChar = service.getEncoderCharacteristic();
}

void connect_callback(uint16_t conn_handle)
{
  char central_name[32] = { 0 };
  Bluefruit.Gap.getPeerName(conn_handle, central_name, sizeof(central_name));

  Serial.print("Connected to ");
  Serial.println(central_name);
}

void disconnect_callback(uint16_t conn_handle, uint8_t reason)
{
  (void) conn_handle;
  (void) reason;

  Serial.println("Disconnected");
  Serial.println("Advertising!");
}

void loop()
{
  digitalToggle(LED_RED);
  
  if ( Bluefruit.connected() ) {

    batch++;

    imuTorso.read(acc, gyr, mag);
    imuChar.notify(IMU_TORSO_ARM_ID, IMU_DATA_ACC, batch, acc[0], acc[1], acc[2]);
    imuChar.notify(IMU_TORSO_ARM_ID, IMU_DATA_GYR, batch, gyr[0], gyr[1], gyr[2]);
    imuChar.notify(IMU_TORSO_ARM_ID, IMU_DATA_MAG, batch, mag[0], mag[1], mag[2]);

    imuTorso.read_quaternion(quaternion);
    imuChar.notify(IMU_TORSO_ARM_ID, IMU_DATA_QUATERNION1, batch, quaternion[0], quaternion[1], quaternion[2]);
    imuChar.notify(IMU_TORSO_ARM_ID, IMU_DATA_QUATERNION2, batch, quaternion[3], 0, 0);
    imuTorso.read_euler(euler);
    imuChar.notify(IMU_TORSO_ARM_ID, IMU_DATA_EULER, batch, euler[0], euler[1], euler[2]);
        
    imuUpper.read(acc, gyr, mag);
    imuChar.notify(IMU_UPPER_ARM_ID, IMU_DATA_ACC, batch, acc[0], acc[1], acc[2]);
    imuChar.notify(IMU_UPPER_ARM_ID, IMU_DATA_GYR, batch, gyr[0], gyr[1], gyr[2]);
    imuChar.notify(IMU_UPPER_ARM_ID, IMU_DATA_MAG, batch, mag[0], mag[1], mag[2]);

    imuUpper.read_quaternion(quaternion);
    imuChar.notify(IMU_UPPER_ARM_ID, IMU_DATA_QUATERNION1, batch, quaternion[0], quaternion[1], quaternion[2]);
    imuChar.notify(IMU_UPPER_ARM_ID, IMU_DATA_QUATERNION2, batch, quaternion[3], 0, 0);
    imuUpper.read_euler(euler);
    imuChar.notify(IMU_UPPER_ARM_ID, IMU_DATA_EULER, batch, euler[0], euler[1], euler[2]);

    imuLower.read(acc, gyr, mag);
    imuChar.notify(IMU_LOWER_ARM_ID, IMU_DATA_ACC, batch, acc[0], acc[1], acc[2]);
    imuChar.notify(IMU_LOWER_ARM_ID, IMU_DATA_GYR, batch, gyr[0], gyr[1], gyr[2]);
    imuChar.notify(IMU_LOWER_ARM_ID, IMU_DATA_MAG, batch, mag[0], mag[1], mag[2]);

    imuLower.read_quaternion(quaternion);
    imuChar.notify(IMU_LOWER_ARM_ID, IMU_DATA_QUATERNION1, batch, quaternion[0], quaternion[1], quaternion[2]);
    imuChar.notify(IMU_LOWER_ARM_ID, IMU_DATA_QUATERNION2, batch, quaternion[3], 0, 0);
    imuLower.read_euler(euler);
    imuChar.notify(IMU_LOWER_ARM_ID, IMU_DATA_EULER, batch, euler[0], euler[1], euler[2]);

    // encoder.read_angle(&angle);
    // encoderChar.notify(ENCODER_ELBOW_ID, angle);
  }

  delay(50);
}
