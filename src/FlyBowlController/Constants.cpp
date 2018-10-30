// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "Constants.h"


namespace fly_bowl_controller
{
namespace constants
{
CONSTANT_STRING(device_name,"fly_bowl_controller");

CONSTANT_STRING(firmware_name,"FlyBowlController");
// Use semantic versioning http://semver.org/
const modular_server::FirmwareInfo firmware_info =
{
  .name_ptr=&firmware_name,
  .version_major=1,
  .version_minor=0,
  .version_patch=0,
};

const long fan_power_min = 100;
const long fan_power_max = 100;

// Pins

// Units

// Properties
CONSTANT_STRING(fly_bowls_enabled_property_name,"flyBowlsEnabled");
const bool fly_bowls_enabled_element_default = true;

// Parameters

// Function
CONSTANT_STRING(set_ir_backlights_on_at_power_function_name,"setIrBacklightsOnAtPower");
CONSTANT_STRING(set_visible_backlights_on_at_power_function_name,"setVisibleBacklightsOnAtPower");
CONSTANT_STRING(add_visible_backlights_pwm_function_name,"addVisibleBacklightsPwm");

// Callbacks
CONSTANT_STRING(set_ir_backlights_on_callback_name,"setIrBacklightsOn");
CONSTANT_STRING(set_ir_backlights_off_callback_name,"setIrBacklightsOff");
CONSTANT_STRING(set_visible_backlights_on_callback_name,"setVisibleBacklightsOn");
CONSTANT_STRING(set_visible_backlights_off_callback_name,"setVisibleBacklightsOff");

// Errors
}
}
