# Firmware

The firmware is developed as a [platformio](https://platformio.org/) project. It uses the espressif32 platform and arduino framework. 

## Configuration

Configuration is done through compiler flags to limit the need to modify the firmware.

### I2C

Define the `SDA` and `SCL` pins as:

```
build_flags = 

	-D PIN_SDA=21
	-D PIN_SCL=22
```

### Publish interval

The publishing interval is defined as:

```
build_flags = 

	-D PUBLISH_INTERVAL_SECS=10
    -D MODE_DEEP_SLEEP_MINS=0
```

Deep sleep has been investigated as a mechanism for extending battery life. At this revision, it doesn't work pending resolving an issue around waking up and reconnecting the LoRa radio. For now, set it to 0 minutes to disable the feature in firmware.

### Authentication credentials 

LoRa uses a The Things Netwotk (TTN) application (see [LoRa](lora.md) for details). The firmware requires the app eui, dev ei, and app key to connect. To avoid exposing these authentication credentials in version control, they are obtained from a local file and provided as compiler flags.

To configure, create a file named `secret_auth_XXX.py` in the same directory as `platformio.ini`.  add them to this file in the following format:

```
# TTN 'heltec lora environment sensor' credentials

keys = {
  "APP_EUI": "XXX",
  "DEV_EUI": "XXX",
  "APP_KEY": "XXX",
}

print(f"-D APP_EUI={keys['APP_EUI']} -D DEV_EUI={keys['DEV_EUI']} -D APP_KEY={keys['APP_KEY']} ")
```
Finally, add the following buid flag specifier in `platformio.ini`:

```
build_flags = 

    !python secret_auth_XXX.py

```

### LoRa

The firmware uses Francois Riotte's library [TheThingsNetwork_esp32](https://github.com/rgot-org/TheThingsNetwork_esp32). This requires a number of compiler definitions for specifying e.g. the LoRaWAN specification, region, etc. as described [here](https://github.com/mcci-catena/arduino-lmic#configuration).

Check `platformio.ini` for actual variables, but these typically are:

```
[env:ttgo-lora32-v21]

build_flags = 

	-D ARDUINO_LMIC_PROJECT_CONFIG_H_SUPPRESS
	-D CFG_eu868=1
	-D CFG_sx1276_radio=1
	-D LMIC_LORAWAN_SPEC_VERSION=LMIC_LORAWAN_SPEC_VERSION_1_0_3
```

Additional flags are required to specify the pins used for LoRa boards which are not pre-integrated (which the TTGO LoRa v21 is not). These are specified as follows:

```
build_flags = 

	-D NSS=18
	-D RST=14
	-D DIO0=26
	-D DIO1=33
	-D DIO2=32
```

[This spreadsheet](https://www.dropbox.com/s/gly6z21qqps7uvc/espMeshtasticBoards_ev01.xls?dl=0) may help you identify the pins for your microcontroller.

## Code structure

The code employs a simple plugin architecture to allow new devices to be added relatively easily. It defines a `Sensor` object representing the `Lora` driver object, and one or more `Entity` objects providing `attributes` (using the [language of Home Assistant](https://www.home-assistant.io/docs/configuration/customizing-devices)). At setup, the lora and entities are registered and started. The runloop drives a timer for the publishing interval.

If this isn't clear: an 'Entity' is something like an SHT31 temperature and humidity sensor. 'Temperature' and 'humidity' are attributes of that sensor. A 'Sensor' here is the combination of sensors and lora radio comprising the device.

### Protocol buffer

The device employes Google's [Protocol Buffers](https://developers.google.com/protocol-buffers/) for serialising and transmitting data. This has the advantage of generating very efficient packets, which reduces power requirements and extends battery life. It has the disadvantage of being a pain to implement on microcontrollers. I've made it as simple as possible to extend. 

The schema is defined in `/protobuf-packet/packet.proto`. String sizes for any metadata must be defined in `/protobuf-packet/packet.options`. Together, these define a `Packet` data structure that can be processed be e.g. [node-RED](nodered.md). If you alter this, you need to regenerate the header and implementation code in `proto` (don't alter these by hand) - see `/protobuf-packet/README.md` for instructions.

The result of this is a set of constants you can use in your entity implementations to define entity and attribute properties -- look at an existing Entity implementationfor how to do it.

### Entity class

This handles starting the entity, reading the data, and serialising it. Each entity object provides a `start()` method and a `readData()` method. `start()` returns `true` if startup and initialising was successful. `readData()` obtains the latest data from the sensor and serialises it for encoding by the LoRa class.

#### Battery

An entity class (`EntityBattery`) is defined for reporting the device battery voltage. This may require calibration on your battery as follows:

```
build_flags = 

    -D BATTERY_CORRECTION_FACTOR=0.885
```

I set it to one, measured the voltage and compared it to the reported value, then computed the correction factor.

### Lora class

This handles starting the radio, joining The Things Network, serialising the readings from the sensors, and transmitting it. The device will hang during `start()` if it cannot join. `publish()` takes a vector of readings from the sensors, encodes it as a protocol buffer `Packet`, and transmits it.

### Sensor class

This handles registering entities and the radio, starting them, reading their data at a defined interval, and sending the data to the LoRa for transmission.

Add new entities like so:

```
#include <EntityMyExcellentThing.h>
EntityMyExcellentThing  excellentThing;
void setup()
{
    ...
    sensor.registerEntity( &excellentThing );
}
```






