#include <FastLED.h>
#include <Arduino.h>
#include <PubSubClient.h>
#include <ESP8266WiFi.h>

#define wifi_ssid "Prokesova_laznet.cz"
#define wifi_password "cestmir70"
#define mqtt_server  "192.168.1.103" 
#define mqtt_user "mqtt-user"
#define mqtt_password "123456789"

#define moisture_level_topic "sensor/moisture_level"
#define water_level_topic "sensor/water_level"

#define LED_PIN     15  // D8 pin - Wemos D1 Mini
#define LED_COUNT   12  // Number of LEDs in your NeoPixel ring
#define BRIGHTNESS  45  // LED brightness (0-255 range)
#define BRIGHT_LED 150    // Brightness of the other LEDs
#define ANIMATION_DELAY 100 // Delay between LED changes in milliseconds
#define WATER_MIN   50

CRGB leds[LED_COUNT];

CRGB currentColor;

// Sensor pins
#define WATER_PWR 14   // D5 pin - Wemos D1 Mini
#define WATER_PIN A0    // A0 pin
#define MOISTURE_PWR 4  // D2 pin
#define MOISTURE_PIN 5  // D1 pin
#define WATER_PUMP 12   // D6 pin

#define PUMP_TIME 6000

void animateLights(unsigned long);
void lights(int, int, int);
void startSensors();
int waterSensor();
int moistureSensor();
void connectWifi();
void connectMQTT();

unsigned long currentTime;
unsigned long lastCheckSensor;
unsigned long wateringCheck;
unsigned long lastPublish;

const int delaySensor = 5000;
const int delaySensorValue = 500;
const int wateringDelay = 300000;
const int publishDelay = 10000; // Delay between publishing to MQTT. You can change it

bool sensors = false;
bool pump = false;

int lastWaterLevelCheck;
int waterLevel;
int moistureLevel;


WiFiClient Client;
PubSubClient client(Client);

void setup() {
  Serial.begin(9600);

  //connectWifi();
  
  client.setServer(mqtt_server, 1883);

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
  currentTime = millis();

  //if(WiFi.status()!=WL_CONNECTED) connectWifi();
  //if(!client.connected()) connectMQTT();

  if (currentTime-lastCheckSensor >= delaySensor) {
    lastCheckSensor = currentTime;
    sensors = true;
    startSensors();
  }else if(currentTime-lastCheckSensor >= delaySensorValue && sensors == true) {
    sensors = false;
    waterLevel = waterSensor();
    moistureLevel = moistureSensor();
  }

  if (currentTime-wateringCheck >= wateringDelay) {
    wateringCheck = currentTime;
    if (moistureLevel == LOW) {
      Serial.println("She is happy:)");
    }else {
      Serial.println("SHE DRY, NEED WATER");
      if (waterLevel >= WATER_MIN) {
        digitalWrite(WATER_PUMP, HIGH);
        Serial.println("Zapinam pumpu");
        pump = true;
      }
      
    }
  }

  if (currentTime-wateringCheck >= PUMP_TIME && currentTime-wateringCheck < wateringDelay && pump == true) {
    digitalWrite(WATER_PUMP, LOW);
    Serial.println("Vypinam pumpu");
    pump = false;
  }

  if (lastWaterLevelCheck != waterLevel) {
    lastWaterLevelCheck = waterLevel;
    if(waterLevel >= WATER_MIN) {
      Serial.println("Yea enough water baby");
    }else {
      Serial.println("ADD WATER NOW");
      Serial.println(waterLevel);
    }
  }

  if(currentTime-lastPublish >= publishDelay){
    lastPublish = currentTime;
    Serial.println("Publishing data to MQTT...");
    client.publish(water_level_topic, String(waterLevel).c_str());
    client.publish(moisture_level_topic, String(moistureLevel).c_str());
  }

  if(waterLevel < WATER_MIN) {
    lights(255, 0, 0);
  }else if(pump == true) {
    currentColor = CRGB(0, 15, 0);
    animateLights(currentTime);
  }else{
    lights(138, 43, 226);
  }

  client.loop();
}

void connectWifi() {
  WiFi.begin(wifi_ssid, wifi_password);

  Serial.println("Připojuji se k Wifi");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("Připojeno k WIFI");
}

void connectMQTT() {
  while(!client.connected() && WiFi.status() == WL_CONNECTED) {
    Serial.println("Am calling MQTT baby!");
    if (client.connect("esp8266", mqtt_user, mqtt_password)) {
      Serial.println("Připojeno k MQTT");
    }else {
    Serial.println("Připojení selhalo, zkouším opakované připojení");
    delay(5000);
    }
  }
}

void animateLights(unsigned long currentMillis) {
  static int currentLed = 0;
  static unsigned long lastLAnimTime = 0;

  if(currentMillis - lastLAnimTime >= ANIMATION_DELAY) {
    for(int i = 0; i < LED_COUNT; i++) {
      leds[i] = currentColor;
    }

    leds[currentLed] = CRGB(BRIGHT_LED, BRIGHT_LED, BRIGHT_LED);
    FastLED.show();
    currentLed = (currentLed + 1) % LED_COUNT;
    lastLAnimTime = currentMillis;
  }
}

void lights(int red, int green, int blue) {
    currentColor = CRGB(red, green, blue);
    fill_solid(leds, LED_COUNT, currentColor);
    FastLED.show();
}
void startSensors() {
  digitalWrite(WATER_PWR, HIGH);
  digitalWrite(MOISTURE_PWR, HIGH);
}

int waterSensor() {
  int sensorValue = analogRead(WATER_PIN);
  digitalWrite(WATER_PWR, LOW);
  return sensorValue;
}

int moistureSensor() {
  int sensorValue = digitalRead(MOISTURE_PIN);
  digitalWrite(MOISTURE_PWR, LOW);
  return sensorValue;
}
