
#define DECODE_NEC
#include <Arduino.h>

#include "PinDefinitionsAndMore.h"
#include <IRremote.hpp>

int temperatureC = 0, heartRate = 0, spO2 = 0;

void setup() {
  Serial.begin(115200);
  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // Start the receiver and if not 3. parameter specified, take LED_BUILTIN pin from the internal boards definition as default feedback LED
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);

  Serial.print(F("Ready to receive IR signals of protocols: "));
  printActiveIRProtocols(&Serial);
  Serial.println(F("at pin " STR(IR_RECEIVE_PIN)));
}

void loop() {
  if (IrReceiver.decode()) {

    IrReceiver.printIRResultShort(&Serial);
    IrReceiver.printIRSendUsage(&Serial);
    if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
      Serial.println(F("Received noise or an unknown (or not yet enabled) protocol"));
      // We have an unknown protocol here, print more info
      IrReceiver.printIRResultRawFormatted(&Serial, true);
    }
    Serial.println();

    IrReceiver.resume();  // Enable receiving of the next value

    if (IrReceiver.decodedIRData.address == 0x01) {
      temperatureC = IrReceiver.decodedIRData.command;
      Serial.print("temperatureC: " + String(temperatureC));
    } else if (IrReceiver.decodedIRData.address == 0x02) {
      heartRate = IrReceiver.decodedIRData.command;
      Serial.print(",  heartRate: " + String(heartRate));
    } else if (IrReceiver.decodedIRData.address == 0x03) {
      spO2 = IrReceiver.decodedIRData.command;
      Serial.print(",  spO2: " + String(spO2));
    }

    Serial.println();
  }
}
