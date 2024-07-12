// Sketch for push button sensor in pull-down resistor configuration

#define BUTTON_PIN 2
boolean preesedOnce = false;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
}

// void loop() {
  // checkPress();
  // if (checkPress()) {                      // Check if the button is pressed
  //   unsigned long startTime = millis();    // Get the current time
  //   while (millis() - startTime < 1000) {  // Check if 1 second has not elapsed yet
  //     if (checkPress()) {                  // Check if the button is pressed again
  //       Serial.println("Button Pressed Twice");
  //       // Handle the action for button pressed twice here
  //       break;  // Exit the loop once the button is pressed again
  //     }
  //   }
  // }
// }

// boolean checkPress() {
void loop() {
  if (digitalRead(BUTTON_PIN)) {  // switch closed?

    delay(40);  // switch debounce delay
    while (digitalRead(BUTTON_PIN))
      ;                               // wait for switch to open
    digitalWrite(LED_BUILTIN, HIGH);  // switch LED on
    // delay(2000);                      // leave LED on for period
    Serial.println("Button Pressed Once");
    // return true;
  } else {
    digitalWrite(LED_BUILTIN, LOW);  // switch LED off
    // return false;
  }
}
