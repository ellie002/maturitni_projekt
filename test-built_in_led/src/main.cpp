#include <Arduino.h>

bool Mode = 0; // What mode is the light in?

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  // blink LED
  digitalWrite(LED_BUILTIN, Mode); // remember: TRUE = HIGH = 1 and FALSE = LOW = 0 (You can use whatever You like)
  delay(5);
}