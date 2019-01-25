//plot sine wave on serial monitor

void setup() {
Serial.begin(115200);
}

void loop() {
  for (int j=0;j < 360; j++){
    Serial.println(sin(j*(PI / 180)));
  }

}
