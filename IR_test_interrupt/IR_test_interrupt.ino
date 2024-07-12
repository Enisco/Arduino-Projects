const int IR_sensor = 0;
bool isTriggered = false;
int previousVal = 0;

void setup() {
  pinMode(IR_sensor, INPUT);  // Set IR sensor 1 pin as input
  Serial.begin(115200);       // Start serial communication
  attachInterrupt(IR_sensor, showInterrupt, RISING);
}

void showInterrupt() {
  checkVal();
  if (isTriggered == false) {
    Serial.println(" >>>> Interrupt triggered ");
  } else {
    Serial.println(" ??? Interrupt done ");
  }
}

void checkVal() {
  int sensorValue = digitalRead(2);  // Read IR sensor value
  Serial.print("Sensor: ");
  Serial.println(sensorValue);
  if (sensorValue != previousVal) {
    previousVal = sensorValue;
    isTriggered = !isTriggered;
  }
}

void loop() {
  if (isTriggered == false) {
    Serial.println(". . ");
    delay(5000);
  }
}
