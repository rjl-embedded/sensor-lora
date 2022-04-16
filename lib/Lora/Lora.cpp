#include <Lora.h>

TTN_esp32 ttn;

Lora::Lora( std::string appEui, std::string devEui, std::string appKey )
{
  _appEui = appEui;
  _devEui = devEui;
  _appKey = appKey;

  Wire.begin( PIN_SDA, PIN_SCL );
  Wire.setClock( 400000L );
}

void Lora::start()
{
  log_d( "Starting LORA..." );
  ttn.begin();
  ttn.onMessage( message );
  ttn.join( _devEui.c_str(), _appEui.c_str(), _appKey.c_str(), -1, 1000 );
  while ( !ttn.isJoined() ) { ; }

  log_d( "LORA started" );
  ttn.showStatus();
}

void Lora::publish( std::vector<Attribute> readings )
{
  uint8_t  buffer[PROTO_BUF_LENGTH] = { 0 };
  uint16_t bytes_written;

  encodePROTO( _devEui, readings, buffer, PROTO_BUF_LENGTH, bytes_written );

  ttn.sendBytes( buffer, bytes_written, 1, true );

  log_d( "Published protobuf: (%d bytes)", bytes_written );
}

bool Lora::isJoined() { return ttn.isJoined(); }

void message( const uint8_t *payload, size_t size, int rssi )
{
  Serial.println( "-- MESSAGE" );
  Serial.print( "Received " + String( size ) + " bytes RSSI=" + String( rssi ) +
                "db" );
  for ( int i = 0; i < size; i++ )
  {
    Serial.print( " " + String( payload[i] ) );
    // Serial.write(payload[i]);
  }

  Serial.println();
}
