#include <Wire.h>

#define Addr 0x20

#define beep_on PCF8574Write(0xDF & PCF8574Read())
#define beep_off PCF8574Write(0x20 | PCF8574Read())

byte value;

void setup() {
  Serial.begin(115200);
  Serial.println("Joystick Testing");
  Wire.begin();
}

void loop() {
  PCF8574Write(0x1F | PCF8574Read());
  value = PCF8574Read() | 0xE0;
  if (value != 0xFF) {
    beep_on;
    switch (value) {
      case 0xFE:
        Serial.println("up");
        break;
      case 0xFD:
        Serial.println("right");
        break;
      case 0xFB:
        Serial.println("left");
        break;
      case 0xF7:
        Serial.println("down");
        break;
      case 0xEF:
        Serial.println("center");
        break;
      default:
        Serial.println("unknown");
    }
    while (value != 0xFF) {
      PCF8574Write(0x1F | PCF8574Read());
      value = PCF8574Read() | 0xE0;
      delay(10);
    }
    beep_off;
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