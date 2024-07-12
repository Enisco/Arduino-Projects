
#include <ArduinoJson.h>  // https://github.com/bblanchon/ArduinoJson
#include <ESP8266Firebase.h>
#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#define _SSID "Hello_"
#define _PASSWORD "987654321"
#define REFERENCE_URL "https://esp32-cam-image-upload-default-rtdb.firebaseio.com/"

SoftwareSerial mySerial(D5, D6);  // RX, TX
Firebase firebase(REFERENCE_URL);
#define EEPROM_ADDRESS 0
int dataPointCount = 0;

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600);
  EEPROM.begin(512);

  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(1000);

  // Connect to WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to: ");
  Serial.println(_SSID);
  WiFi.begin(_SSID, _PASSWORD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("-");
  }

  Serial.println("");
  Serial.println("WiFi Connected");

  // Print the IP address
  Serial.print("IP Address: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  digitalWrite(LED_BUILTIN, HIGH);

  int dataRead;
  EEPROM.get(EEPROM_ADDRESS, dataRead);
  if (dataRead > 0) {
    dataPointCount = dataRead;
  }
}

void loop() {
  if (mySerial.available() > 0) {
    String data = mySerial.readStringUntil('\n');  // Read the data until newline character '\n'

    Serial.print("Received data: ");
    Serial.println(data);

    // Write some data to the realtime database.
    Serial.println(firebase.setString("atmospheredata/" + String(dataPointCount), data));

    EEPROM.put(EEPROM_ADDRESS, dataPointCount + 1);
    EEPROM.commit();

    Serial.println("Cycle done");
  }
}
