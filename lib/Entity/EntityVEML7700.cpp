#include "EntityVEML7700.h"

EntityVEML7700::EntityVEML7700() : Entity( EntityName_VEML7700 ) {}

bool EntityVEML7700::start()
{
  _isStarted = _veml7700.begin();

  if ( _isStarted )
  {
    _veml7700.setGain( VEML7700_GAIN_1_8 );
    _veml7700.setIntegrationTime( VEML7700_IT_25MS );
    _veml7700.powerSaveEnable( true );
    _veml7700.setPowerSaveMode( VEML7700_POWERSAVE_MODE4 );
    _veml7700.setLowThreshold( 10000 );
    _veml7700.setHighThreshold( 20000 );
    _veml7700.interruptEnable( true );
  }

  return _isStarted;
}
bool EntityVEML7700::readData( std::vector<Attribute> *readings )
{
  if ( _isStarted )
  {
    Attribute attribute = Attribute_init_default;
    attribute.entity_name = EntityName_VEML7700;

    attribute.which_type = Attribute_light_tag;
    attribute.type.light = _veml7700.readLuxNormalized();
    readings->push_back( attribute );

    return true;
  } else
  {
    return false;
  }
}