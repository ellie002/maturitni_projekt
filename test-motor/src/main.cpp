#include <Arduino.h>
#define MOTORPIN 12

int mode = 0;

void setup() {
  pinMode(MOTORPIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(mode == 1){
    digitalWrite(MOTORPIN, LOW);
    mode = 0;
  }else{
    digitalWrite(MOTORPIN, HIGH);
    mode = 1;
  }
  delay(5000);
  Serial.println(mode);
}
