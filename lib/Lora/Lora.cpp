#include <Lora.h>

#define _STRINGIZE( x ) #x
#define STRINGIZE( x )  _STRINGIZE( x )

TTN_esp32 ttn;

Lora::Lora()
{
  _appEui = STRINGIZE(APP_EUI);
  _devEui = STRINGIZE(DEV_EUI);
  _appKey = STRINGIZE(APP_KEY);

  Wire.begin( PIN_SDA, PIN_SCL );
  Wire.setClock( 400000L );
}

void Lora::start()
{
  log_d( "Starting LORA..." );
#ifdef TTGO_LORA32_V21
  ttn.begin( NSS, 0, RST, DIO0, DIO1, DIO2 );
#else
  ttn.begin();
#endif
  log_d( "LORA begin - OK" );
  ttn.onMessage( message );
  ttn.join( _devEui, _appEui, _appKey, 10, 1000 );
  while ( !ttn.isJoined() ) { ; }
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
