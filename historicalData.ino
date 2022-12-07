void updateHistoricalData(byte currentValues[]) {
  prefs.begin("historicalData");
  if (firstHistoricalData) {
    //Replace the hour 0 reading with the latest reading on first power up
    for (int i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
      prefs.getBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
      fuelArray[0] = currentValues[i];
      prefs.putBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
    }
  } else {
    //Ring buffer of historical data
    for (int i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
      prefs.getBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
      int last = fuelArray[HISTORICAL_DATA_POINTS - 1];
      for (int j = HISTORICAL_DATA_POINTS - 1; j > 0; j--) {
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
  byte fuelArrayNew[HISTORICAL_DATA_POINTS] = {};
  for (int i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    prefs.putBytes(fuelVisual_labels[i], fuelArrayNew, HISTORICAL_DATA_POINTS);
  }
  prefs.end();
}

void populateHistoricalDataArray() {
  prefs.begin("historicalData");
  //Ring buffer of historical data
  Serial.println("getting historical data");
  for (int i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    prefs.getBytes(fuelVisual_labels[i], historicalDataPoints[i], HISTORICAL_DATA_POINTS);
  }
  prefs.end();
  Serial.println("got historical data");
}


void printOutHistoricalData() {
  prefs.begin("historicalData");
  Serial.println("Historical Data Print out. Hourly, starting now to 24 hours ago");
  Serial.println("-------------------------------------------------------------");
  Serial.println();
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    prefs.getBytes(fuelVisual_labels[i], fuelArray, HISTORICAL_DATA_POINTS);
    Serial.print(fuelVisual_labels[i]);
    Serial.print(": " );
    Serial.println(fuelArray[0]);
    Serial.println();
    for (int j = 0; j < HISTORICAL_DATA_POINTS; j++) {
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
  if (skipUpdate == false) {
    //if (historicalDataCounter == 0) {
    Serial.println("Saving new historical data!");
    updateHistoricalData(fuelUsageInPoints);
    firstHistoricalData = false;
    // }
    // historicalDataCounter++;
    // if (historicalDataCounter == HISTORICAL_DATA_COUNTS_PER_LOG) {
    //   historicalDataCounter = 0 ;
    // }
  }
}
