#pragma once

#include "Adafruit_SHT31.h"
#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include <Entity.h>

#include <packet.pb.h>

/**
 * @brief A device driver for the Sensirion SHT31 temperature and humidity
 * sensor
 *
 */
class EntitySHT31 : public Entity {
 public:
  EntitySHT31();

  /**
   * @brief Construct a new entity with a temperature offset
   *
   * This is subtracted from the measured temperature i.e. positive values
   * represent an entity that is overreading temperature.
   *
   * @param temperatureOffset The offset (degrees centigrade)
   */
  EntitySHT31( float temperatureOffset );

  /**
   * @brief Perform startup functions for the entity
   *
   * @return true if startup successful
   * @return false if startup fails
   */
  bool start();

  /**
   * @brief Read the entity attributes into a vector of Attribute
   *
   * @param readings the Attribute vector
   * @return true if the device is started
   * @return false if the device is not started
   */
  bool readData( std::vector<Attribute> *readings );

 protected:
  Adafruit_SHT31 _sht31 = Adafruit_SHT31();
  float          _temperatureOffset = 0;
};