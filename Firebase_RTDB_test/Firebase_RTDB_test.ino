
#include <Arduino.h>
#include <ESP8266WiFi.h>

#include <Firebase_ESP_Client.h>
#include <addons/RTDBHelper.h>

#define WIFI_SSID "Hello_"
#define WIFI_PASSWORD "987654321"
#define DATABASE_URL "www.medilifi-a63d4-default-rtdb.firebaseio.com"
#define API_KEY "AIzaSyA04NpEkWHSWAFn62poqwXSpFt-UAP7B0E"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

unsigned long dataMillis = 0;
int count = 0;

#if defined(ARDUINO_RASPBERRY_PI_PICO_W)
WiFiMulti multi;
#endif

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to Wi-Fi");
  unsigned long ms = millis();

  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  config.signer.test_mode = true;

  Firebase.reconnectNetwork(true);
  fbdo.setBSSLBufferSize(128, 128);
  Firebase.begin(&config, &auth);
}

void loop() {
  if (millis() - dataMillis > 5000) {
    dataMillis = millis();
    Serial.printf("Set int... %s\n", Firebase.RTDB.setInt(&fbdo, "/test/int", count++) ? "ok" : fbdo.errorReason().c_str());
  }
}
