#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial gpsSerial(4, 3);

void setup() {
  Serial.begin(115200);
  gpsSerial.begin(4800);
  Serial.println(F("Starting"));
}

void loop() {
  while (gpsSerial.available() > 0) {
    gps.encode(gpsSerial.read());
    if (gps.location.isUpdated()) {
      // Latitude in degrees (double)
      Serial.print("Latitude= ");
      Serial.print(gps.location.lat(), 6);
      // Longitude in degrees (double)
      Serial.print(" Longitude= ");
      Serial.println(gps.location.lng(), 6);

      // Raw latitude in whole degrees
      Serial.print("Raw latitude = ");
      Serial.print(gps.location.rawLat().negative ? "-" : "+");
      Serial.println(gps.location.rawLat().deg);
      // ... and billionths (u16/u32)
      Serial.println(gps.location.rawLat().billionths);

      // Raw longitude in whole degrees
      Serial.print("Raw longitude = ");
      Serial.print(gps.location.rawLng().negative ? "-" : "+");
      Serial.println(gps.location.rawLng().deg);
      // ... and billionths (u16/u32)
      Serial.println(gps.location.rawLng().billionths);

      // Raw date in DDMMYY format (u32)
      Serial.print("Raw date DDMMYY = ");
      Serial.println(gps.date.value());

      // Raw time in HHMMSSCC format (u32)
      Serial.print("Raw time in HHMMSSCC = ");
      Serial.println(gps.time.value());

      // Hour (0-23) (u8)
      // Serial.print("Hour = ");
      // Serial.println(gps.time.hour());
      // // Minute (0-59) (u8)
      // Serial.print("Minute = ");
      // Serial.println(gps.time.minute());
      // // Second (0-59) (u8)
      // Serial.print("Second = ");
      // Serial.println(gps.time.second());

      // Raw altitude in centimeters (i32)
      Serial.print("Raw altitude in centimeters = ");
      Serial.println(gps.altitude.value());
      // Altitude in meters (double)
      Serial.print("Altitude in meters = ");
      Serial.println(gps.altitude.meters());
    }
  }
}