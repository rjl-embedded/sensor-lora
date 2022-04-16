#include "encode.h"

void encodePROTO( std::string devEUI, std::vector<Attribute> readings,
                  uint8_t *buffer, uint8_t buffer_length,
                  uint16_t &bytes_written )
{
  Packet packet = Packet_init_default;
  packet.sensor_type = SensorType_environment;

  Meta sensorMeta = Meta_init_default;
  strcpy( sensorMeta.device_eui, devEUI.c_str() );
  packet.has_meta = true;
  packet.meta = sensorMeta;

  packet.attributes.funcs.encode = encodeAttributes;
  packet.attributes.arg = &readings;

  pb_ostream_t ostream = pb_ostream_from_buffer( buffer, buffer_length );
  if ( !pb_encode( &ostream, Packet_fields, &packet ) )
  {
    log_e( "Failed to encode: %s", ostream.errmsg );
    return;
  }
  bytes_written = ostream.bytes_written;

  for ( int i = 0; i < ostream.bytes_written; i++ )
  {
    Serial.printf( "%02X", buffer[i] );
  }
  Serial.println();
}

bool encodeAttributes( pb_ostream_t *ostream, const pb_field_iter_t *field,
                       void *const *arg )
{
  bool isOK = false;

  std::vector<Attribute> *readings = (std::vector<Attribute> *)( *arg );

  for ( auto reading : ( *readings ) )
  {
    isOK |= encodeAttribute( ostream, field, &reading );
  }

  return isOK;
}

bool encodeAttribute( pb_ostream_t *ostream, const pb_field_iter_t *field,
                      Attribute *sensorField )
{
  if ( !( pb_encode_tag_for_field( ostream, field ) &&
          pb_encode_submessage( ostream, Attribute_fields, sensorField ) ) )
  {
    log_e( "Failed to encode field: %s ", ostream->errmsg );
    return false;
  }
  return true;
}
