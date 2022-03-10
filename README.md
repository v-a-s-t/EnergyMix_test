# EnergyMix_test

### Outline 

EnergyMix is a project to make initial prototypes of the Inside concept from [Everyone Forever](https://www.everyoneforever.com/), the sister studio of [Universal Everything](https://www.universaleverything.com/).

This prototype is based around the ESP32 and High density APA102/Dotstar addressable LED strips.

EnergyMix relies on the [PV_Live platform](https://www.solar.sheffield.ac.uk/pvlive/) from Sheffield University for solar power generation information. PV_Live "provides a near realtime estimate of nationally- and regionally-aggregated electricity generation from solar Photovoltaics (PV) connected to the GB transmission network".

EnergyMix relies on the [Balancing Mechanism Reporting Service](https://www.bmreports.com/bmrs/?q=eds/main) for other power generation information.

### How to Use

- Connect to the Captive Portal Named "_EnergyMix-XXXXX_" with the Password "_solar-wind-hydro_"
- Press Setup and Add your WiFi credentials and press save.

The device should close the captive portal and connect to the internet to gather the energy data.

If you need to update the WiFi credentials or colours for each energy source, you can launch the captive portal by press and holding the _Boot_ button after initial power up until the start up light sequence is complete.


### Hardware Guide

- [Esp32](https://www.amazon.co.uk/ESP-32S-Development-2-4GHz-Bluetooth-Antenna/dp/B071JR9WS9/ref=sr_1_3?crid=1C49KKM9QVDHF&keywords=esp32s&qid=1646922921&sprefix=esp32s%2Caps%2C164&sr=8-3)
- [Addressable Led Tape (40 Leds)](https://coolcomponents.co.uk/products/apa102-digital-rgb-addressable-led-weatherproof-strip-144-led-1m-adafruit-dotstar-compatible?_pos=10&_sid=0066bb396&_ss=r)
- [Level Shifter](https://www.amazon.co.uk/ARCELI-Channels-Converter-Bi-Directional-Shifter/dp/B07RDHR315/ref=sr_1_8?crid=1QDL958AQ3QDG&keywords=level+shifter&qid=1646923699&sprefix=level+shifte%2Caps%2C146&sr=8-8)

![Simple Wiring Diagram](https://github.com/v-a-s-t/EnergyMix_test/blob/main/schematic_simple.png?raw=true)
