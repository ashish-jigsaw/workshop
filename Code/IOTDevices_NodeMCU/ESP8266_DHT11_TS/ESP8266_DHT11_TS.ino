 /*@@AG
 * Read Temperature and Humidity values from DHT11 sensor and send
 * to ThingSpeak cloud service.
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

#include <Arduino.h>
#include <ESP8266HTTPClient.h>
#include "DHT.h"
#include <ESP8266WiFi.h>        // Include the Wi-Fi library

const char* ssid     = "AshishNote9";         // The SSID (name) of the Wi-Fi network you want to connect to
const char* password = "9886717078";     // The password of the Wi-Fi network

#define DHTPIN 14
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

void setup() {

  dht.begin();
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');
  
  WiFi.begin(ssid, password);             // Connect to the network
  Serial.print("Connecting to ");
  Serial.print(ssid); Serial.println(" ...");

  int i = 0;
  while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
    delay(1000);
    Serial.print(++i); Serial.print(' ');
  }

  Serial.println('\n');
  Serial.println("Connection established!");  
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());         // Send the IP address of the ESP8266 to the computer
}

void loop() {
    
        float h = dht.readHumidity();
        float t = dht.readTemperature();
        
        if (isnan(h) || isnan(t)) {
          Serial.println("Failed to read from DHT sensor!");
          delay(2000);
          return;
        }

        HTTPClient http;
        char url[1024];

        Serial.print("[HTTP] begin...\n");
        // configure server and url
        sprintf (url, "http://api.thingspeak.com/update?api_key=URFI77SB6L5SZ0VF&field1=%d&field2=%d", (int) t, (int) h);

        Serial.println(url);
        http.begin(url); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);

            // file found at server
            if(httpCode == HTTP_CODE_OK) {
                String payload = http.getString();
                Serial.println(payload);
            }
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();

    delay(16000);
}

