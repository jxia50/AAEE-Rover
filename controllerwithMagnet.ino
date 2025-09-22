const int joyX = A2;
const int joyY = A3;
const int buttonD2 = 2; // movement
const int buttonD4 = 4; // magnet ON
const int buttonD9 = 9; // magnet OFF

void setup() {
  pinMode(buttonD2, INPUT_PULLUP);
  pinMode(buttonD4, INPUT_PULLUP);
  pinMode(buttonD9, INPUT_PULLUP);
  Serial1.begin(9600);
}

void loop() {
  int xVal = analogRead(joyX);
  int yVal = analogRead(joyY);
  int d2State = !digitalRead(buttonD2);
  int d4State = !digitalRead(buttonD4);
  int d9State = !digitalRead(buttonD9);

  byte xMapped = map(xVal, 0, 1023, 0, 255);
  byte yMapped = map(yVal, 0, 1023, 0, 255);

  // Send X, Y, D2, D4, D9
  Serial1.write(xMapped);
  Serial1.write(yMapped);
  Serial1.write(d2State);
  Serial1.write(d4State);
  Serial1.write(d9State);

  delay(50);
}
