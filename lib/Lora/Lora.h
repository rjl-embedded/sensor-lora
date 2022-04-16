#pragma once

#include <Arduino.h>
#include <TTN_esp32.h>
#include <Wire.h>

#include "packet.pb.h"

/**
 * @brief Publishes a protobuf packet of sensor readings to The
 * Things Network.
 *
 */
class Lora {
 public:
  Lora();

  /**
   * @brief Start the driver and join The Things Network
   *
   */
  void start();

  /**
   * @brief Publish readings to The Things Network
   *
   * @param readings A vector of readings of `Attribute`
   */
  void publish( std::vector<Attribute> readings );

  /**
   * @brief Returns true if LoRa is joined to TTN
   *
   */
  bool isJoined();

 private:
  char *_appEui;
  char *_devEui;
  char *_appKey;
};

/**
 * @brief Print the encoded protobuf payload to the console for debugging
 *
 * @param payload
 * @param size
 * @param rssi
 */
void message( const uint8_t *payload, size_t size, int rssi );

void encodePROTO( std::string devEUI, std::vector<Attribute> readings,
                  uint8_t *buffer, uint8_t buffer_length,
                  uint16_t &bytes_written );
bool encodeAttributes( pb_ostream_t *ostream, const pb_field_iter_t *field,
                       void *const *arg );
bool encodeAttribute( pb_ostream_t *ostream, const pb_field_iter_t *field,
                      Attribute *sensorField );