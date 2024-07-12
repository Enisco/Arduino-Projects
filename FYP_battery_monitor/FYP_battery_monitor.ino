// DC Current and Voltage Sensing

#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);  // RX, TX

int decimalPrecision = 2;  // decimal places for all values shown

int batteryInputCurrentPin = A0;                                          // Pin to measure Current Value from Charge Controller to battery
int batteryOutputCurrentPin = A2;                                         // Pin to measure Current Value from battery to inverter
int inputCalibrationPin = A1, outputCalibrationPin = A3;                  // Pin to calibrate offset middle value
float batteryInputManualOffset = 1.16, batteryOutputManualOffset = 0.00;  // Key in value to manually offset the initial value
float mVperAmpValue = 4.166667, voltageCalVal = 0.984251;                 // If using "Hall-Effect" Current Transformer, key in value using this formula: mVperAmp = maximum voltage range (in milli volt) / current rating of CT
                                                                          // 150A Hall-Effect Current Transformer rated at 150A, 2.5V +/- 0.625V, mVperAmp will be 625 mV / 150A = 4.166667 mV/A
float supplyVoltage = 5000;                                               // Analog input pin maximum supply voltage, ATMEGA328P is 5000mV
float offsetSampleRead = 0;                                               /* to read the value of a sample for offset purpose later */
float currentSampleRead = 0;                                              /* to read the value of a sample including currentOffset1 value*/
float currentLastSample = 0;                                              /* to count time for each sample. Technically 1 milli second 1 sample is taken */
float currentSampleSum = 0;                                               /* accumulation of sample readings */
float currentSampleCount = 0;                                             /* to count number of sample. */
float currentMean;                                                        /* to calculate the average value from all samples, in analog values*/
float RMSCurrentMean;                                                     /* square roof of currentMean, in analog values */
float voltageInPin = A4;
float FinalRMSCurrent, chargingCurrent, disChargingCurrent, batteryVoltage; /* the final RMS current reading*/

void setup() {
  Serial.begin(115200);
  mySerial.begin(19200);
  delay(500);
}

void loop() {
  chargingCurrent = readCurrent(batteryInputCurrentPin, inputCalibrationPin, batteryInputManualOffset);
  Serial.print(" <<<<<<< The Charging Current RMS value is: ");
  Serial.print(chargingCurrent, decimalPrecision);
  Serial.println(" A ");

  disChargingCurrent = readCurrent(batteryOutputCurrentPin, outputCalibrationPin, batteryOutputManualOffset);
  Serial.print("\n >>>>>>>  The Disharging Current RMS value is: ");
  Serial.print(disChargingCurrent, decimalPrecision);
  Serial.println(" A ");

  batteryVoltage = readDcVoltage();
  Serial.print("The battery voltage is: ");
  Serial.print(batteryVoltage, decimalPrecision);
  Serial.println(" V \n");

  sendDataToNode();

  delay(3000);
  Serial.println("\n Going again . . . . . . . \n");
}

void sendDataToNode() {
  String vals = "CM-" + String(chargingCurrent, decimalPrecision) + "," + String(disChargingCurrent, decimalPrecision) + "," + String(batteryVoltage, decimalPrecision);
  Serial.println(vals);
  // Send to Node via SS
  mySerial.println(vals);
}

float readDcVoltage() {
  int batSensorValue = analogRead(A4);
  float voltage = (batSensorValue * (100.0 / 1023.0)) * voltageCalVal;
  return voltage;
}

/* Read Current */
float readCurrent(int currentAnalogInputPin, int calibrationPin, float manualOffset) {

readC:  // Label to continue reading of current samples from

  if (micros() >= currentLastSample + 200) /* every 0.2 milli second taking 1 reading */
  {
    currentSampleRead = analogRead(currentAnalogInputPin) - analogRead(calibrationPin); /* read the sample value including offset value*/
    currentSampleSum = currentSampleSum + sq(currentSampleRead);                        /* accumulate total analog values for each sample readings*/
    currentSampleCount = currentSampleCount + 1;                                        /* to count and move on to the next following count */
    currentLastSample = micros();                                                       /* to reset the time again so that next cycle can start again*/
  }

  if (currentSampleCount == 4000) {
    currentMean = currentSampleSum / currentSampleCount;                                          /* average accumulated analog values*/
    RMSCurrentMean = sqrt(currentMean);                                                           /* square root of the average value*/
    FinalRMSCurrent = (((RMSCurrentMean / 1023) * supplyVoltage) / mVperAmpValue) - manualOffset; /* calculate the final RMS current*/
    if (FinalRMSCurrent <= 0.03)                                                                  /* if the current detected is less than or not up to 1%, set current value to 0A*/
    { FinalRMSCurrent = 0; }

    currentSampleSum = 0;   /* to reset accumulate sample values for the next cycle */
    currentSampleCount = 0; /* to reset number of sample for the next cycle */
    return FinalRMSCurrent;
  } else {
    goto readC;
  }
}
