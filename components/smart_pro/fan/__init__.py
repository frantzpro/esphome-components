from esphome.components import fan
from esphome.const import CONF_OUTPUT_ID
import esphome.config_validation as cv
import esphome.codegen as cg

DEPENDENCIES = ["esp32"]

fansmartpro_ns = cg.esphome_ns.namespace('fansmartpro')
FanSmartPro = fansmartpro_ns.class_('FanSmartPro', fan.Fan)

CONFIG_SCHEMA = fan.FAN_SCHEMA.extend(
    {
        cv.GenerateID(CONF_OUTPUT_ID): cv.declare_id(FanSmartPro),
    }
).extend(cv.COMPONENT_SCHEMA)

async def to_code(config):
    var = cg.new_Pvariable(config[CONF_OUTPUT_ID])
    await cg.register_component(var, config)
    await fan.register_fan(var, config)
