#include <SPI.h>

const int CS_PIN = 10;
int sensorValue;

void setup() {
  Serial.begin(9600);
  pinMode(CS_PIN, OUTPUT);
  digitalWrite(CS_PIN, HIGH);
  SPI.begin();
}

void loop() {
  digitalWrite(CS_PIN, LOW);
  sensorValue = SPI.transfer(0x00);
  digitalWrite(CS_PIN, HIGH);
  
  Serial.println(sensorValue);
  delay(50);
}
