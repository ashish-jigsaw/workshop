/*
 ESP8266 --> ThingSpeak Channel
 
 This sketch sends the value of DHT11 to a ThingSpeak channel
 using the ThingSpeak API (https://www.mathworks.com/help/thingspeak).
 Arduino library reference https://github.com/mathworks/thingspeak-arduino
 
 Requirements:
 
   * ESP8266 Wi-Fi Device
   * Arduino 1.8.8+ IDE
   * Additional Boards URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
   * Library: esp8266 by ESP8266 Community
   * Library: ThingSpeak by MathWorks
 
 ThingSpeak Setup:
 
   * Sign Up for New User Account - https://thingspeak.com/users/sign_up
   * Create a new Channel by selecting Channels, My Channels, and then New Channel
   * Enable one field
   * Enter SECRET_CH_ID in "secrets.h"
   * Enter SECRET_WRITE_APIKEY in "secrets.h"

 Setup Wi-Fi:
  * Enter SECRET_SSID in "secrets.h"
  * Enter SECRET_PASS in "secrets.h"
  
 Connections:
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
 * 
 */

#include "ThingSpeak.h"
#include "secrets.h"
#include "DHT.h"

#define DHTPIN 14     // what digital pin we're connected to
#define DHTTYPE DHT11   // DHT 11

// Initialize DHT sensor.
DHT dht(DHTPIN, DHTTYPE);

unsigned long myChannelNumber = SECRET_CH_ID;
const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

#include <ESP8266WiFi.h>

char ssid[] = SECRET_SSID;   // your network SSID (name)
char pass[] = SECRET_PASS;   // your network password
int keyIndex = 0;            // your network key index number (needed only for WEP)
WiFiClient  client;

void setup() {
  Serial.begin(115200);
  delay(100);
  dht.begin();

  WiFi.mode(WIFI_STA);

  ThingSpeak.begin(client);
}

void loop() {

  // Connect or reconnect to WiFi
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(SECRET_SSID);
    while (WiFi.status() != WL_CONNECTED) {
      WiFi.begin(ssid, pass); // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }

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

  // Write value to Field 1 of a ThingSpeak Channel
  //int httpCode = ThingSpeak.writeField(myChannelNumber, 1, t, myWriteAPIKey);

  ThingSpeak.setField (1, t);
  ThingSpeak.setField (2, h);
    
  int httpCode = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);

  if (httpCode == 200) {
    Serial.println("Channel write successful.");
  }
  else {
    Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
  }

  // Wait 20 seconds to uodate the channel again
  delay(16000);
}
