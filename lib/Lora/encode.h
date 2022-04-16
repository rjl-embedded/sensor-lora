#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include <Arduino.h>

#include "packet.pb.h"
/**
 * @brief Encodes a vector of readings to a protobuf packet buffer.
 *
 */
void encodePROTO( std::string devEUI, std::vector<Attribute> readings,
                  uint8_t *buffer, uint8_t buffer_length,
                  uint16_t &bytes_written );

/**
 * @brief The encoder function for repeated attributes.
 *
 */
bool encodeAttributes( pb_ostream_t *ostream, const pb_field_iter_t *field,
                       void *const *arg );

/**
 * @brief The encoder function for a specific attribute.
 *
 */
bool encodeAttribute( pb_ostream_t *ostream, const pb_field_iter_t *field,
                      Attribute *sensorField );