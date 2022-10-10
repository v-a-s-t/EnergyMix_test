/* TODO:
    - Update BMRS API to filter XML file with all types of power instead of separate"
    - Update LED distribution function to be use ints instead of floats.
    - Clean up
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
#define NUM_LEDS_IN_VISUAL 100
#define PADDING 21 // 3 leds inbetween each energy
#define OFFSET 1 // start offset
#define TOTAL_LEDS NUM_LEDS_IN_VISUAL+PADDING+OFFSET


//Button
#define CAPTOUCH T7
#define LONG_TOUCH 2000
int TOUCH_THRESHOLD = 60;
int TOUCH_HYSTERESIS = 20;
#include <AceButton.h>
using namespace ace_button;

//Timer
unsigned long lastTime = 0;
#define TIMER_DELAY 300000 //5 minutes

//Historical data
const int HISTORICAL_DATA_POINTS = 86400 / (TIMER_DELAY / 1000); //24 hours, every 5 minutes
const int HISTORICAL_DATA_COUNTS_PER_LOG = 60 / (TIMER_DELAY / 60000);
//int HISTORICAL_DATA_COUNTS_PER_LOG = 1;
int historicalDataCounter = 0;
bool firstHistoricalData = true;
byte fuelArray[HISTORICAL_DATA_POINTS];
byte historicalDataPoints[NUM_FUEL_VISUALISERS][HISTORICAL_DATA_POINTS];

// Touch settings and config
class CapacitiveConfig: public ButtonConfig {
  public:
    uint8_t _pin;
    uint16_t _threshold;
    CapacitiveConfig(uint8_t pin, uint16_t threshold) {
      _pin = pin;
      _threshold = threshold;
    }
    void setThreshold(uint16_t CapThreshold) {
      _threshold = CapThreshold;
    }
  protected:
    int readButton(uint8_t /*pin*/) override {
      uint16_t val = touchRead(_pin);
      return (val < _threshold) ? LOW : HIGH;
    }
};

CapacitiveConfig touchConfig(CAPTOUCH, TOUCH_THRESHOLD);
AceButton buttonTouch(&touchConfig);

void handleButtonEvent(AceButton*, uint8_t, uint8_t);

//Fuels used in visualisation
int LED_BRIGHTNESS = 40;
#define MAXBRIGHTNESS 100
float fuelVisualiserPercent[NUM_FUEL_VISUALISERS];
byte fuelUsageInPoints[NUM_FUEL_VISUALISERS];

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

CRGB leds[TOTAL_LEDS];


//captive portal variables
String wifiName;
bool isCaptivePortal = false;

void setup() {
  pinSetup();
  getColours();
  ledSetup();
  ledStartupAnimation();
  wifiSetup();
  //initHistoricalData();
}

void loop() {

  buttonTouch.check();
  if ((millis() - lastTime) > TIMER_DELAY || firstHistoricalData == true) {
    if (WiFi.status() == WL_CONNECTED) {
      getData();
      calculateEnergyConsumption();
      errorCheckData();
      historicalDataHandler();
      printOutHistoricalData();
      // displayEnergyConsumption();
      displayHistoricalEnergyConsumption();
     
    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
  displayUpdate();
  ledSend();
}
