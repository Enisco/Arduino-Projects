
/************************************************/
//void forward(), backward(), leftward(), rightward(), turnAround(), haltMotion();

// motor 2 control pins
// #define ENB 3
#define IN4 12
#define IN3 11
// motor 1 control pins
#define IN2 10
#define IN1 9
// #define ENA 6

void setup() {
  Serial.begin(115200);
  //set output for motor 1 related pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //set output for motor 2 related pins
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
}

void loop() {

  forward();
  delay(2000);
  haltMotion();
  delay(1000);
  backward();
  delay(2000);
  haltMotion();
  delay(1000);
  rightward();
  delay(2000);
  haltMotion();
  delay(1000);
  leftward();
  delay(2000);
  haltMotion();
  delay(2000);
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
