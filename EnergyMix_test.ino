/* TODO:
    - Fix HTTP retry
    - Update BMRS API to filter XML file with all types of power instead of separate"
    - clean up functions and OO
*/

//#define XML
//#define USE_CA_CERT
#define NUM_FUEL_TYPES 19
#define NUM_FUEL_VISUALISERS 7
#include "certs.h"

#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiManager.h>
WiFiManager wm;
WiFiManagerParameter RGBParams[NUM_FUEL_VISUALISERS]; // global param ( for non blocking w params )
WiFiManagerParameter GLOBALBRIGHTNESS; // global param ( for non blocking w params )

#include <Preferences.h>
Preferences prefs;

//LED
#include <FastLED.h>
#define DATA_PIN 13
#define CLOCK_PIN 14
#define NUM_LEDS 40

//Fuels used in visualisation
int LED_BRIGHTNESS = 20;
float fuelVisualiserPercent[NUM_FUEL_VISUALISERS];




enum fuelVisuals {
  led_solar,
  led_wind,
  led_nuclear,
  led_hydro,
  led_biomass,
  led_gas,
  led_coal
};

byte fuelColours[NUM_FUEL_VISUALISERS][3];
bool fuelColoursSet = false;

const char * fuelVisual_labels[NUM_FUEL_VISUALISERS] = {
  "solar",
  "wind",
  "nuclear",
  "hydro",
  "biomass",
  "gas",
  "coal"
};

//RGB
byte defaultColours[NUM_FUEL_VISUALISERS][3] = {
  231, 221, 35, //solar e7dd23
  255, 255, 255,//wind ffffff
  205, 36, 37,//nuclear cd2425
  30, 29, 174,//hydro 1e1dae
  29, 173, 35,//biomass 1dad23
  216, 123, 36,//gas d87b24
  28, 24, 28//coal 1c181c
};

CRGB leds[NUM_LEDS];

#define BUTTON 0

unsigned long lastTime = 30000;
unsigned long timerDelay = 30000;

void setup() {
  pinSetup();
  getColours();
  ledSetup();
  ledStartupAnimation();
  wifiSetup();
}

void loop() {
  if ((millis() - lastTime) > timerDelay) {
    if (WiFi.status() == WL_CONNECTED) {
      getData();
      calculateEnergyConsumption();
      displayEnergyConsumption();
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  ledSend();
}
