String httpGETRequest(const char* serverName, const char* rootCert) {
  HTTPClient http;
  // Your Domain name with URL path or IP address with path
#ifdef USE_CA_CERT
  http.begin(serverName, rootCert); /*Removed CA cert to work with latest Arduino-esp32...*/
#else
  http.begin(serverName);
#endif
  http.setTimeout(20000);

  // Send HTTP POST request
  int httpResponseCode = http.GET();

  String payload = "{}";

  if (httpResponseCode == 200) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  }
  else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
    payload == "ERROR";
  }
  // Free resources
  http.end();

  return payload;
}
void setupParameters() {

  //Global brightness parameter
  const char* globalBrightnessHTML = "<br/><p> Global Brightness (Default 100): </p><input type='range' name='global' min='0' max='255' value='100' oninput='this.nextElementSibling.value = this.value'><output>100</output>";
  new (&GLOBALBRIGHTNESS) WiFiManagerParameter(globalBrightnessHTML); // custom html input
  wm.addParameter(&GLOBALBRIGHTNESS);

  const char* custom_radio_str1 = "<br/><p> Solar RGB: </p><input type='range' name='solarR' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='solarG' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='solarB' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'> <output>0</output>";
  const char* custom_radio_str2 = "<br/><p> Wind RGB: </p><input type='range' name='windR' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='windG' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='windB' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'> <output>0</output>";
  const char* custom_radio_str3 = "<br/><p> Nuclear RGB: </p><input type='range' name='nuclearR' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='nuclearG' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='nuclearB' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'> <output>0</output>";
  const char* custom_radio_str4 = "<br/><p> Hydro RGB: </p><input type='range' name='hydroR' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='hydroG' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='hydroB' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'> <output>0</output>";
  const char* custom_radio_str5 = "<br/><p> Biomass RGB: </p><input type='range' name='biomassR' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='biomassG' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='biomassB' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'> <output>0</output>";
  const char* custom_radio_str6 = "<br/><p> Gas RGB: </p><input type='range' name='gasR' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='gasG' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='gasB' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'> <output>0</output>";
  const char* custom_radio_str7 = "<br/><p> Coal RGB: </p><input type='range' name='coalR' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='coalG' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'><output>0</output><input type='range' name='coalB' min='0' max='255' value='0' oninput='this.nextElementSibling.value = this.value'> <output>0</output>";

  new (&RGBParams[0]) WiFiManagerParameter(custom_radio_str1);
  new (&RGBParams[1]) WiFiManagerParameter(custom_radio_str2);
  new (&RGBParams[2]) WiFiManagerParameter(custom_radio_str3);
  new (&RGBParams[3]) WiFiManagerParameter(custom_radio_str4);
  new (&RGBParams[4]) WiFiManagerParameter(custom_radio_str5);
  new (&RGBParams[5]) WiFiManagerParameter(custom_radio_str6);
  new (&RGBParams[6]) WiFiManagerParameter(custom_radio_str7);

  wm.addParameter(&RGBParams[0]);
  wm.addParameter(&RGBParams[1]);
  wm.addParameter(&RGBParams[2]);
  wm.addParameter(&RGBParams[3]);
  wm.addParameter(&RGBParams[4]);
  wm.addParameter(&RGBParams[5]);
  wm.addParameter(&RGBParams[6]);



  wm.setSaveParamsCallback(saveParamCallback);
  std::vector<const char *> menu = {"wifi", "info", "param", "sep", "restart", "exit"};
  wm.setMenu(menu);

}

void wifiSetup() {
  // WiFi manager

  WiFi.mode(WIFI_STA);

  // WiFi manager
  setupParameters();

  String wifiName = "EnergyMix-" + generateID();

  if (digitalRead(BUTTON) == LOW) {
    wm.startConfigPortal(wifiName.c_str(), "solar-wind-hydro");
  } else {

    bool res = wm.autoConnect(wifiName.c_str(), "solar-wind-hydro");
    if (!res) {
      ESP.restart();
    }
  }

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
}

String getParam(String name) {
  //read parameter from server, for customhmtl input
  String value;
  if (wm.server->hasArg(name)) {
    value = wm.server->arg(name);
  }
  return value;
}

void saveParamCallback() {
  Serial.println("[CALLBACK] saveParamCallback fired");
  delay(10);
  int r, g, b;
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    String r_, g_, b_;
    r_ = String(fuelVisual_labels[i]) + "R";
    g_ = String(fuelVisual_labels[i]) + "G";
    b_ = String(fuelVisual_labels[i]) + "B";
    r = getParam(r_).toInt();
    g = getParam(g_).toInt();
    b = getParam(b_).toInt();
    Serial.println(r);
    Serial.println(g);
    Serial.println( b);
    if (r == 0 && g == 0 && b == 0) {
      Serial.println("Parameters haven't been updated");
    } else {
      setColours(fuelVisual_labels[i], (byte)r, (byte)g, (byte)b);
    }
  }
  int gb = getParam("global").toInt();
  if (gb != 0) {
    setGlobalBrightness(gb);
  }
  getColours();
  ESP.restart();
}
