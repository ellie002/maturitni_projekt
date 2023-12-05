#include <Adafruit_NeoPixel.h>
#define INPUT_PIN 8
#define NUM_OF_LED 12
Adafruit_NeoPixel rgbWS = Adafruit_NeoPixel(NUM_OF_LED, INPUT_PIN, NEO_GRB + NEO_KHZ800);
void setup() {
 rgbWS.begin();
 rgbWS.setBrightness(255); //max jas
}
void loop() {
 // Zobrazení bílé
 for (int i = 0; i < NUM_OF_LED; i++) {
 rgbWS.setPixelColor(i, rgbWS.Color(255, 255, 255));
 rgbWS.show();
 }
 delay(2000);

 //Zobrazení červené
 for (int i = 0; i < NUM_OF_LED; i++) {
 rgbWS.setPixelColor(i, rgbWS.Color(139, 0, 0));
 rgbWS.show();
 }
 delay(2000);
//Zobrazení zelené
 for (int i = 0; i < NUM_OF_LED; i++) {
 rgbWS.setPixelColor(i, rgbWS.Color(0, 128, 0));
 rgbWS.show();
 }
 delay(2000);
//Zobrazení modré
 for (int i = 0; i < NUM_OF_LED; i++) {
 rgbWS.setPixelColor(i, rgbWS.Color(0, 191, 255));
 rgbWS.show();
 }
 delay(2000);
}