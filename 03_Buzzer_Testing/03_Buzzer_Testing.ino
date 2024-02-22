#include <Wire.h>

#define beep_on PCF8574Write(0xDF & PCF8574Read())
#define beep_off PCF8574Write(0x20 | PCF8574Read())

#define Addr 0x20

void setup() {
  Wire.begin();
}

void loop() {
  beep_on;
  delay(100);
  beep_off;
  delay(100);

  beep_on;
  delay(100);
  beep_off;
  delay(2000);

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
