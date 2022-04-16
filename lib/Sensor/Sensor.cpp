#include <Sensor.h>

UniversalTimer publishDataTimer( 1000, true );

Sensor::Sensor( uint16_t publishIntervalSecs )
{
  publishDataTimer.setInterval( publishIntervalSecs * 1000 );
  // TODO get device ID
}

bool isNotStarted( Entity* entity ) { return !( entity->isStarted() ); }

void Sensor::registerEntity( Entity* entity ) { _entities.push_back( entity ); }

void Sensor::registerLora( Lora* lora ) { _lora = lora; }

void Sensor::start()
{
  _lora->start();
  for ( auto entity : _entities ) { entity->start(); }

  auto it = std::remove_if( _entities.begin(), _entities.end(), isNotStarted );
  _entities.erase( it, _entities.end() );

  publishDataTimer.start();

  printSensors();
  log_i( "Started publishDataTimer" );
}

void Sensor::publish()
{
  for ( auto entity : _entities ) { entity->readData( &_attributes ); }
  _lora->publish( _attributes );
  _attributes.clear();
}

void Sensor::run()
{
  if ( MODE_DEEP_SLEEP_MINS > 0 )
  {
    // wait until LoRa has rejoined
    _lora->start();

    delay( 5000 );
    publish();
    delay( 5000 );
    publish();
    delay( 10000 );

    // Let the bytes transmit

    log_i( "Sleeping" );
    ESP.deepSleep( (MODE_DEEP_SLEEP_MINS)*60 * 1000000L );
  } else
  {
    if ( publishDataTimer.check() ) { publish(); }
  }
}

void Sensor::printSensors()
{
  log_i( "Sensors:" );
  for ( auto entity : _entities )
  {
    log_i( "- %s", entity->entityName().c_str() );
  }
}