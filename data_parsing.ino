/*
  solar = solar
  gas = ocgt + ccgt
  oil = oil
  coal = coal
  nuclear = nuclear
  wind = wind
  hydro = ps + npshyd
  biomass = biomass
  internationalPowerSources = intfr + intirl + intned + intew + intne + intelec + intifa2 + intnsl
*/
enum fuelTypes {
  ccgt,
  ocgt,
  oil,
  coal,
  nuclear,
  wind,
  ps,
  npshyd,
  other,
  intfr,
  intirl,
  intned,
  intew,
  biomass,
  intnem,
  intelec,
  intifa2,
  intnsl,
  solar
};

#include <ArduinoJson.h>
#ifdef XML
#include "src/tinyxml2/tinyxml2.h"
using namespace tinyxml2;
XMLDocument xmlDocument;
#else
#include <CSV_Parser.h>
char    **FuelNames;
int32_t *fuelConsumption;
#endif

String data;
float solarMW;
//https://api0.solar.sheffield.ac.uk/pvlive/api/v4/pes/0
const char* serverSolar = "https://api0.solar.sheffield.ac.uk/pvlive/api/v4/pes/0";
#ifdef XML
String serverBMRS = "https://api.bmreports.com/BMRS/FUELINSTHHCUR/V1?APIKey=e0bs40fsmoq6elz&FuelType=";
String serverBMRS_end = "&ServiceType=xml";
String serverBMRSALL = "https://api.bmreports.com/BMRS/FUELINSTHHCUR/V1?APIKey=e0bs40fsmoq6elz&ServiceType=xml";
#else
const char* serverBMRS_CSV = "https://api.bmreports.com/BMRS/FUELINSTHHCUR/V1?APIKey=e0bs40fsmoq6elz&ServiceType=csv";
#endif

// 8 fuels from BMRS and 1 from solar report
String BMRS_fuelTypes[NUM_FUEL_TYPES - 1] = {"CCGT", "OCGT", "OIL", "COAL", "NUCLEAR", "WIND", "PS", "NPSHYD", "OTHER", "INTFR", "INTIRL", "INTNED", "INTEW", "BIOMASS", "INTNEM", "INTELEC", "INTIFA2", "INTNSL"};
uint32_t fuel_MW[NUM_FUEL_TYPES];
int32_t totalEnergy;
float fuel_percent[NUM_FUEL_TYPES];

uint32_t parseJSONtoInt(String dataIn) {
  StaticJsonDocument<384> doc;

  DeserializationError error = deserializeJson(doc, dataIn);

  if (error) {
    Serial.print("deserializeJson() failed: ");
    Serial.println(error.c_str());
    return 0;
  }

  JsonArray data_0 = doc["data"][0];
  uint32_t data_0_0 = data_0[0]; // 0
  const char* data_0_1 = data_0[1]; // "2022-02-24T10:30:00Z"
  uint32_t data_0_2 = data_0[2]; // 1
  //set24hrPreviousTime(data_0_1);

  JsonArray meta = doc["meta"];
  const char* meta_0 = meta[0]; // "ggd_id"
  const char* meta_1 = meta[1]; // "datetime_gmt"
  const char* meta_2 = meta[2]; // "n_ggds"
  //const char* meta_3 = meta[3]; // "generation_mw"

  return data_0_2;
}
#ifdef XML
int parseXMLtoInt(String dataIn) {
  if (xmlDocument.Parse(dataIn.c_str()) != XML_SUCCESS) {
    Serial.println("Error");
    return 0;
  }
  const char* output = xmlDocument.FirstChildElement( "response" )->FirstChildElement( "responseBody" )->FirstChildElement( "responseList" )->FirstChildElement( "item" )->FirstChildElement( "currentMW" )->GetText();
  return atoi(output);
}

int parseALLXMLtoInt(String dataIn) {
  if (xmlDocument.Parse(dataIn.c_str()) != XML_SUCCESS) {
    Serial.println("Error");
    return 0;
  }
  tinyxml2::XMLElement *levelElement = xmlDocument.FirstChildElement( "response" )->FirstChildElement( "responseBody" )->FirstChildElement( "responseList" );
  //const char* output = xmlDocument.FirstChildElement( "response" )->FirstChildElement( "responseBody" )->FirstChildElement( "responseList" )->FirstChildElement( "item" )->FirstChildElement( "currentMW" )->GetText();
  tinyxml2::XMLElement* child;
  for (child = levelElement->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
  {
    const char* out = child->FirstChildElement("fuelType")->GetText();
    Serial.println(out);
    for (byte i = 0; i < NUM_FUEL_TYPES - 1; i ++) {
      if (BMRS_fuelTypes[i] == String(out)) {
        Serial.println("match xml to data");
        fuel_MW[i] = atoi(child->FirstChildElement("currentMW")->GetText());
        Serial.print(out);
        Serial.print(": ");
        Serial.println(fuel_MW[i]);
      }
    }
    // do something with each child element
  }
  return 1;
}
#endif

bool skipUpdate = false;
#ifdef XML
void XMLBMRS() {
  //Parse XML data from BMRS
  /*for (byte i = 0; i < NUM_FUEL_TYPES - 1; i ++) {
    String serverOut = serverBMRS + BMRS_fuelTypes[i];
    serverOut = serverOut + serverBMRS_end;
    data = httpGETRequest(serverOut.c_str(), root_ca_bmrs);
    if (data == "ERROR") {
      //quick retry...
      delay(2000);
      data = httpGETRequest(serverOut.c_str(), root_ca_bmrs);
    }
    // Serial.println(data);
    fuel_MW[i] = parseXMLtoInt(data);
    }
  */
  String serverOut = serverBMRSALL;
  data = httpGETRequest(serverOut.c_str(), root_ca_bmrs);
  if (data == "ERROR") {
    //quick retry...
    Serial.println("retrying to send request");
    delay(2000);
    data = httpGETRequest(serverOut.c_str(), root_ca_bmrs);
  }
  if (parseALLXMLtoInt(data) != 0) {
    Serial.println("XML Parse success!");
  } else {
    Serial.println("XML Parse Fail");
  }
}
#else
void CSVBMRS() {
  skipUpdate = false;
  //Parse CSV from BMRS
  data = httpGETRequest(serverBMRS_CSV, root_ca_bmrs);
  if (data == "ERROR") {
    //quick retry...
    Serial.println("Delay and retry");
    delay(20000);
    data = httpGETRequest(serverBMRS_CSV, root_ca_bmrs);
  }
  if (data  != "ERROR") {
    parseCSV(data);
    if (skipUpdate == false) {
      for (byte i = 0; i < NUM_FUEL_TYPES - 1; i ++) {
        fuel_MW[i] = getFuelValue(i);
      }
    } else {
      for (byte i = 0; i < NUM_FUEL_TYPES - 1; i ++) {
        fuel_MW[i] = 0;
      }
    }
  } else {
    Serial.println("Skipping update this time as there was an error with the request");
    for (byte i = 0; i < NUM_FUEL_TYPES - 1; i ++) {
      fuel_MW[i] = 0;
    }
    skipUpdate = true;
  }
}
#endif

void JSONSOLAR() {
  if (skipUpdate == false) {
    //Parse JSON from solar
    data = httpGETRequest(serverSolar, root_ca_solar);
    if (data == "ERROR") {
      //quick retry...
      delay(2000);
      data = httpGETRequest(serverSolar, root_ca_solar);
    }
    if (data != "ERROR") {
      // Serial.println(data);
      fuel_MW[NUM_FUEL_TYPES - 1] = parseJSONtoInt(data);
    } else {
      for (byte i = 0; i < NUM_FUEL_TYPES; i ++) {
        fuel_MW[i] = 0;
        skipUpdate = true;
      }
    }
  } else {
    for (byte i = 0; i < NUM_FUEL_TYPES; i ++) {
      fuel_MW[i] = 0;
    }
  }
}


#ifndef XML
void parseCSV(String dataIn) {
  // data = httpGETRequest("https://api.bmreports.com/BMRS/FUELINSTHHCUR/V1?APIKey=e0bs40fsmoq6elz&ServiceType=csv", root_ca_bmrs);
  if (dataIn.length() > 100) {
    int indexofFirstLine = dataIn.indexOf('\n');
    dataIn.remove(0, indexofFirstLine + 1);
    int indexofLastLine = dataIn.lastIndexOf('\n');
    dataIn.remove(indexofLastLine, dataIn.length() - indexofLastLine);
    dataIn.trim();
    Serial.println(dataIn);
    CSV_Parser cp(dataIn.c_str(), /*format*/ "ssLfLfLf", false);
    cp.print();

    FuelNames =         (char**)cp[1];
    fuelConsumption =          (int32_t*)cp[2];
  } else {
    skipUpdate = true;
  }
}

uint32_t getFuelValue(int id) {
  Serial.print(FuelNames[id]);
  Serial.print(": ");
  Serial.println(fuelConsumption[id]);
  return (fuelConsumption[id]);
}
#endif

void calculateEnergyConsumption() {
  //solar, wind, nuclear, hydro, biomass, gas, coal
  if (skipUpdate == false) {
    totalEnergy = 0;
    totalEnergy = fuel_MW[ccgt] + fuel_MW[ocgt] + fuel_MW[coal] + fuel_MW[nuclear] + fuel_MW[wind] + fuel_MW[ps] +  fuel_MW[npshyd] + fuel_MW[biomass] + fuel_MW[solar];
    fuelVisualiserPercent[led_solar] = float(fuel_MW[solar]) / float(totalEnergy);
    fuelVisualiserPercent[led_wind] = float(fuel_MW[wind]) / float(totalEnergy);
    fuelVisualiserPercent[led_nuclear] = float(fuel_MW[nuclear]) / float(totalEnergy);
    fuelVisualiserPercent[led_hydro] = float(fuel_MW[npshyd] + fuel_MW[ps]) / float(totalEnergy);
    fuelVisualiserPercent[led_biomass] =  float(fuel_MW[biomass]) / float(totalEnergy);
    fuelVisualiserPercent[led_gas] = float(fuel_MW[ocgt] + fuel_MW[ccgt]) / float(totalEnergy);
    fuelVisualiserPercent[led_coal] = float(fuel_MW[coal]) / float(totalEnergy);
    Serial.print("Total Energy: ");
    Serial.println(totalEnergy);
    Serial.println();
    Serial.println("Fuel Breakdowns in Percentages");
    for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
      Serial.print(fuelVisual_labels[i]);
      Serial.print(": ");
      fuelUsageInPoints[i] = int((fuelVisualiserPercent[i] * 100.0) + 0.5);
      Serial.print(fuelUsageInPoints[i]);
      Serial.println("%");
      Serial.println();
    }
  }
}

void calculateAllEnergyConsumption() {
  totalEnergy = 0;
  for (byte i = 0; i < NUM_FUEL_TYPES; i ++) {
    totalEnergy = totalEnergy + fuel_MW[i];
  }
  for (byte i = 0; i < NUM_FUEL_TYPES; i ++) {
    fuel_percent[i] = float(fuel_MW[i]) / float(totalEnergy);
  }
  Serial.print("Total Energy: ");
  Serial.println(totalEnergy);
  Serial.println("Fuel Breakdowns");
  Serial.println();

  for (byte i = 0; i < NUM_FUEL_TYPES - 1; i ++) {
    Serial.print(BMRS_fuelTypes[i]);
    Serial.print(": ");
    Serial.print(uint32_t(fuel_percent[i] * 100));
    Serial.print("%");
    Serial.println();
    uint32_t line = int(fuel_percent[i] * 100);
    for (int i = 0 ; i < line; i++) {
      Serial.print("-");
    }
    Serial.println();
  }
  Serial.print("SOLAR");
  Serial.print(": ");
  Serial.print(int(fuel_percent[NUM_FUEL_TYPES - 1] * 100));
  Serial.print("%");
  Serial.println();
  int line = int(fuel_percent[NUM_FUEL_TYPES - 1] * 100);
  for (int i = 0 ; i < line; i++) {
    Serial.print("-");
  }
  Serial.println();

  Serial.println();
}

void getData() {
#ifdef XML
  XMLBMRS();
#else
  CSVBMRS();
#endif
  JSONSOLAR();
}

void errorCheckData() {
  Serial.println("error checking");
  for (byte i = 0; i < NUM_FUEL_VISUALISERS; i ++) {
    if (fuelUsageInPoints[i] < 0 || fuelUsageInPoints[i] > 100) {
      for (byte j = 0; j < NUM_FUEL_VISUALISERS; j ++) {
        fuelUsageInPoints[j] = 0;
        Serial.println("found data error!");
      }
      skipUpdate = true;
    }
  }
  Serial.println("error check finished");
}

void dataHandler() {
  if (((millis() - lastTime) > TIMER_DELAY) || firstHistoricalData == true) {
    if (WiFi.status() == WL_CONNECTED) {
      getData();
      calculateEnergyConsumption();
      errorCheckData();
      historicalDataHandler();
      printOutHistoricalData();
      //displayEnergyConsumption();
      //displayHistoricalEnergyConsumption();

    } else {
      Serial.println("WiFi Disconnected");
    }
    lastTime = millis();
  }
}
