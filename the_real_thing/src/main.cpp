/* Fill-in information from Blynk Device Info here */
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL4QDiILS43"
#define BLYNK_TEMPLATE_NAME "Kvetinac"
#define BLYNK_AUTH_TOKEN "OALjQD1FsXxNC3k9mMpDmtoBpav0vKWH"

#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "ESPNet";
char pass[] = "";

#define LED_PIN     15  // D8 pin - Wemos D1 Mini
#define LED_COUNT   12  // Number of LEDs in your NeoPixel ring
#define BRIGHTNESS  45  // LED brightness (0-255 range)

CRGB leds[LED_COUNT];

// Sensor pins
#define WATER_PWR 14   // D5 pin - Wemos D1 Mini
#define WATER_PIN A0    // A0 pin
#define MOISTURE_PWR 4  // D2 pin
#define MOISTURE_PIN 5  // D1 pin
#define WATER_PUMP 12   // D6 pin

/* Define how long the pump will run (3 seconds) */
#define PUMP_TIME 3000

/* Change these values based on your calibration values */
#define LVL_HIGH 520  // Define max value water level
#define LVL_LOW 470   // Define min value of water level

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Wi-Fi connected: ");
  Serial.println(WiFi.localIP());

  Blynk.config(BLYNK_AUTH_TOKEN);

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

/* Ultraviolet color function (You can adjust the values here to get the desired color) */
void ultravioletEffect() {
  CRGB uvColor(138, 43, 226);
  // Turn on all LEDs with the ultraviolet color
  fill_solid(leds, LED_COUNT, uvColor);
  FastLED.show();
}

void loop() {
  // Run the Blynk app.
  Blynk.run();
  // Run the LED function
  ultravioletEffect();
  
}
