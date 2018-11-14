// ----------------------------------------------------------------------------
// Constants.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef FLY_BOWL_CONTROLLER_CONSTANTS_H
#define FLY_BOWL_CONTROLLER_CONSTANTS_H
#include <ConstantVariable.h>
#include <BacklightController.h>


namespace fly_bowl_controller
{
namespace constants
{
//MAX values must be >= 1, >= created/copied count, < RAM limit
enum{PROPERTY_COUNT_MAX=1};
enum{PARAMETER_COUNT_MAX=8};
enum{FUNCTION_COUNT_MAX=6};
enum{CALLBACK_COUNT_MAX=9};

enum{EXPERIMENT_STEP_COUNT_MAX=32};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern const double fan_power_min;
extern const double fan_power_max;

struct PwmInfo
{
  uint32_t visible_backlight_channels;
  double intensity;
  uint32_t indicator_channels;
};

struct ExperimentStep
{
  double intensity;
  long pulse_period;
  long pulse_on_duration;
  long pulse_count;
  long sequence_off_duration;
  long sequence_count;
  double step_delay;
  double step_duration;
};

enum
{
  NO_EXPERIMENT_STEP_SPACE_LEFT_INDEX=-1,
};

struct ExperimentStatus
{
  const ConstantString * state_ptr;
  size_t experiment_step_index;
  long sequence_index;
  long sequence_count;
  EventId start_sequence_event_id;
  digital_controller::constants::PwmId pwm_id;
};

extern const long ms_per_second;

extern ConstantString state_string;
extern ConstantString state_experiment_not_running_string;
extern ConstantString state_experiment_running_string;

extern ConstantString experiment_step_index_string;
extern ConstantString experiment_step_count_string;
extern ConstantString sequence_index_string;
extern ConstantString sequence_count_string;

// Pins

// Units
extern ConstantString seconds_units;

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString fly_bowls_enabled_property_name;
extern const bool fly_bowls_enabled_element_default;

// Parameters
extern ConstantString pulse_delay_parameter_name;
extern const long pulse_delay_min;
extern const long pulse_delay_max;

extern ConstantString pulse_period_parameter_name;
extern const long pulse_period_min;
extern const long pulse_period_max;

extern ConstantString pulse_on_duration_parameter_name;
extern const long pulse_on_duration_min;
extern const long pulse_on_duration_max;

extern ConstantString pulse_count_parameter_name;
extern const long pulse_count_min;
extern const long pulse_count_max;

extern ConstantString sequence_off_duration_parameter_name;
extern const long sequence_off_duration_min;
extern const long sequence_off_duration_max;

extern ConstantString sequence_count_parameter_name;
extern const long sequence_count_min;
extern const long sequence_count_max;

extern ConstantString step_delay_parameter_name;
extern const double step_delay_min;
extern const double step_delay_max;

extern ConstantString step_duration_parameter_name;
extern const double step_duration_min;
extern const double step_duration_max;

// Function
extern ConstantString set_ir_backlights_on_at_intensity_function_name;
extern ConstantString set_visible_backlights_on_at_intensity_function_name;
extern ConstantString add_visible_backlights_pwm_function_name;
extern ConstantString add_experiment_step_function_name;
extern ConstantString get_experiment_steps_function_name;
extern ConstantString get_experiment_status_function_name;

// Callbacks
extern ConstantString set_ir_backlights_on_callback_name;
extern ConstantString set_ir_backlights_off_callback_name;
extern ConstantString toggle_ir_backlights_callback_name;
extern ConstantString set_visible_backlights_on_callback_name;
extern ConstantString set_visible_backlights_off_callback_name;
extern ConstantString toggle_visible_backlights_callback_name;
extern ConstantString remove_all_experiment_steps_callback_name;
extern ConstantString run_experiment_callback_name;
extern ConstantString stop_experiment_callback_name;

// Errors
extern ConstantString no_experiment_step_space_left_error;
}
}
#include "5x3.h"
#include "3x2.h"
#endif
