// ----------------------------------------------------------------------------
// 3x2.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#ifndef FLY_BOWL_CONTROLLER_3X2_CONSTANTS_H
#define FLY_BOWL_CONTROLLER_3X2_CONSTANTS_H
#include "Constants.h"


#if defined(__MK20DX256__)

namespace fly_bowl_controller
{
namespace constants {
enum {FLY_BOWL_COUNT=1};

extern const size_t fly_bowl_ir_backlights[FLY_BOWL_COUNT];

extern const size_t fly_bowl_visible_backlights[FLY_BOWL_COUNT];

extern const size_t fan_high_voltages[FLY_BOWL_COUNT];

extern const size_t indicator_low_voltages[FLY_BOWL_COUNT];

// Pins

// Units

// Properties
// Property values must be long, double, bool, long[], double[], bool[], char[], ConstantString *, (ConstantString *)[]
extern const bool fly_bowls_enabled_default[FLY_BOWL_COUNT];

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
#endif
