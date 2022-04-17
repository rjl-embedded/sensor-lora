# sensor-lora

**Home Assistant LoRa-connected sensor firmware for an ESP32.**

![dashboard](docs/src/img/dashboard.jpg)

OK. It's pretty niche. But if you happen to have, say, a greenhouse that is beyond packet-radio transmission distance for a battery powered temperature sensor, here's arduino firmware for an ESP32 providing [Home Assistant sensor](https://www.home-assistant.io/integrations/sensor/) data over a LoRa link. 

Yes. You can now check your greenhouse temperature from 5 kilometers away. Handy!

Drivers for a [VEM7700 light sensor](https://www.vishay.com/docs/84286/veml7700.pdf), [Sensirion SHT31 temperature and humidity sensor](https://www.amazon.co.uk/Temperature-Interface-Measurement-GY-SHT31-D-Production/dp/B08NB86TRC/ref=sr_1_3_sspa?adgrpid=1181975898127193&hvadid=73873694047276&hvbmt=bp&hvdev=c&hvlocphy=131921&hvnetw=o&hvqmt=p&hvtargid=kwd-73873627544018%3Aloc-188&hydadcr=25808_1974543&keywords=sht31&qid=1650173019&sr=8-3-spons&psc=1&smid=A4K6YCJSIGVT2&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFZSkJHV1hUM1RFMjMmZW5jcnlwdGVkSWQ9QTA1NTI0NDYySUY0TTRGMTBGTUNMJmVuY3J5cHRlZEFkSWQ9QTA1MzI2NjczVDlMMDJSTEtEMEJPJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==), and the device's battery voltage are provided. The firmware's plugin architecture makes it easily extensible to provide new sensors.


## How to use this

You'll need [platformio](https://platformio.org/), a LILYGO T3 V2.1.6 LoRa32 microcontroller, some sensors, a [The Things Network](https://www.thethingsnetwork.org/), a LoRaWAN hub, and a [Home Assistant](https://www.home-assistant.io/) installation. 

Step one. Create a The Things Network project and get its authentication details. Set those in `platformio.ini` build flags. Flash the micocontroller. Install the Node-RED flow with the protocol buffer schema. Wire up an MQTT in node for The Things Network, and an MQTT out node for Home Assistant's MQTT server. 

Step two. Boom. The entities appear in Home Assistant.

![cartoon](docs/src/img/i_think_you_should_be_more_explicit.jpg)

OK. Full(er) documentation [here](https://richardjlyon.github.io/sensor-lora/).

## Licensing

It's licensed under the MIT License - see file [LICENSE.md](docs/src/LICENSE.md) for details.

## Credits

The LoRa library uses Francois Riotte's library [TheThingsNetwork_esp32](https://github.com/rgot-org/TheThingsNetwork_esp32).

## Contact

You can contact me at [sensorlora.richlyon@spamgourmet.com]()