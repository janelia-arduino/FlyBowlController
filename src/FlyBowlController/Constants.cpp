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

const long ms_per_second = 1000;

// Pins

// Units
CONSTANT_STRING(seconds_units,"s");

// Properties
CONSTANT_STRING(fly_bowls_enabled_property_name,"flyBowlsEnabled");
const bool fly_bowls_enabled_element_default = true;

CONSTANT_STRING(experiment_delay_property_name,"experimentDelay");
const double experiment_delay_min = 0.0;
const double experiment_delay_max = 120.0;
const double experiment_delay_default = 0.0;

// Parameters
CONSTANT_STRING(pulse_delay_parameter_name,"pulse_delay");
const long pulse_delay_min = 0;
const long pulse_delay_max = 2000000000;

CONSTANT_STRING(pulse_period_parameter_name,"pulse_period");
const long pulse_period_min = 2;
const long pulse_period_max = 2000000000;

CONSTANT_STRING(pulse_on_duration_parameter_name,"pulse_on_duration");
const long pulse_on_duration_min = 1;
const long pulse_on_duration_max = 2000000000;

CONSTANT_STRING(pulse_count_parameter_name,"pulse_count");
const long pulse_count_min = 1;
const long pulse_count_max = 2000000000;

CONSTANT_STRING(sequence_off_duration_parameter_name,"sequence_off_duration");
const long sequence_off_duration_min = 0;
const long sequence_off_duration_max = 2000000000;

CONSTANT_STRING(sequence_count_parameter_name,"sequence_count");
const long sequence_count_min = 1;
const long sequence_count_max = 2000000000;

CONSTANT_STRING(step_duration_parameter_name,"step_duration");
const double step_duration_min = 10.0;
const double step_duration_max = 2000.0;

// Function
CONSTANT_STRING(set_ir_backlights_on_at_power_function_name,"setIrBacklightsOnAtPower");
CONSTANT_STRING(set_visible_backlights_on_at_power_function_name,"setVisibleBacklightsOnAtPower");
CONSTANT_STRING(add_visible_backlights_pwm_function_name,"addVisibleBacklightsPwm");
CONSTANT_STRING(add_experiment_step_function_name,"addExperimentStep");
CONSTANT_STRING(get_experiment_steps_function_name,"getExperimentSteps");
CONSTANT_STRING(get_experiment_info_function_name,"getExperimentInfo");

// Callbacks
CONSTANT_STRING(set_ir_backlights_on_callback_name,"setIrBacklightsOn");
CONSTANT_STRING(set_ir_backlights_off_callback_name,"setIrBacklightsOff");
CONSTANT_STRING(set_visible_backlights_on_callback_name,"setVisibleBacklightsOn");
CONSTANT_STRING(set_visible_backlights_off_callback_name,"setVisibleBacklightsOff");
CONSTANT_STRING(remove_all_experiment_steps_callback_name,"removeAllExperimentSteps");
CONSTANT_STRING(run_experiment_callback_name,"runExperiment");
CONSTANT_STRING(stop_experiment_callback_name,"stopExperiment");

// Errors
CONSTANT_STRING(no_experiment_step_space_left_error,"No experiment step space left.");
}
}
