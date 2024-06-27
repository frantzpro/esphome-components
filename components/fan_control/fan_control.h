#pragma once

#include "esphome.h"
#include "esphome/components/ble_client/ble_client.h"  // BLEClient einbinden

namespace esphome {
  namespace fan_control {

    class FanControl : public Component, public ble_client::BLEClientNode {
     public:
      void setup() override;
      void set_fan_speed(uint8_t speed);
      void turn_fan_on_off(bool on);
      
     protected:
      void send_ble_command(uint8_t command, uint8_t value);
    };

  }  // namespace fan_control
}  // namespace esphome

