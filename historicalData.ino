void updateHistoricalData(byte currentValues[]) {
  prefs.begin("historicalData");
  byte fuelArray[HISTORICAL_DATA_POINTS];
  if (firstHistoricalData) {
    //Replace the hour 0 reading with the latest reading on first power up
    for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
      prefs.getBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
      fuelArray[0] = currentValues[i];
      prefs.putBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
    }
  } else {
    //Ring buffer of historical data
    for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
      prefs.getBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
      byte last = fuelArray[HISTORICAL_DATA_POINTS - 1];
      for (byte j = HISTORICAL_DATA_POINTS - 1; j > 0; j--) {
        fuelArray[j] = fuelArray[j - 1];
      }
      fuelArray[0] = currentValues[i];
      prefs.putBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
    }
  }
  prefs.end();
}

void initHistoricalData() {
  prefs.begin("historicalData");
  byte fuelArray[HISTORICAL_DATA_POINTS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    prefs.putBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
  }
  prefs.end();
}

void printOutHistoricalData() {
  prefs.begin("historicalData");
  byte fuelArray[HISTORICAL_DATA_POINTS];
  Serial.println("Historical Data Print out. Hourly, starting now to 24 hours ago");
  Serial.println("-------------------------------------------------------------");
  Serial.println();
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    prefs.getBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
    Serial.print(fuelVisual_labels[i]);
    Serial.print(": " );
    Serial.println(fuelArray[0]);
    Serial.println();
    for (int j = 0; j > HISTORICAL_DATA_POINTS; j++) {
      for (int k = 0; k < fuelArray[j]; k++) {
        Serial.print("-");
      }
      Serial.println();
    }
    Serial.println();
  }
  prefs.end();
}

void historicalDataHandler() {
  if (historicalDataCounter % HISTORICAL_DATA_POINTS == 0) {
    updateHistoricalData(fuelUsageInPoints);
    firstHistoricalData = false;
  }
  historicalDataCounter++;
}
