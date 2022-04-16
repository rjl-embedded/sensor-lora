#include <Arduino.h>
#include <EntitySHT31.h>
#include <EntityVEML7700.h>
#include <Lora.h>
#include <Sensor.h>
#include <secrets.h>

#define LO_BATT_SLEEP_TIME \
  10 * 60 * 1000 * 1000  // How long when low batt to stay in sleep (us)

Sensor         sensor( PUBLISH_INTERVAL_SECS );
Lora           lora( APP_EUI, DEV_EUI, APP_KEY );
EntitySHT31    sht31;
EntityVEML7700 veml7700;

void setup()
{
  Serial.begin( 115200 );
  Wire.begin();

  sensor.registerEntity( &sht31 );
  sensor.registerEntity( &veml7700 );
  sensor.registerLora( &lora );

  sensor.start();
}

void loop() { sensor.run(); }