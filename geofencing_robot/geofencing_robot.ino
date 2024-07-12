
// IR pins
const int frontIrInterrupt = 0;
const int backIrInterrupt = 1;
const int frontIR = 2;
const int backIR = 3;
const int leftIR = 4;
const int rightIR = 5;

// motor control pins
#define IN4 12
#define IN3 11
#define IN2 10
#define IN1 9

unsigned long currentTime;
unsigned long previousTime = 0;
bool runAuto = false;

void setup() {
  pinMode(frontIR, INPUT);
  pinMode(backIR, INPUT);
  pinMode(leftIR, INPUT);
  pinMode(rightIR, INPUT);
  //set output for motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  Serial.begin(115200);
}

void loop() {

  currentTime = millis();

  int frontIRValue = digitalRead(frontIR);
  int backIRValue = digitalRead(backIR);
  int leftIRValue = digitalRead(leftIR);
  int rightIRValue = digitalRead(rightIR);

  if (frontIRValue == 1 || backIRValue == 1 || leftIRValue == 1 || rightIRValue) {
    if (frontIRValue == 1) {
      Serial.println("Line detected in Front, Stop motion");
      haltMotion();
      /*
    leftIRValue = digitalRead(leftIR);
    rightIRValue = digitalRead(rightIR);
    if (leftIRValue == 0) {  //No line in the back
      Serial.println("Turn left");
      leftward();
      delay(600);
      Serial.println("Stop");
      haltMotion();
    } else if (rightIRValue == 0) {
      Serial.println("Turn right");
      rightward();
      delay(600);
      Serial.println("Stop");
      haltMotion();
    } else {
      Serial.println("Reverse");
      backward();
      delay(300);
    }
    */
      Serial.println("Reverse");
      backward();
      delay(200);
      leftward();
      delay(650);
      forward();
      delay(500);
    }
    // Left Check
    leftIRValue = digitalRead(leftIR);
    if (leftIRValue == 1) {
      Serial.println("Turn right");
      rightward();
      delay(330);
      Serial.println("Forward");
      forward();
      delay(600);
      /*
    frontIRValue = digitalRead(frontIR);
    if (frontIRValue == 0) {
      Serial.println("Go front");
      forward();
      delay(600);
    } else {
      Serial.println("Go right");
      rightward();
      delay(600);
    }
    frontIRValue = digitalRead(frontIR);
    if (frontIRValue == 0) {
      Serial.println("Go front");
      forward();
      delay(1000);
    } else {
      Serial.println("Reverse");
      backward();
      delay(1000);
    }
    */
    }
    // Right Check
    rightIRValue = digitalRead(rightIR);
    if (rightIRValue == 1) {
      Serial.println("Turn left");
      leftward();
      delay(330);
      Serial.println("Forward");
      forward();
      delay(600);

      /*
    frontIRValue = digitalRead(frontIR);
    if (frontIRValue == 0) {
      Serial.println("Go front");
      forward();
      delay(600);
    } else {
      Serial.println("Go left");
      leftward();
      delay(600);
    }
    frontIRValue = digitalRead(frontIR);
    if (frontIRValue == 0) {
      Serial.println("Go front");
      forward();
      delay(1000);
    } else {
      Serial.println("Reverse");
      backward();
      delay(1000);
    }
    */
    }
    // Back Check
    backIRValue = digitalRead(backIR);
    if (backIRValue == 1) {
      Serial.println("Line detected at the back, Stop motion");
      haltMotion();
      /*
    leftIRValue = digitalRead(leftIR);
    rightIRValue = digitalRead(rightIR);
    if (leftIRValue == 0) {  //No line in the back
      Serial.println("Turn left");
      leftward();
      delay(600);
      Serial.println("Stop");
      haltMotion();
    } else if (rightIRValue == 0) {
      Serial.println("Turn right");
      rightward();
      delay(600);
      Serial.println("Stop");
      haltMotion();
    } else {
      Serial.println("Go front");
      forward();
      delay(1000);
    }
    */
      Serial.println("Reverse");
      forward();
      delay(600);
    }
  } else {
    if (runAuto == true) {
      forward();
      delay(200);
      haltMotion();
      delay(200);
      leftward();
      delay(1300);
      haltMotion();
      delay(200);
      rightward();
      delay(1500);
      haltMotion();
      delay(200);
      backward();
      delay(200);
      haltMotion();

      previousTime = currentTime;
      runAuto = false;
    }
  }

  if (currentTime - previousTime >= 5000) {
    // Do nothing
    runAuto = true;
    previousTime = currentTime;
  }
}

void forward() {
  // motor 1 run Clockwise
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // motor 2 run Anticlockwise
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void backward() {
  // motor 1 run Anticlock wise
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // motor 2 run Clockwise
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void rightward() {
  // motor 1 run
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  // motor 2 stop
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void leftward() {
  // motor 1 run
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // motor 2 stop
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}

void haltMotion() {
  // All motor stops
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
