unsigned long prevLed, ledTime;

void ledSetup() {
  FastLED.addLeds<APA102, DATA_PIN, CLOCK_PIN, BGR>(leds, TOTAL_LEDS);
  FastLED.setBrightness(getGlobalBrightness());
  FastLED.clear();
  FastLED.show();
}

void displayEnergyConsumption() {
  int startingPoint = 0;
  int elementAmount = 0;
  int endingPoint = 0;
  Serial.println("Number of Leds per Element");
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    startingPoint = endingPoint;
    elementAmount = int((fuelVisualiserPercent[i] * NUM_LEDS_IN_VISUAL) + 0.5);
    endingPoint = endingPoint + elementAmount;
    if (i > 0 && i < NUM_FUEL_VISUALISERS) {
      //if needs padding inbetween
      for (int ledIndex = startingPoint; ledIndex < startingPoint + (PADDING / NUM_FUEL_VISUALISERS); ledIndex++) {
        //make sure the padding leds are turning off
        leds[ledIndex + OFFSET] = CRGB(0, 0, 0);
      }
      //add padding to the starting point
      startingPoint = startingPoint + (PADDING / NUM_FUEL_VISUALISERS);
      endingPoint = endingPoint + (PADDING / NUM_FUEL_VISUALISERS);
    }
    for (int j = startingPoint; j < endingPoint; j++) {
      leds[j + OFFSET] = CRGB(fuelColours[i][0], fuelColours[i][1], fuelColours[i][2]);
    }

    Serial.print(fuelVisual_labels[i]);
    Serial.print(": ");
    Serial.print(startingPoint + 1);
    Serial.print("----" );
    Serial.println(endingPoint);
  }
  FastLED.show();
}

void displayHistoricalEnergyConsumption() {
  int startingPoint = 0;
  int elementAmount = 0;
  int endingPoint = 0;
  populateHistoricalDataArray();
  for(int i = 0; i < TOTAL_LEDS; i++){
    leds[i] = CRGB(0, 0, 0);
  }
  for (int k = HISTORICAL_DATA_POINTS - 1; k > 0; k --) {
    startingPoint = 0;
    elementAmount = 0;
    endingPoint = 0;
    Serial.println("Number of Leds per Element");
    for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
      startingPoint = endingPoint;
      elementAmount = historicalDataPoints[i][k];
      endingPoint = endingPoint + elementAmount;
      if (endingPoint > startingPoint) {
        if (i > 0 && i < NUM_FUEL_VISUALISERS) {
          //if needs padding inbetween
          for (int ledIndex = startingPoint; ledIndex < startingPoint + (PADDING / NUM_FUEL_VISUALISERS); ledIndex++) {
            //make sure the padding leds are turning off
            leds[ledIndex + OFFSET] = CRGB(0, 0, 0);
          }
          //add padding to the starting point
          startingPoint = startingPoint + (PADDING / NUM_FUEL_VISUALISERS);
          endingPoint = endingPoint + (PADDING / NUM_FUEL_VISUALISERS);
        }
        for (int j = startingPoint; j < endingPoint; j++) {
          leds[j + OFFSET] = CRGB(fuelColours[i][0], fuelColours[i][1], fuelColours[i][2]);
        }
      } else {
        
      }

      Serial.print(fuelVisual_labels[i]);
      Serial.print(": ");
      Serial.print(startingPoint + 1);
      Serial.print("----" );
      Serial.println(endingPoint);
    }
    FastLED.show();
    delay(10);
  }
}


void ledSend() {
  if (millis() - prevLed > ledTime) {
    prevLed = millis();
    FastLED.show();
  }
}

unsigned long prevDisplay;
unsigned long displayTime = 10000;

void displayUpdate() {
  if (millis() - prevDisplay > displayTime) {
    prevDisplay = millis();
    displayHistoricalEnergyConsumption();
  }
}

void ledStartupAnimation() {
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    for (int j = OFFSET; j < TOTAL_LEDS; j++) {
      leds[j] = CRGB(fuelColours[i][0], fuelColours[i][1], fuelColours[i][2]);
      delay(10);
      FastLED.show();
    }
    delay(100);
  }
}

void captivePortalAnimation() {
  for (int j = OFFSET; j < TOTAL_LEDS; j++) {
    leds[j] = CRGB(20, 20, 20);
    delay(10);
    FastLED.show();
  }
  FastLED.clear();
}
