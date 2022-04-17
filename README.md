# sensor-lora  

Home Assistant LoRa-connected sensor firmware for an ESP32.

OK. It's pretty niche. But if you happen to have, say, a greenhouse that is beyond packet-radio transmission distance for a battery powered temperature sensor, here's arduino firmware for an ESP32 providing [Home Assistant sensor](https://www.home-assistant.io/integrations/sensor/) data over a LoRa link. 

Yes. You can now check your greenhouse temperature from 5 km away. Handy!

Drivers for a [VEM7700 light sensor](https://www.vishay.com/docs/84286/veml7700.pdf), [Sensirion SHT31 temperature and humidity sensor](https://www.amazon.co.uk/Temperature-Interface-Measurement-GY-SHT31-D-Production/dp/B08NB86TRC/ref=sr_1_3_sspa?adgrpid=1181975898127193&hvadid=73873694047276&hvbmt=bp&hvdev=c&hvlocphy=131921&hvnetw=o&hvqmt=p&hvtargid=kwd-73873627544018%3Aloc-188&hydadcr=25808_1974543&keywords=sht31&qid=1650173019&sr=8-3-spons&psc=1&smid=A4K6YCJSIGVT2&spLa=ZW5jcnlwdGVkUXVhbGlmaWVyPUFZSkJHV1hUM1RFMjMmZW5jcnlwdGVkSWQ9QTA1NTI0NDYySUY0TTRGMTBGTUNMJmVuY3J5cHRlZEFkSWQ9QTA1MzI2NjczVDlMMDJSTEtEMEJPJndpZGdldE5hbWU9c3BfYXRmJmFjdGlvbj1jbGlja1JlZGlyZWN0JmRvTm90TG9nQ2xpY2s9dHJ1ZQ==), and the device's battery voltage are provided. The firmware's plugin architecture makes it easily extensible to provide new sensors.

## Documentation

For documentation, see [documentation]().

## License

This project is licensed under the MIT License - see file [LICENSE.md](LICENSE.md) for details.

## Version history

0.1 Initial release.