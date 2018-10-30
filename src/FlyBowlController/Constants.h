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
enum{PARAMETER_COUNT_MAX=1};
enum{FUNCTION_COUNT_MAX=3};
enum{CALLBACK_COUNT_MAX=4};

extern ConstantString device_name;

extern ConstantString firmware_name;
extern const modular_server::FirmwareInfo firmware_info;

extern const long fan_power_min;
extern const long fan_power_max;

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern ConstantString fly_bowls_enabled_property_name;
extern const bool fly_bowls_enabled_element_default;

// Parameters

// Function
extern ConstantString set_ir_backlights_on_at_power_function_name;
extern ConstantString set_visible_backlights_on_at_power_function_name;
extern ConstantString add_visible_backlights_pwm_function_name;

// Callbacks
extern ConstantString set_ir_backlights_on_callback_name;
extern ConstantString set_ir_backlights_off_callback_name;
extern ConstantString set_visible_backlights_on_callback_name;
extern ConstantString set_visible_backlights_off_callback_name;

// Errors
}
}
#include "5x3.h"
#include "3x2.h"
#endif
