#pragma once

#include "Adafruit_VEML7700.h"
#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include <Entity.h>

#include <packet.pb.h>

/**
 * @brief A device driver for the VEML7700 ambient lilght sensor
 *
 */
class EntityVEML7700 : public Entity {
 public:
  EntityVEML7700();

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
  Adafruit_VEML7700 _veml7700;
};
