/*
  AG: Modified to add serial prints and custom blink pattern
  ESP8266 Blink by Simon Peter
  Blink the blue LED on the ESP-01 module
  This example code is in the public domain

  The blue LED on the ESP-01 module is connected to GPIO1
  (which is also the TXD pin; so we cannot use Serial.print() at the same time)

  Note that this sketch uses LED to find the pin with the internal LED
*/

#define LED 16

void setup() {
  Serial.begin(115200);
  pinMode(LED, OUTPUT);     // Initialize the LED pin as an output
  delay(1000);
  Serial.println("Hello");
}

// the loop function runs over and over again forever
void loop() {
  Serial.println(LED, DEC);
    
  digitalWrite(LED, LOW);   // Turn the LED on (Note that LOW is the voltage level)
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(100);                      // Wait for a 100 ms
  digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(100);
  digitalWrite(LED, LOW);
  delay(100);
  digitalWrite(LED, HIGH);
  delay(1000);// Wait for a second
}
