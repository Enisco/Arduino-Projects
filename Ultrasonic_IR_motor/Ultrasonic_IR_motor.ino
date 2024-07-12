//Arduino Human Following Robot
// You have to install the AFMotor and NewPing library Before Uploading the sketch
// You can find all the required libraris from arduino library manager.
// Contact me on instagram for any query(Insta Id : prateek.815)

//include the library code:
#include <NewPing.h>
#include <AFMotor.h>

#define LEFT 2            // Right IR sensor connected to analog pin A2 of Arduino Uno:
#define RIGHT 3           // Left IR sensor connected to analog pin A3 of Arduino Uno:
#define TRIGGER_PIN A2    // Trigger pin connected to analog pin A1 of Arduino Uno:
#define ECHO_PIN A3       // Echo pin connected to analog pin A0 of Arduino Uno:
#define MAX_DISTANCE 200  // Maximum ping distance:
#define IN4 12
#define IN3 11
// motor 1 control pins
#define IN2 10
#define IN1 9
int directn;

unsigned int distanceRead = 0;  //Variable to store ultrasonic sensor distance:
unsigned int Right_Value = 0;   //Variable to store Right IR sensor value:
unsigned int Left_Value = 0;    //Variable to store Left IR sensor value:
float setRange = 15.0, bufferRange = 60.0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);  //NewPing setup of pins and maximum distance:

//create motor objects
AF_DCMotor Motor1(1, MOTOR12_1KHZ);
AF_DCMotor Motor2(2, MOTOR12_1KHZ);
AF_DCMotor Motor3(3, MOTOR34_1KHZ);
AF_DCMotor Motor4(4, MOTOR34_1KHZ);

void setup() {  // the setup function runs only once when power on the board or reset the board:

  Serial.begin(115200);   //initailize serial communication at 9600 bits per second:
  pinMode(RIGHT, INPUT);  //set analog pin RIGHT as an input:
  pinMode(LEFT, INPUT);   //set analog pin RIGHT as an input:
                          //set output for motor 1 related pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  //set output for motor 2 related pins
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  // stop();
}

// the lope function runs forever
void loop() {
  delay(50);                       //wait 50ms between pings:
  distanceRead = sonar.ping_cm();  //send ping, get distance in cm and store it in 'distance' variable:
  Serial.print("distanceRead: ");
  Serial.println(distanceRead);  // print the distance in serial monitor:

  Right_Value = !digitalRead(RIGHT);  // read the value from Right IR sensor:
  Left_Value = !digitalRead(LEFT);    // read the value from Left IR sensor:

  Serial.print("RIGHT: ");
  Serial.println(Right_Value);  // print the right IR sensor value in serial monitor:
  Serial.print("LEFT: ");
  Serial.println(Left_Value);  //print the left IR sensor value in serial monitor:

  if ((distanceRead > 1) && (distanceRead < setRange)) {
    Serial.println("Stop");
    haltMotion();

  } else if ((distanceRead > setRange) && (distanceRead < bufferRange)) {
    Serial.println("Move Forward");
    forward();

  } else if (distanceRead > bufferRange) {

    if ((Right_Value == 1) && (Left_Value == 0)) {
      //Turn right
      Serial.println("Turn right");
      rightward();

    } else if ((Right_Value == 0) && (Left_Value == 1)) {
      //Turn left
      Serial.println("Turn left");
      leftward();

    } else {
      Serial.println("Nah");
    }
  } else {
    Serial.println("Do nothing");
    //haltMotion()
  }
}
void backward() {
  // motor 1 run Clockwise
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  // motor 2 run Anticlockwise
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}

void forward() {
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
  digitalWrite(IN4, LOW);
}

void leftward() {
  // motor 1 stop
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  // motor 2 run
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

void stop() {
  //Stop
  Serial.println("Stop");
  Motor1.setSpeed(0);   //define motor1 speed:
  Motor1.run(RELEASE);  //stop motor1:
  Motor2.setSpeed(0);   //define motor2 speed:
  Motor2.run(RELEASE);  //stop motor2:
  Motor3.setSpeed(0);   //define motor3 speed:
  Motor3.run(RELEASE);  //stop motor3:
  Motor4.setSpeed(0);   //define motor4 speed:
  Motor4.run(RELEASE);  //stop motor4:
}