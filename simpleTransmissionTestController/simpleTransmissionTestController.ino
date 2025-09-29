// SparkFun Wireless Joystick Kit - Transmitter
// Reads joystick on A2 (X) and A3 (Y), sends over XBee

const int joyX = A2;
const int joyY = A3;

void setup() {
  Serial1.begin(9600);  // Serial1 is the UART connected to the XBee
}

void loop() {
  int xVal = analogRead(joyX);
  int yVal = analogRead(joyY);

  // Map to bytes for easy transmission
  byte xMapped = map(xVal, 0, 1023, 0, 255);
  byte yMapped = map(yVal, 0, 1023, 0, 255);

  // Send joystick data
  Serial1.write(xMapped);
  Serial1.write(yMapped);

  delay(50);
}