#include <Entity.h>

Entity::Entity( EntityName entityName ) : _entityName( entityName ) {}

bool Entity::isStarted() { return _isStarted; }

std::string Entity::entityName()
{
  switch ( _entityName )
  {
    case EntityName_HDC1080: return "HDC1080";
    case EntityName_SCD30: return "SCD30";
    case EntityName_BMP388: return "BMP388";
    case EntityName_VEML7700: return "VEML7700";
    case EntityName_LORA: return "LORA";
    case EntityName_BATTERY: return "BATTERY";
    case EntityName_EMONPI: return "EMONPI";
    case EntityName_BOILERLIGHT: return "BOILERLIGHT";
    case EntityName_DHT22: return "DHT22";
    case EntityName_SHT15: return "kwSHT15";
    case EntityName_SHT31: return "SHT31";
    default: return "UNKNOWN_SENSOR";
  }
}

float dewpoint( float temp_C, uint16_t relativeHumidity )
{
  float logHumidity = log( relativeHumidity / 100.0 );
  float adjustedTemperature = ( 17.62 * temp_C ) / ( 243.12 + temp_C );
  return ( 243.12 * ( logHumidity + adjustedTemperature ) ) /
         ( 17.62 - ( logHumidity + adjustedTemperature ) );
}