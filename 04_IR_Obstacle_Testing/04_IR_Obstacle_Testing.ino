#include <Wire.h>

#define Addr 0x20

byte value;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("IR Obstacle Testing");
}

void loop() {
  PCF8574Write(0xC0 | PCF8574Read());  //set Pin High
  value = PCF8574Read() | 0x3F;        //read Pin
  if (value != 0xFF) {
    Serial.println("Obstacle Detected");
  } else {
    Serial.println("No Obstacle");
  }
}

void PCF8574Write(byte data) {
  Wire.beginTransmission(Addr);
  Wire.write(data);
  Wire.endTransmission();
}

byte PCF8574Read() {
  int data = -1;
  Wire.requestFrom(Addr, 1);
  if (Wire.available()) {
    data = Wire.read();
  }
  return data;
}
