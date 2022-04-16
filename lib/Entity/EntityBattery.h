#pragma once

#include "pb.h"
#include "pb_common.h"
#include "pb_encode.h"
#include <Arduino.h>
#include <Entity.h>
#include <esp_adc_cal.h>

#include <packet.pb.h>

class EntityBattery : public Entity {
 public:
  EntityBattery();

  /**
   * @brief Perform startup functions for the battery
   *
   * @return true if startup successful
   * @return false if startup fails
   */
  bool start();

  /**
   * @brief Read the battery voltage
   *
   * @param readings the Attribute vector
   * @return true if the device is started
   * @return false if the device is not started
   */
  bool readData( std::vector<Attribute> *readings );
};

uint16_t Sample();
uint16_t ReadVBatt();