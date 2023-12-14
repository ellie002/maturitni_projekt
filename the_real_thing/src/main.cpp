/* Fill-in information from Blynk Device Info here */
#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL4QDiILS43"
#define BLYNK_TEMPLATE_NAME "Kvetinac"
#define BLYNK_AUTH_TOKEN "OALjQD1FsXxNC3k9mMpDmtoBpav0vKWH"

#include <ESP8266WiFi.h>
#include <FastLED.h>
#include <BlynkSimpleEsp8266.h>

char ssid[] = "E_#&";
char pass[] = "fuckingpassword";

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

/* Define the time range for sensor measurements */
const int measurementInterval = 10000;
/* Time variable to keep track of the time range */
unsigned long previousMillis = 0;
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

int readWaterLevel();
int readMoisture();
void ultravioletEffect();

int Relay;

BLYNK_WRITE(V1) {
  Relay = param.asInt();

  if (Relay == 1) {
    Serial.println("Hello");
  } else {
    Serial.println("Off");
  }
}

void loop() {
  // Run the Blynk app.
  Blynk.run();
  // Run the LED function
  ultravioletEffect();

  /* Get current time. If the defined time range 
  has not passed, terminate the loop */
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis < measurementInterval) {
    return;
  }
  /* If the defined time range is complete, update the time */
  previousMillis = currentMillis;

  /* Get the value from the soil moisture sensor function 
  when the defined time range is complete */
  int MOISTURE_LEVEL = readMoisture();
  Blynk.virtualWrite(V0, MOISTURE_LEVEL);
  Serial.println(MOISTURE_LEVEL);

  /* If the soil moisture is HIGH, report everything as perfect! */
  /* The sensor value works inversely! */
  if (MOISTURE_LEVEL == LOW) {
    Serial.println("Moisture is perfect");

    /* If the soil moisture value is LOW, report it and 
  run the water pump motor for the defined pump time, 
  then stop thSSPUOpavavalue from the water level sensor function 
  when the defined time range is complete */
  int WATER_LEVEL = readWaterLevel();
  /* Convert the received water level value to the percent value */
  float percentLevel = map(WATER_LEVEL, 300, 600, 0, 100);
  Serial.print("Water Level: ");
  Serial.print(percentLevel);
  Serial.println(" %");
  /* Report and print the received water level status */
  if (WATER_LEVEL > LVL_HIGH) {
    Serial.println("Water level is too");
  } else if (WATER_LEVEL >= LVL_LOW && WATER_LEVEL < LVL_HIGH) {
    Serial.println("Water level is perfect");
  } else {
    Serial.println("Water level is low! Time to add water!");
  }

  /* It is the last line of the Loop Function, 
  the Loop Function is executed from the beginning... */
  Serial.println();
 }
}

/* This function returns the analog water level measurement */
int readWaterLevel(){
  digitalWrite(WATER_PWR, HIGH);            // Turn the sensor ON
  delay(10);                                // Allow power to settle
  int sensorValue = analogRead(WATER_PIN);  // Read the analog value from sensor
  digitalWrite(WATER_PWR, LOW);             // Turn the sensor OFF
  return sensorValue;                       // Return analog water value
}

/* This function returns the digital soil moisture measurement */
int readMoisture(){
  digitalWrite(MOISTURE_PWR, HIGH);             // Turn the sensor ON
  delay(10);                                    // Allow power to settle
  int sensorValue = digitalRead(MOISTURE_PIN);  // Read the digital value from sensor
  digitalWrite(MOISTURE_PWR, LOW);              // Turn the sensor OFF
  return sensorValue;                           // Return digital moisture value
}

/* Ultraviolet color function (You can adjust the values here to get the desired color) */
void ultravioletEffect() {
  CRGB uvColor(138, 43, 226);
  // Turn on all LEDs with the ultraviolet color
  fill_solid(leds, LED_COUNT, uvColor);
  FastLED.show();
}