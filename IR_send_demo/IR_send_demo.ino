
#include <Arduino.h>
#include "PinDefinitionsAndMore.h"

#define DISABLE_CODE_FOR_RECEIVER
#include <IRremote.hpp>

#define DELAY_AFTER_SEND 500
#define DELAY_AFTER_LOOP 5000
#define USE_DEFAULT_FEEDBACK_LED_PIN false

void setup() {
  Serial.begin(115200);

  // Just to know which program is running on my Arduino
  Serial.println(F("START " __FILE__ " from " __DATE__ "\r\nUsing library version " VERSION_IRREMOTE));

  // IrSender.begin(); 
  IrSender.begin(DISABLE_LED_FEEDBACK);
  Serial.println(F("Send IR signals at pin 6"));
}

int intValue1 = 240;  // Replace these with your desired integer values
int intValue2 = 123;
int intValue3 = 205;
uint8_t convertedHexValue1, convertedHexValue2, convertedHexValue3;

uint8_t sAddress = 0x01;
uint8_t sCommand = 0x34;
uint8_t sRepeats = 0;

char hexValue1[4];
char hexValue2[4];
char hexValue3[4];

void loop() {

  // Convert INT to HEX with 3 bit length
  sprintf(hexValue1, "%03X", intValue1);
  sprintf(hexValue2, "%03X", intValue2);
  sprintf(hexValue3, "%03X", intValue3);

  // Convert HEX to uint8_t
  sscanf(hexValue1, "%hhx", &convertedHexValue1);
  sscanf(hexValue2, "%hhx", &convertedHexValue2);
  sscanf(hexValue3, "%hhx", &convertedHexValue3);


  Serial.println(F("Send Apple"));
  Serial.flush();

  // Send to the receiver in sequence
  IrSender.sendApple(0x01, convertedHexValue1, sRepeats);
  delay(DELAY_AFTER_SEND);
  IrSender.sendApple(0x02, convertedHexValue2, sRepeats);
  delay(DELAY_AFTER_SEND);
  IrSender.sendApple(0x03, convertedHexValue3, sRepeats);
  delay(DELAY_AFTER_SEND);

  sRepeats++;

  if (sRepeats > 4) {
    sRepeats = 4;
  }

  delay(3000);
}
