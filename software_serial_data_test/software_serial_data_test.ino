
#include <SoftwareSerial.h>

SoftwareSerial mySerial(D5, D6);  // RX, TX

int count = 0;

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(115200);

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
}

void loop() {                                      // run over and over
  if (mySerial.available() > 0) {                  // Check if data is available to read
    String data = mySerial.readStringUntil('\n');  // Read the data until newline character '\n'

    Serial.print("Received data: ");
    Serial.println(data);
    count += 1;
    mySerial.println("Wemos Acknowledged: " + data + " - " + String(count));
  }
}
