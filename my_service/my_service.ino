#include <bluefruit.h>
#include "src/my_service.h"


#define BLE_MANUFACTURER "Adafruit Industries"
#define BLE_MODEL "Bluefruit Feather52"
#define BLE_NAME "Bluefruit Alex"





//#define UUID128_SERVICE 0x72, 0xcb, 0xa5, 0xa9, 0x87, 0x38, 0x48, 0xab, 0xb6, 0xe0, 0x34, 0x1a, 0x93, 0x16, 0x95, 0x7f
//#define UUID128_CHAR1 0x65, 0x5a, 0x2e, 0xc6, 0x15, 0x16, 0x48, 0xcd, 0xb0, 0x51, 0xd9, 0xd5, 0x3c, 0xd8, 0x17, 0x41
//#define UUID128_CHAR2 0xb8, 0xb9, 0xca, 0xba, 0xd0, 0x29, 0x43, 0xdc, 0x87, 0x1c, 0x79, 0x8b, 0x5a, 0x31, 0xe2, 0x02


//BLEService        service = BLEService(new uint8_t[16] {UUID128_SERVICE});
//BLECharacteristic char1 = BLECharacteristic(new uint8_t[16] {UUID128_CHAR1});
//BLECharacteristic char2 = BLECharacteristic(new uint8_t[16] {UUID128_CHAR2});

MyService service = MyService();
MyCharacteristicNotify charNotify;
MyCharacteristicSend charSend;
MyCharacteristicRead charRead;

BLEDis bledis;    // DIS (Device Information Service) helper class instance
BLEBas blebas;    // BAS (Battery Service) helper class instance

uint8_t  bps = 0;
char name[100];
char buffer[100];

// Advanced function prototypes
void startAdv(void);
void setupHRM(void);
void connect_callback(uint16_t conn_handle);
void disconnect_callback(uint16_t conn_handle, uint8_t reason);
void cccd_callback(BLECharacteristic& chr, ble_gatts_evt_write_t* request);

void blink_timer_callback(TimerHandle_t xTimerID);

void setup()
{
  Serial.begin(115200);
  Serial.println("Bluefruit52 Custom Service");
  Serial.println("-----------------------\n");

  // Initialise the Bluefruit module
  Serial.println("Initialise the Bluefruit nRF52 module");
  Bluefruit.begin();

  // Set the advertised device name (keep it short!)
  Serial.println("Setting Device Name");
  Bluefruit.setName(BLE_NAME);
  Bluefruit.getName(name, sizeof(name));
  Serial.println(name);

  // Set the connect/disconnect callback handlers
  Bluefruit.setConnectCallback(connect_callback);
  Bluefruit.setDisconnectCallback(disconnect_callback);

  // Configure and Start the Device Information Service
  Serial.println("Configuring the Device Information Service");
  bledis.setManufacturer(BLE_MANUFACTURER);
  bledis.setModel(BLE_MODEL);
  bledis.begin();

  // Start the BLE Battery Service and set it to 100%
  Serial.println("Configuring the Battery Service");
  blebas.begin();
  blebas.write(100);

  // Setup the Heart Rate Monitor service using
  // BLEService and BLECharacteristic classes
  Serial.println("Configuring the Custom Service");
  setupService();

  // Setup the advertising packet(s)
  Serial.println("Setting up the advertising payload(s)");
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
  // Configure the Heart Rate Monitor service
  // See: https://www.bluetooth.com/specifications/gatt/viewer?attributeXmlFile=org.bluetooth.service.heart_rate.xml
  // Supported Characteristics:
  // Name                         UUID    Requirement Properties
  // ---------------------------- ------  ----------- ----------
  // Heart Rate Measurement       0x2A37  Mandatory   Notify
  // Body Sensor Location         0x2A38  Optional    Read
  // Heart Rate Control Point     0x2A39  Conditional Write       <-- Not used here
  service.begin();
  charNotify = service.getCharacteristicNotify();
  charSend = service.getCharacteristicSend();
  charRead = service.getCharacteristicRead();
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

/*void cccd_callback(BLECharacteristic& chr, uint16_t cccd_value)
{
    // Display the raw request packet
    Serial.print("CCCD Updated: ");
    //Serial.printBuffer(request->data, request->len);
    Serial.print(cccd_value);
    Serial.println("");

    // Check the characteristic this CCCD update is associated with in case
    // this handler is used for multiple CCCD records.
    if (chr.uuid == char1.uuid) {
        if (chr.notifyEnabled()) {
            Serial.println("Char 1 'Notify' enabled");
        } else {
            Serial.println("Char 1 'Notify' disabled");
        }
    }
}*/

void loop()
{
  digitalToggle(LED_RED);
  
  if ( Bluefruit.connected() ) {
    uint8_t data1[2] = { 0b00000110, bps++ };           // Sensor connected, increment BPS value
    
    // Note: We use .notify instead of .write!
    // If it is connected but CCCD is not enabled
    // The characteristic's value is still updated although notification is not sent
    if ( charNotify.notify(data1, sizeof(data1)) ){
      Serial.print("Char 1 updated to: "); Serial.println(bps); 
    }else{
      Serial.println("ERROR: Notify not set in the CCCD or not connected!");
    }

    uint8_t value;
    uint16_t len = charSend.read(&value);
    Serial.print("Len = ");Serial.println(len);
    Serial.printf("Value %u\n", value);
  }

  // Only send update once per second
  delay(1000);
}

/**
 * RTOS Idle callback is automatically invoked by FreeRTOS
 * when there are no active threads. E.g when loop() calls delay() and
 * there is no bluetooth or hw event. This is the ideal place to handle
 * background data.
 * 
 * NOTE: FreeRTOS is configured as tickless idle mode. After this callback
 * is executed, if there is time, freeRTOS kernel will go into low power mode.
 * Therefore waitForEvent() should not be called in this callback.
 * http://www.freertos.org/low-power-tickless-rtos.html
 * 
 * WARNING: This function MUST NOT call any blocking FreeRTOS API 
 * such as delay(), xSemaphoreTake() etc ... for more information
 * http://www.freertos.org/a00016.html
 */
void rtos_idle_callback(void)
{
  // Don't call any other FreeRTOS blocking API()
  // Perform background task(s) here
}
