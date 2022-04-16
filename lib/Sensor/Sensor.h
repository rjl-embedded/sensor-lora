#pragma once
#include <Arduino.h>
#include <Entity.h>
#include <Lora.h>
#include <UniversalTimer.h>

#define MAX_ENTITIES 10

/**
 * @brief Represents the sensor with a LoRa channel and a set of entities.
 *
 */
class Sensor {
 public:
  Sensor( uint16_t publishIntervalSecs );

  /**
   * @brief Register an entity on the sensor
   *
   * @param entity (Entity) The entity to register
   */
  void registerEntity( Entity* entity );

  /**
   * @brief Register the LoRa driver
   *
   * @param lora (Lora) The LoRa driver
   */
  void registerLora( Lora* lora );

  /**
   * @brief Start the entities, LoRa driver, and publish timer
   *
   */
  void start();

  /**
   * @brief Publish the readings over LoRa and reset them
   *
   */
  void publish();

  /**
   * @brief Run the publish event loop
   *
   */
  void run();

 private:
  Lora*                  _lora;
  std::vector<Entity*>   _entities;
  std::vector<Attribute> _attributes;
  void                   printSensors();
};