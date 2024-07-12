
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2, vo = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  lcd.begin(16, 2);
  analogWrite(vo, 90);

  lcd.print("Pot Analog Read");
}

void loop() {
  lcd.setCursor(0, 1);
  double potReading = analogRead(A0);
  double voltage = (potReading /1023) * 5;
  
  lcd.print(String(voltage) + "V");
  delay(500);
}
