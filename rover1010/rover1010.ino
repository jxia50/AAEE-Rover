#include <Servo.h>

Servo leftMotor;
Servo rightMotor;

const int leftPin = 10;
const int rightPin = 11;
const int magnetPin = 7;

bool magnetState = false; // track current state

void setup() {
  Serial.begin(9600);  // XBee is on hardware Serial (pins 0/1)
  

  leftMotor.attach(leftPin);
  rightMotor.attach(rightPin);

  pinMode(magnetPin, OUTPUT);
  digitalWrite(magnetPin, LOW); // start OFF

  leftMotor.writeMicroseconds(1485);
  rightMotor.writeMicroseconds(1500);
}

void loop() {
  // Look for a start marker (255)
  if (Serial.available() >= 6) { // 1 start + 5 data bytes
    int startByte = Serial.read();
    if (startByte == 255) {
      int xVal    = Serial.read();
      int yVal    = Serial.read();
      int d2State = Serial.read();
      int d4State = Serial.read();
      int d9State = Serial.read();

      // --- Magnet update ---
      if (d4State == 1) magnetState = true;
      if (d9State == 1) magnetState = false;
      digitalWrite(magnetPin, magnetState ? HIGH : LOW);

      // --- Movement (only if D2 held) ---
      if (d2State == 1) {
        int speed = map(xVal, 0, 255, -200, 200);   // forward/back
        int turn  = map(yVal, 0, 255, 200, -200);   // left/right

        // Deadzone
        const int deadzone = 20;
        if (abs(speed) < deadzone) speed = 0;
        if (abs(turn)  < deadzone) turn  = 0;

        int leftSpeed  = constrain(speed + turn, -200, 200);
        int rightSpeed = constrain(speed - turn, -200, 200);

        leftMotor.writeMicroseconds(1485 - leftSpeed);
        rightMotor.writeMicroseconds(1500 - rightSpeed);
      } else {
        // Stop when D2 not held
        leftMotor.writeMicroseconds(1485);
        rightMotor.writeMicroseconds(1500);
      }
    }
  }
}
