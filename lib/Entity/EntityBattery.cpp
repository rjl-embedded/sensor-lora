#include "EntityBattery.h"

const uint8_t vbatPin = 35;

EntityBattery::EntityBattery() : Entity( EntityName_BATTERY ) {}

bool EntityBattery::start()
{
  _isStarted = true;

  pinMode( vbatPin, INPUT );

  return _isStarted;
}

/*-----------------------------------------------------------
 * readData()
 *----------------------------------------------------------*/

bool EntityBattery::readData( std::vector<Attribute> *readings )
{
  /*
    The ADC value is a 12-bit number, so the maximum value is 4095 (counting
    from 0). To convert the ADC integer value to a real voltage you’ll need to
    divide it by the maximum value of 4095, then double it (note above that
    TTGO halves the voltage), then multiply that by the reference voltage of
    the ESP32 which is 3.3V, and then multiply that by a correction factor
    obtained by comparing the calculated and measured voltage.
  */

  float voltage_battery = (float)( analogRead( vbatPin ) ) / 4095 * 2 * 3.3 *
                          BATTERY_CORRECTION_FACTOR;

  Attribute attribute = Attribute_init_default;
  attribute.entity_name = EntityName_BATTERY;

  attribute.which_type = Attribute_voltage_tag;
  attribute.type.voltage = voltage_battery;
  readings->push_back( attribute );
}