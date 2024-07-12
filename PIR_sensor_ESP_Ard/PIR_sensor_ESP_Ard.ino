
const int PIR_SENSOR = GPIO_NUM_4;  // the pin that OUTPUT pin of sensor is connected to
const int LED = GPIO_NUM_12;
int pinStateCurrent = LOW;   // current state of pin
int pinStatePrevious = LOW;  // previous state of pin

void setup() {
  Serial.begin(115200);  // initialize serial
  pinMode(LED, OUTPUT);
  pinMode(PIR_SENSOR, INPUT);  // set arduino pin to input mode to read value from OUTPUT pin of sensor

  digitalWrite(LED, HIGH);
  delay(1000);
  digitalWrite(LED, LOW);
}

void loop() {
  pinStatePrevious = pinStateCurrent;         // store old state
  pinStateCurrent = digitalRead(PIR_SENSOR);  // read new state

  if (pinStatePrevious == LOW && pinStateCurrent == HIGH) {  // pin state change: LOW -> HIGH
    Serial.println("Motion detected!");
    digitalWrite(LED, HIGH);
    // TODO: turn on alarm, light or activate a device ... here
  } else if (pinStatePrevious == HIGH && pinStateCurrent == LOW) {  // pin state change: HIGH -> LOW
    Serial.println("Motion stopped!");
    digitalWrite(LED, LOW);
    // TODO: turn off alarm, light or deactivate a device ... here
  }

  // if (digitalRead(PIR_SENSOR)) {
  //   Serial.println("Motion detected!");
  //   digitalWrite(13, HIGH);
  // } else {
  //   Serial.println("watching . . .");
  //   digitalWrite(13, LOW);
  // }
  // delay(200);
}
