// These constants won't change. They're used to give names to the pins used:
#define outputA 2

int sensorValue = 0;        // value read from the pot

void setup() {
  // initialize serial communications at 9600 bps:
  pinMode (outputA,INPUT);
  Serial.begin(9600);
  // Reads the initial state of the outputA
}

void loop() {
//  sensorValue = digitalRead(outputA);
//  Serial.print("sensor =   ");
  sensorValue = pulseIn(outputA,HIGH);
  Serial.println(sensorValue);
//  Serial.print('\n');
}


//byte PWM_PIN = 3;
// 
//int pwm_value;
// 
//void setup() {
//  pinMode(PWM_PIN, INPUT);
//  Serial.begin(115200);
//}
// 
//void loop() {
//  pwm_value = pulseIn(PWM_PIN, HIGH);
//  Serial.println(pwm_value);
//}

