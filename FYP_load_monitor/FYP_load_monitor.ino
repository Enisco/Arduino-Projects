
#include "EmonLib.h"
#include <SoftwareSerial.h>

EnergyMonitor emon1;            // Create an instance
SoftwareSerial mySerial(5, 6);  // RX, TX

void setup() {
  Serial.begin(115200);
  mySerial.begin(19200);

  emon1.voltage(2, 234.26, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon1.current(1, 111.1);        // Current: input pin, calibration.
}

void loop() {
  emon1.calcVI(20, 2000);  // Calculate all. No.of half wavelengths (crossings), time-out
  emon1.serialprint();     // Print out all variables (realpower, apparent power, Vrms, Irms, power factor)

  float realPower = emon1.realPower;          //extract Real Power into variable
  float apparentPower = emon1.apparentPower;  //extract Apparent Power into variable
  float powerFActor = emon1.powerFactor;      //extract Power Factor into Variable
  float supplyVoltage = emon1.Vrms;           //extract Vrms into Variable
  float Irms = emon1.Irms;                    //extract Irms into Variable

  String powerData = "LM-" + String(supplyVoltage) + "," + String(Irms) + "," + String(realPower) + "," + String(apparentPower) + "," + String(powerFActor);
  Serial.println(powerData);
  // Send to gateway middleman
  mySerial.println(powerData);
  delay(5000);
}
