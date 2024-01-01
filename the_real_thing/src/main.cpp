#include <FastLED.h>

#define LED_PIN     15  // D8 pin - Wemos D1 Mini
#define LED_COUNT   12  // Number of LEDs in your NeoPixel ring
#define BRIGHTNESS  45  // LED brightness (0-255 range)
#define WATER_MIN   470

CRGB leds[LED_COUNT];

// Sensor pins
#define WATER_PWR 14   // D5 pin - Wemos D1 Mini
#define WATER_PIN A0    // A0 pin
#define MOISTURE_PWR 4  // D2 pin
#define MOISTURE_PIN 5  // D1 pin
#define WATER_PUMP 12   // D6 pin

/* Define how long the pump will run (3 seconds) */
#define PUMP_TIME 3000

void lights(int, int, int);
int waterSensor();
int moistureSensor();

unsigned long time;
unsigned long lastCheckSensor;
const unsigned long delaySensor = 5000;
unsigned long wateringCheck;
const unsigned long wateringDelay = 300000;

int lastWaterLevelCheck;

int waterLevel;
int moistureLevel;

void setup() {
  Serial.begin(9600);
  
  pinMode(WATER_PWR, OUTPUT);
  pinMode(WATER_PIN, INPUT);
  pinMode(MOISTURE_PWR, OUTPUT);
  pinMode(MOISTURE_PIN, INPUT);
  pinMode(WATER_PUMP, OUTPUT);

  /* Initially keep the sensors and motor OFF */
  digitalWrite(WATER_PWR, LOW);
  digitalWrite(MOISTURE_PWR, LOW);
  digitalWrite(WATER_PUMP, LOW);

  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();
  FastLED.clear();
}

void loop() {
  time = millis();
  if (time-lastCheckSensor >= delaySensor) {
    lastCheckSensor = time;
    waterLevel = waterSensor();
    moistureLevel = moistureSensor();
  }
  if (time-wateringCheck >= wateringDelay) {
    wateringCheck = time;
    if (moistureLevel == LOW) {
      Serial.println("Good enough :)");
    }else {
      Serial.println("Not good honey");
      digitalWrite(WATER_PUMP, HIGH);
    }
  }
  if (time-wateringCheck >= PUMP_TIME && time-wateringCheck < wateringDelay) {
    digitalWrite(WATER_PUMP, LOW);
  }
  if (lastWaterLevelCheck != waterLevel) {
    lastWaterLevelCheck = waterLevel;
    if(waterLevel >= WATER_MIN && waterLevel <= WATER_MAX) {
      Serial.println("Yea enough water baby");
      lights(37, 112, 15);
    }else {
      Serial.println("SHE DRY, NEED WATER");
      lights(247, 29, 5);
    }
  }
}

void lights(int red, int green, int blue) {
  CRGB color(red, green, blue);
  fill_solid(leds, LED_COUNT, color);
  FastLED.show();
}

int waterSensor() {
  digitalWrite(WATER_PWR, HIGH);
  int sensorValue = analogRead(WATER_PIN);
  digitalWrite(WATER_PWR, LOW);
  return sensorValue;
}

int moistureSensor() {
  digitalWrite(MOISTURE_PWR, HIGH);
  int sensorValue = digitalRead(MOISTURE_PIN);
  digitalWrite(MOISTURE_PWR, LOW);
  return sensorValue;
}
