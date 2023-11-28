#include <Arduino.h>

const int buttonPin = 2;    //  button is connected to pin

bool buttonState = 0;       // variable to hold the button state
bool Mode = 0;              // What mode is the light in?


void setup()
{
  pinMode(buttonPin, INPUT_PULLUP);    // Set the switch pin as input
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  if (!digitalRead(buttonPin)) // cheks if button is pressed (cheks if it's LOW, becouse PULLUP inverts signal: LOW = button pressed)
  {
    if (!buttonState) // same as: (buttonState == false) ---I made it a bit compact, but it may be confusinf to you
    {
      buttonState = true;
      Mode = !Mode; // this inverts button mode: If Mode was True - it will make it False and viseversa
    }
  }
  else buttonState = false;

  // blink LED
  digitalWrite(LED_BUILTIN, Mode); // remember: TRUE = HIGH = 1 and FALSE = LOW = 0 (You can use whatever You like)
  delay(5);
}