#define PIN_LED 16 // D4

void setup() {
  // Initialize serial port
  Serial.begin(115200);
  Serial.println("Ready to receive commands.");

  // Configure D4 as output pin and start with LED OFF condition
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(PIN_LED, HIGH);
}

void loop() {

  // Check if serial data is available
  if (Serial.available() > 0) {

    // Read command from serial port
    String cmd = Serial.readStringUntil('\n');
    //Serial.println(cmd);

    if (cmd.equals("on")) {
      // Turn the LED ON
      digitalWrite(PIN_LED, LOW);
      Serial.println("LED is turned ON");
    }
    else {
      // Turn the LED OFF
      digitalWrite(PIN_LED, HIGH);
      Serial.println("LED is turned OFF");
    }
  }

  delay(100);
}
