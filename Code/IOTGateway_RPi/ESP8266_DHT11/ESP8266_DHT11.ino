 /*@@AG
 * Display Temperature and Humidity values from DHT11 to OLED display
 * Note: This program is modified for ESP8266 and not Arduino. We
 * are not using Adafruit library, instead OLED library
 * 
 * Connections:
 * DHT 11
 * DHT 11 data out = Pin D5 = GPIO14
 * 
 * Connect pin 1 "+" (on the left) of the sensor to +5V
 * Connect pin 2 "out" of the sensor to whatever your DHTPIN is, D5 for NodeMCU
 * Connect pin 3 "-" (on the right) of the sensor to GROUND
 * 
 * Library dependency:
 * https://github.com/adafruit/DHT-sensor-library
 * https://github.com/adafruit/Adafruit_Sensor
 */

#include "DHT.h"

#define DHTPIN 14     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  //Serial.println("DHT11 test!");

  dht.begin();
}

void loop() {
  // Wait a few seconds between measurements.
  delay(3000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Compute heat index
  
  /*The heat index is an index that combines air temperature and relative humidity, 
   * to estimate a human-perceived equivalent temperature, as how hot it would feel 
   * if the humidity were some other value in the shade. 
   * The result is also known as the "felt air temperature" or "apparent temperature". 
   */
  
  float hic = dht.computeHeatIndex(t, h, false);

//  Serial.print("Humidity: ");
  Serial.println(h);
//  Serial.print(" %\t");
//  Serial.print("Temperature: ");
//  Serial.print(t);
//  Serial.print(" *C \t");
//  Serial.print("HI: ");
//  Serial.print(hic);
//  Serial.print(" *C \n");
}
