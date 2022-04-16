# Welcome to MkDocs

This is firmware for a Home Assistant compatible sensor that provides environment data over a LoRa link.

## Configuration

### Secrets 

Authentication data is obtained from `include/secrets.h` See Things Network [Add an Application](https://www.thethingsnetwork.org/docs/applications/add/) for how to generate an application and obtain keys. 

```
#define APP_EUI "XXX"
#define DEV_EUI "XXX"
#define APP_KEY "XXX"
```

### Publish interval

The publishing interval is defined in `platformio.ini`

```
build_flags = 
	-D PUBLISH_INTERVAL_SECS=10
```

### LoRa

LoRa uses Francois Riotte's library [TheThingsNetwork_esp32](https://github.com/rgot-org/TheThingsNetwork_esp32). This requires a number of compiler definitions for specifying e.g. the LoRaWAN specification, region, etc. as described [here](https://github.com/mcci-catena/arduino-lmic#configuration).

Check `platformio.ini` for actual variables, but these typically are:

```
[env:heltec_lora]

build_flags = 

	-D ARDUINO_LMIC_PROJECT_CONFIG_H_SUPPRESS
	-D CFG_eu868=1
	-D CFG_sx1276_radio=1
	-D LMIC_LORAWAN_SPEC_VERSION=LMIC_LORAWAN_SPEC_VERSION_1_0_3
```