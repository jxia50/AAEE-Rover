void setup() {
  Serial.begin(9600);  // this talks to XBee
  Serial.println("Receiver ready...");
}

void loop() {
  if (Serial.available() >= 2) {
    int xVal = Serial.read();
    int yVal = Serial.read();

    Serial.print("X: ");
    Serial.print(xVal);
    Serial.print("  Y: ");
    Serial.println(yVal);
  }
}