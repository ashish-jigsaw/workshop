#include <ESP8266WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

// WiFi parameters
const char* ssid = "AshishNote9";
const char* password = "9886717078";

// Create an instance of the server
WiFiServer server(80);

void setup() {
  // Start Serial
  Serial.begin(115200);

  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  
  // Function to be exposed
  rest.function("led", ledControl);
  
  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("10");
  rest.set_name("esp8266");

  // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {
   // Handle REST calls
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  while(!client.available()){
    delay(1);
  }
  rest.handle(client);
}

// Custom function accessible by the API
int ledControl(String command) {

  // Get state from command
  int state = command.toInt();
  Serial.println("Changing LED state");
  Serial.println(state);
  if (state == 0)
    digitalWrite(16,HIGH);
   else
     digitalWrite(16,LOW);
  return state;
}
