#include <Arduino.h>

int mode = 0;

void setup() {
  pinMode(6, OUTPUT);
}

void loop() {
  mode = !mode;
  digitalWrite(6, HIGH);
  delay(5000);
}
