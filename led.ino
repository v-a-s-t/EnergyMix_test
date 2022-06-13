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
    elementAmount = float(fuelVisualiserPercent[i] * NUM_LEDS_IN_VISUAL) + 0.5;
    endingPoint = endingPoint + elementAmount;
    if (i > 0 && i < NUM_FUEL_VISUALISERS - 1) {
      //if needs padding inbetween
      for (int ledIndex = startingPoint; ledIndex < startingPoint + (PADDING / (NUM_FUEL_VISUALISERS - 1)); ledIndex++) {
        //make sure the padding leds are turning off
        leds[ledIndex] = CRGB(0, 0, 0);
      }
      //add padding to the starting point
      startingPoint = startingPoint + (PADDING / (NUM_FUEL_VISUALISERS - 1));
    }
    for (int j = startingPoint; j < endingPoint; j++) {
      leds[j] = CRGB(fuelColours[i][0], fuelColours[i][1], fuelColours[i][2]);
    }

    Serial.print(fuelVisual_labels[i]);
    Serial.print(": ");
    Serial.print(startingPoint + 1);
    Serial.print("----" );
    Serial.println(endingPoint);
  }
  FastLED.show();
}

void ledSend() {
  if (millis() - prevLed > ledTime) {
    prevLed = millis();
    FastLED.show();
  }
}

void ledStartupAnimation() {
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    for (int j = 0; j < TOTAL_LEDS; j++) {
      leds[j] = CRGB(fuelColours[i][0], fuelColours[i][1], fuelColours[i][2]);
      delay(30);
      FastLED.show();
    }
    delay(100);
  }
}
