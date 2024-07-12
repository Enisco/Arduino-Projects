// Define the analog pin connected to the MQ5 sensor
const int mq5Pin = A1, mq9Pin = A2, mq4Pin = A3;

// Define variables for sensor calibration
const float R0 = 10.0;          // Resistance of the sensor in clean air (in kohms), mq4 and mq9 have 20
const float Rs_R0_Ratio = 1.0;  // Rs/R0 ratio for clean air
float ppm_mq4, ppm_mq5, ppm_mq9;

void setup() {
  Serial.begin(115200);
  delay(60000);
}

void loop() {
  readMQ5ppm();
  readMQ4ppm();
  readMQ9ppm();
  delay(3000);
}

void readMQ5ppm() {
  // Read analog value from MQ5 sensor
  int sensorValue = analogRead(mq5Pin);

  // Convert analog value to resistance (in kohms)
  float sensorVoltage = sensorValue * (5.0 / 1023.0);                     // Convert analog value to voltage
  float sensorResistance = (5.0 - sensorVoltage) / sensorVoltage * 10.0;  // Convert voltage to resistance

  // Calculate ppm value using the Rs/R0 ratio
  ppm_mq5 = pow(10, ((log10(sensorResistance / R0) + 0.095) / (-0.33)));

  // Print ppm value to serial monitor
  Serial.print("LPG PPM: ");
  Serial.println(ppm_mq5);

  delay(10);  // Delay for stability
}

void readMQ4ppm() {
  // Read analog value from MQ4 sensor
  int sensorValue_mq4 = analogRead(mq4Pin);

  // Convert analog value to resistance (in kohms)
  float sensorVoltage_mq4 = sensorValue_mq4 * (5.0 / 1023.0);                         // Convert analog value to voltage
  float sensorResistance_mq4 = (5.0 - sensorVoltage_mq4) / sensorVoltage_mq4 * 10.0;  // Convert voltage to resistance

  // Calculate ppm value using the Rs/R0 ratio
  ppm_mq4 = pow(10, ((log10(sensorResistance_mq4 / (R0 * 2)) - 0.28) / (-0.51)));

  // Print ppm value to serial monitor
  Serial.print("Methane PPM: ");
  Serial.println(ppm_mq4);

  delay(10);  // Delay for stability
}

void readMQ9ppm() {
  // Read analog value from MQ9 sensor
  int sensorValue_mq9 = analogRead(mq9Pin);

  // Convert analog value to resistance (in kohms)
  float sensorVoltage_mq9 = sensorValue_mq9 * (5.0 / 1023.0);                         // Convert analog value to voltage
  float sensorResistance_mq9 = (5.0 - sensorVoltage_mq9) / sensorVoltage_mq9 * 10.0;  // Convert voltage to resistance

  // Calculate ppm value using the Rs/R0 ratio
  ppm_mq9 = pow(10, ((log10(sensorResistance_mq9 / R0 * 2) - 0.2) / (-0.53)));

  // Print ppm value to serial monitor
  Serial.print("CO PPM: ");
  Serial.println(ppm_mq9);

  delay(10);  // Delay for stability
}
