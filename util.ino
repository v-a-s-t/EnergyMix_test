void pinSetup() {
  Serial.begin(115200);
  // pinMode(BUTTON, INPUT_PULLUP);
  delay(500); //delay so can press the button

  touchConfig.setFeature(ButtonConfig::kFeatureClick);
  touchConfig.setFeature(ButtonConfig::kFeatureLongPress);
  touchConfig.setEventHandler(handleTouchEvent);
  touchConfig.setLongPressDelay(LONG_TOUCH);

  buttonTouch.check();
}

String generateID() {
  //https://github.com/espressif/arduino-esp32/issues/3859#issuecomment-689171490
  uint64_t chipID = ESP.getEfuseMac();
  uint32_t low = chipID % 0xFFFFFFFF;
  uint32_t high = (chipID >> 32) % 0xFFFFFFFF;
  String out = String(low);
  return  out;
}

void getColours() {
  prefs.begin("colours");
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i++) {
    prefs.getBytes(fuelVisual_labels[i], fuelColours[i], 3);
    for (byte j = 0; j < 3; j++) {
      if (fuelColours[i][j] != 0) {
        fuelColoursSet = true;
      }
    }
  }
  if (fuelColoursSet == false) {
    Serial.println("Colours haven't been set!");
    for (byte i = 0; i < NUM_FUEL_VISUALISERS; i++) {
      prefs.putBytes(fuelVisual_labels[i], defaultColours[i], 3);
      for (byte j = 0; j < 3; j++) {
        fuelColours[i][j] = defaultColours[i][j];
      }
    }
    Serial.println("Colours now set into prefs");
  } else {
    Serial.println("Colours RGB:");
    for (byte i = 0; i < NUM_FUEL_VISUALISERS; i++) {
      Serial.print(fuelVisual_labels[i]);
      Serial.print(": ");
      for (byte j = 0; j < 3; j++) {
        Serial.print(fuelColours[i][j]);
        Serial.print("   ");
      }
      Serial.println();
    }
  }
  prefs.end();
}

void setColours(String label, byte r, byte g, byte b) {
  prefs.begin("colours");
  byte rgb[3];
  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;
  prefs.putBytes(label.c_str(), rgb, 3);
  Serial.print(label);
  Serial.print(" RGB updated to ");
  Serial.print(r);
  Serial.print(" ");
  Serial.print(g);
  Serial.print(" ");
  Serial.println(b);
  prefs.end();
}

void setGlobalBrightness(int brightness) {
  prefs.begin("colours");
  prefs.putUInt("brightness", brightness);
  prefs.end();
}

int getGlobalBrightness() {
  int brightness;
  prefs.begin("colours");
  brightness = prefs.getUInt("brightness", 0);
  prefs.end();
  if (brightness == 0) {
    Serial.println("setting Global brightness in preferences to default");
    setGlobalBrightness(20);
  } else {
    if (brightness > MAXBRIGHTNESS) {
      brightness = MAXBRIGHTNESS;
      setGlobalBrightness(brightness);
    }
  }
  return brightness;
}

// button functions
void handleTouchEvent(AceButton* button, uint8_t eventType, uint8_t buttonState) {
  Serial.println(button->getId());

  switch (eventType) {
    case AceButton::kEventPressed:
      Serial.println("TOUCH: pressed");
      if (startup) {
        captivePortalAnimation();
        wm.startConfigPortal(wifiName.c_str(), "solar-wind-hydro");
      }
      break;
    case AceButton::kEventLongPressed:
      Serial.println("TOUCH: Long pressed");
      captivePortalAnimation();
      wm.startConfigPortal(wifiName.c_str(), "solar-wind-hydro");
      break;
    case AceButton::kEventReleased:
      Serial.println("TOUCH: released");
      break;
    case AceButton::kEventClicked:
      Serial.println("TOUCH: clicked");
      break;
  }
}

void startUpButtonHandler() {
  unsigned long millisNow = millis();
  while (millis() - millisNow < 3000) {
    buttonTouch.check();
  }
  startup = false;
}
