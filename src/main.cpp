#include <Arduino.h>
#include <EntityBattery.h>
#include <EntitySHT31.h>
#include <EntityVEML7700.h>
#include <Lora.h>
#include <Sensor.h>

Sensor         sensor( PUBLISH_INTERVAL_SECS );
Lora           lora{};
EntitySHT31    sht31;
EntityVEML7700 veml7700;
EntityBattery  battery;

void setup()
{
  Serial.begin( 115200 );
  Wire.begin();

  sensor.registerEntity( &sht31 );
  sensor.registerEntity( &veml7700 );
  sensor.registerEntity( &battery );
  sensor.registerLora( &lora );

  sensor.start();
}

void loop() { sensor.run(); }