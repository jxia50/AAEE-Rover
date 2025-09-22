#include <Servo.h>

Servo leftMotor;
Servo rightMotor;

const int leftPin = 10;
const int rightPin = 11;
const int magnetPin = 7;

bool magnetState = false; // track current state

void setup() {
  Serial.begin(9600);

  leftMotor.attach(leftPin);
  rightMotor.attach(rightPin);

  pinMode(magnetPin, OUTPUT);
  digitalWrite(magnetPin, LOW); // start OFF

  leftMotor.writeMicroseconds(1500);
  rightMotor.writeMicroseconds(1500);
}

void loop() {
  if (Serial.available() >= 5) { // X, Y, D2, D4, D9
    int xVal = Serial.read();
    int yVal = Serial.read();
    int d2State = Serial.read();
    int d4State = Serial.read();
    int d9State = Serial.read();

    // Update magnet state
    if (d4State == 1) {
      magnetState = true;
    } 
    if (d9State == 1) {
      magnetState = false;
    }

    // Apply magnet output
    digitalWrite(magnetPin, magnetState ? HIGH : LOW);

    // Robot movement (only if D2 held)
    if (d2State == 1) {
      int speed = map(xVal, 0, 255, -200, 200);
      int turn  = map(yVal, 0, 255, 200, -200);

      int leftSpeed  = speed + turn;
      int rightSpeed = speed - turn;

      leftSpeed  = constrain(leftSpeed, -200, 200);
      rightSpeed = constrain(rightSpeed, -200, 200);

      leftMotor.writeMicroseconds(1500 - leftSpeed);
      rightMotor.writeMicroseconds(1500 - rightSpeed);
    } else {
      leftMotor.writeMicroseconds(1500);
      rightMotor.writeMicroseconds(1500);
    }
  }
}
