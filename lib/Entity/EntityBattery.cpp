#include "EntityBattery.h"

esp_adc_cal_characteristics_t *adc_chars;

EntityBattery::EntityBattery() : Entity( EntityName_BATTERY ) {}

bool EntityBattery::start()
{
  _isStarted = true;

  adc_chars = (esp_adc_cal_characteristics_t *)calloc(
      1, sizeof( esp_adc_cal_characteristics_t ) );
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(
      ADC_UNIT_1, ADC_ATTEN_DB_6, ADC_WIDTH_BIT_12, DEFAULT_VREF, adc_chars );
  adc1_config_width( ADC_WIDTH_BIT_12 );
  adc1_config_channel_atten( ADC1_CHANNEL_1, ADC_ATTEN_DB_6 );

  // Prime the Sample register
  for ( uint8_t i = 0; i < VBATT_SMOOTH; i++ ) { Sample(); }

  pinMode( VBATT_GPIO, OUTPUT );
  digitalWrite( VBATT_GPIO,
                LOW );  // ESP32 Lora v2.1 reads on GPIO37 when GPIO21 is low
  delay( ADC_READ_STABILIZE_MS );  // let GPIO stabilize}

  return _isStarted;
}

/*-----------------------------------------------------------
 * readData()
 *----------------------------------------------------------*/

bool EntityBattery::readData( std::vector<Attribute> *readings )
{
  float voltage_battery = Sample() / 1000.0;
  Serial.println( voltage_battery );

  Attribute attribute = Attribute_init_default;
  attribute.entity_name = EntityName_BATTERY;

  attribute.which_type = Attribute_voltage_tag;
  attribute.type.voltage = voltage_battery;
  readings->push_back( attribute );
}

//  Use a buffer to average/sample ADC
uint16_t Sample()
{
  static uint8_t  i = 0;
  static uint16_t samp[VBATT_SMOOTH];
  static int32_t  t = 0;
  static bool     f = true;
  if ( f )
  {
    for ( uint8_t c = 0; c < VBATT_SMOOTH; c++ ) { samp[c] = 0; }
    f = false;
  }              // Initialize the sample array first time
  t -= samp[i];  // doing a rolling recording, so remove the old rolled around
                 // value out of total and get ready to put new one in.
  if ( t < 0 ) { t = 0; }

  // ADC read
  uint16_t voltage = ReadVBatt();

  samp[i] = voltage;
#if defined( __DEBUG ) && __DEBUG > 0
  Serial.printf( "ADC Raw Reading[%d]: %d", i, voltage );
#endif
  t += samp[i];

  if ( ++i >= VBATT_SMOOTH ) { i = 0; }
  uint16_t s = round( ( (float)t / (float)VBATT_SMOOTH ) );
#if defined( __DEBUG ) && __DEBUG > 0
  Serial.printf( "   Smoothed of %d/%d = %d\n", t, VBATT_SMOOTH, s );
#endif

  return s;
}

// Poll the proper ADC for VBatt on Heltec Lora 32 with GPIO21 toggled
uint16_t ReadVBatt()
{
  uint16_t reading = 666;

  digitalWrite( VBATT_GPIO,
                LOW );  // ESP32 Lora v2.1 reads on GPIO37 when GPIO21 is low
  delay( ADC_READ_STABILIZE_MS );  // let GPIO stabilize
#if ( defined( HELTEC_V2_1 ) )
  pinMode( ADC1_CHANNEL_1, OPEN_DRAIN );  // ADC GPIO37
  reading = adc1_get_raw( ADC1_CHANNEL_1 );
  pinMode( ADC1_CHANNEL_1,
           INPUT );  // Disconnect ADC before GPIO goes back high so we protect
                     // ADC from direct connect to VBATT (i.e. no divider)
#else
  pinMode( ADC2_CHANNEL_4, OPEN_DRAIN );  // ADC GPIO13
  adc2_get_raw( ADC2_CHANNEL_4, ADC_WIDTH_BIT_12, &reading );
  pinMode( ADC2_CHANNEL_4,
           INPUT );  // Disconnect ADC before GPIO goes back high so we protect
                     // ADC from direct connect to VBATT (i.e. no divider
#endif

  uint16_t voltage = esp_adc_cal_raw_to_voltage( reading, adc_chars );
  voltage *= VOLTAGE_DIVIDER;

  return voltage;
}