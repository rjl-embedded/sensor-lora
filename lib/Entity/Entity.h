/**
 * Defines an Entity - a physical or virtual device that privodes one or more
 * measurements of an attribute e.g. temperature (physical) or virtual (LoRa
 * RSSI).
 */

#pragma once
#include <Arduino.h>

#include <packet.pb.h>

/**
 * @brief Base class for an Entity
 *
 */
class Entity {
 public:
  Entity( EntityName entityName );
  virtual bool start() = 0;
  virtual bool readData( std::vector<Attribute> *readings ) = 0;

  /**
   * @brief Returns the name entity's name
   *
   * @return std::string The name e.g. "SHT31"
   */
  std::string entityName();

  /**
   * @brief Getter function for `_is_started`
   *
   * @return true if entity started
   * @return false if entity is not started
   */
  bool isStarted();

 protected:
  EntityName _entityName = EntityName_UnknownEntity;
  bool       _isStarted = false;
};

/**
 * @brief Helper function to calculate the dewpoint from temperature and
 * relative humidity
 *
 * See:
 * https://calcunation.com/calculator/dew-point.php#:~:text=What%20is%20the%20Magnus%20Dew%20Point%20Formula%3F%20To,is%3A%20Approximate%20Dew%20Point%20%3D%2047.90%20Degrees%20Celsius.
 *
 * @param temp_C Temperaure in degrees centigrade
 * @param relativeHumidity Relative humidity (0 - 100)
 * @return float Dewpoint in degrees centigrade
 */
float dewpoint( float temp_C, uint16_t relativeHumidity );