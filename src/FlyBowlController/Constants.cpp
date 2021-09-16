// ----------------------------------------------------------------------------
// Constants.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  .version_major=4,
  .version_minor=0,
  .version_patch=0,
};

const double fan_power_min = 100.0;
const double fan_power_max = 100.0;

const long ms_per_second = 1000;

CONSTANT_STRING(state_string,"state");
CONSTANT_STRING(state_experiment_not_running_string,"EXPERIMENT_NOT_RUNNING");
CONSTANT_STRING(state_experiment_running_string,"EXPERIMENT_RUNNING");

CONSTANT_STRING(experiment_step_index_string,"experiment_step_index");
CONSTANT_STRING(experiment_step_count_string,"experiment_step_count");
CONSTANT_STRING(sequence_index_string,"sequence_index");
CONSTANT_STRING(sequence_count_string,"sequence_count");

// Pins

// Units
CONSTANT_STRING(seconds_units,"s");

// Properties
CONSTANT_STRING(fly_bowls_enabled_property_name,"flyBowlsEnabled");
const bool fly_bowls_enabled_element_default = true;

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

CONSTANT_STRING(step_delay_parameter_name,"step_delay");
const double step_delay_min = 0.0;
const double step_delay_max = 3600.0;

CONSTANT_STRING(step_duration_parameter_name,"step_duration");
const long step_duration_min = 1000;
const long step_duration_max = 86400000;

// Function
CONSTANT_STRING(set_ir_backlights_and_fans_on_at_power_function_name,"setIrBacklightsAndFansOnAtPower");
CONSTANT_STRING(set_ir_backlights_and_fans_on_at_intensity_function_name,"setIrBacklightsAndFansOnAtIntensity");
CONSTANT_STRING(set_visible_backlights_and_indicators_on_at_power_function_name,"setVisibleBacklightsAndIndicatorsOnAtPower");
CONSTANT_STRING(set_visible_backlights_and_indicators_on_at_intensity_function_name,"setVisibleBacklightsAndIndicatorsOnAtIntensity");
CONSTANT_STRING(add_visible_backlights_pwm_function_name,"addVisibleBacklightsPwm");
CONSTANT_STRING(add_experiment_step_function_name,"addExperimentStep");
CONSTANT_STRING(get_experiment_steps_function_name,"getExperimentSteps");
CONSTANT_STRING(get_experiment_status_function_name,"getExperimentStatus");

// Callbacks
CONSTANT_STRING(set_ir_backlights_and_fans_on_callback_name,"setIrBacklightsAndFansOn");
CONSTANT_STRING(set_ir_backlights_and_fans_off_callback_name,"setIrBacklightsAndFansOff");
CONSTANT_STRING(toggle_ir_backlights_and_fans_callback_name,"toggleIrBacklightsAndFans");
CONSTANT_STRING(set_visible_backlights_and_indicators_on_callback_name,"setVisibleBacklightsAndIndicatorsOn");
CONSTANT_STRING(set_visible_backlights_and_indicators_off_callback_name,"setVisibleBacklightsAndIndicatorsOff");
CONSTANT_STRING(toggle_visible_backlights_and_indicators_callback_name,"toggleVisibleBacklightsAndIndicators");
CONSTANT_STRING(remove_all_experiment_steps_callback_name,"removeAllExperimentSteps");
CONSTANT_STRING(run_experiment_callback_name,"runExperiment");
CONSTANT_STRING(stop_experiment_callback_name,"stopExperiment");

// Errors
CONSTANT_STRING(no_experiment_step_space_left_error,"No experiment step space left.");
}
}
