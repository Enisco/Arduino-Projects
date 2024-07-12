
#include <TH02_dev.h>
#include "Arduino.h"
#include "Wire.h"
#include "THSensor_base.h"
#include <SoftwareSerial.h>
#include "Air_Quality_Sensor.h"

AirQualitySensor sensor(A0);
SoftwareSerial nodeSerial(5, 6);  // RX, TX
TH02_dev TH02;
int quality;
float temper, humidity;
const int mq5Pin = A1, mq9Pin = A2, mq4Pin = A3;

// Define variables for sensor calibration
const float R0 = 10.0;          // Resistance of the sensor in clean air (in kohms), mq4 and mq9 have 20
const float Rs_R0_Ratio = 1.0;  // Rs/R0 ratio for clean air
float ppm_mq4, ppm_mq5, ppm_mq9;

void setup() {
  Serial.begin(115200);
  nodeSerial.begin(9600);

  Serial.println("Atmosphere Monitor\n");
  /* Power up,delay 150ms,until voltage is stable */
  delay(150);
  /* Reset HP20x_dev */
  TH02.begin();
  delay(100);

  Serial.println("Waiting for sensors to init...");
  delay(60000);

  if (sensor.init()) {
    Serial.println("Sensor ready.");
  } else {
    Serial.println("Sensor ERROR!");
  }
  Serial.println("TH02_dev is available.\n");
}

void loop() {
  readAirQuality();
  readTempHumidity();
  readMQ5ppm();
  readMQ4ppm();
  readMQ9ppm();
  sendDataToNode();
  Serial.println("");
  delay(60000);
}

void sendDataToNode() {
  delay(100);
  String data = String(temper) + "," + String(humidity) + "," + String(ppm_mq5, 2) + "," + String(ppm_mq4, 2) + "," + String(ppm_mq9, 2) + "," + String(quality);
  Serial.println(data);
  nodeSerial.println(data);
}

void readAirQuality() {
  quality = sensor.slope();

  Serial.print("Air quality indicator: ");
  Serial.println(quality);

  if (quality == AirQualitySensor::FORCE_SIGNAL) {
    Serial.println(" ... Very High pollution! Force signal active.");
  } else if (quality == AirQualitySensor::HIGH_POLLUTION) {
    Serial.println(" ... High pollution!");
  } else if (quality == AirQualitySensor::LOW_POLLUTION) {
    Serial.println(" ... Low pollution!");
  } else if (quality == AirQualitySensor::FRESH_AIR) {
    Serial.println(" ... Fresh air.");
  }
}

void readTempHumidity() {
  temper = TH02.ReadTemperature();
  Serial.print("Temperature: ");
  Serial.print(temper);
  Serial.println("C");

  humidity = TH02.ReadHumidity();
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.println("%");
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
