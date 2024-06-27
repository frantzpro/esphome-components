#include "fan_control.h"

namespace esphome {
  namespace fan_control {

    void FanControl::setup() {
      // Hier könnte Initialisierungscodes für BLE stehen, falls notwendig
    }

    void FanControl::set_fan_speed(uint8_t speed) {
      this->send_ble_command(0x01, speed);  // Beispielkommando und Geschwindigkeitswert
    }

    void FanControl::turn_fan_on_off(bool on) {
      this->send_ble_command(0x02, on ? 0x01 : 0x00);  // Beispielkommando für Ein/Aus
    }

    void FanControl::send_ble_command(uint8_t command, uint8_t value) {
      // Konvertieren Sie die Befehle in ein Paket, das über BLE gesendet werden kann
      uint8_t data[2] = {command, value};
      // Sie müssen hier die richtige Characteristic für das Senden herausfinden und verwenden
      auto characteristic = this->parent()->get_characteristic(UUID16(0xXXXX));  // Ersetzen Sie 0xXXXX durch den echten UUID Ihrer BLE-Characteristic
      if (characteristic == nullptr) return;
      characteristic->write_value(data, sizeof(data), true);
    }

  }  // namespace fan_control
}  // namespace esphome

