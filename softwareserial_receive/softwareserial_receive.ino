
#include <SoftwareSerial.h>

SoftwareSerial mySerial(5, 6);  // RX, TX
int count = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(19200);
  delay(2000);
  mySerial.println("Testing from Nano");
  Serial.print("Sent 'Testing from Nano'");
}

void loop() {                                      // run over and over
  if (mySerial.available() > 0) {                  // Check if data is available to read
    String data = mySerial.readStringUntil('\n');  // Read the data until newline character '\n'

    Serial.print("Received data: ");
    Serial.println(data);

    delay(2000);
    count += 1;
    mySerial.println("Nano greeting again - " + String(count));
  }
}
