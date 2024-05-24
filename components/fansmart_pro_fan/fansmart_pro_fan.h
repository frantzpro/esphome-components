#pragma once

#include "esphome.h"
#ifdef USE_API
#include "esphome/components/api/custom_api_device.h"
#endif
#include "esphome/components/fan/fan.h"

#define CMD_PAIR (0x28)
#define CMD_UNPAIR (0x45)
#define CMD_GENERIC_ONOFF (0x6f)
#define CMD_DIRECTION (0x15)
#define CMD_SPEED (0x31)

namespace esphome {
namespace fansmartpro {

class FanSmartProFan : public FanCall, public Component, public EntityBase
#ifdef USE_API
  , public api::CustomAPIDevice
#endif
{
 public:
  void setup() override;
  void dump_config() override;

//  void set_cold_white_temperature(float cold_white_temperature) { cold_white_temperature_ = cold_white_temperature; }
//  void set_warm_white_temperature(float warm_white_temperature) { warm_white_temperature_ = warm_white_temperature; }
//  void set_constant_brightness(bool constant_brightness) { constant_brightness_ = constant_brightness; }
//  void set_reversed(bool reversed) { reversed_ = reversed; }
//  void set_min_brightness(uint8_t min_brightness) { min_brightness_ = min_brightness; }
//  void set_tx_duration(uint32_t tx_duration) { tx_duration_ = tx_duration; }
//  void setup_state(fan::Fan *state) override { this->fan_state_ = state; }
//  void write_state(fan::Fan *state) override;
  void setup_state(fan::Fan *state) { this->fan_state_ = state; }
  void write_state(fan::Fan *state);
//  fan::FanTraits get_traits() override;
  fan::FanTraits get_traits();
  void on_pair();
  void on_unpair();

 protected:
  void send_packet(uint16_t cmd, uint8_t cold, uint8_t warm);

//  float cold_white_temperature_{167};
//  float warm_white_temperature_{333};
//  bool constant_brightness_;
//  bool reversed_;
//  uint8_t min_brightness_;
  bool _is_off;
  uint8_t tx_count_;
  uint32_t tx_duration_;
  fan::Fan *fan_state_;
};

template<typename... Ts> class PairAction : public Action<Ts...> {
 public:
  explicit PairAction(esphome::fan::Fan *state) : state_(state) {}

  void play(Ts... x) override {
    ((FanSmartProFan *)this->state_)->on_pair();
  }

 protected:
  esphome::fan::Fan *state_;
};

template<typename... Ts> class UnpairAction : public Action<Ts...> {
 public:
  explicit UnpairAction(esphome::fan::Fan *state) : state_(state) {}

  void play(Ts... x) override {
    ((FanSmartProFan *)this->state_)->on_unpair();
  }

 protected:
  esphome::fan::Fan *state_;
};

} //namespace fansmartpro
} //namespace esphome
