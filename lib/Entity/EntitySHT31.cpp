#include "EntitySHT31.h"

EntitySHT31::EntitySHT31() : Entity( EntityName_SHT31 ) {}
EntitySHT31::EntitySHT31( float temperatureOffset ) : Entity( EntityName_SHT31 )
{
  _temperatureOffset = temperatureOffset;
}

bool EntitySHT31::start()
{
  if ( _sht31.begin( 0x44 ) ) { _isStarted = true; }

  return _isStarted;
}

bool EntitySHT31::readData( std::vector<Attribute> *readings )
{
  if ( _isStarted )
  {
    float temperature = _sht31.readTemperature() - _temperatureOffset;
    float humidity = _sht31.readHumidity();

    Attribute attribute = Attribute_init_default;
    attribute.entity_name = EntityName_SHT31;

    attribute.which_type = Attribute_temperature_tag;
    attribute.type.temperature = temperature;
    readings->push_back( attribute );

    attribute.which_type = Attribute_humidity_tag;
    attribute.type.humidity = humidity;
    readings->push_back( attribute );

    attribute.which_type = Attribute_dewpoint_tag;
    attribute.type.dewpoint = dewpoint( temperature, humidity );
    readings->push_back( attribute );

    return true;
  } else
  {
    return false;
  }
}