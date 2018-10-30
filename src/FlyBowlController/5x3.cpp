// ----------------------------------------------------------------------------
// 5x3.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "5x3.h"


#if defined(__MK64FX512__)

namespace fly_bowl_controller
{
namespace constants
{

const size_t fly_bowl_ir_backlights[FLY_BOWL_COUNT] =
{
  0,
  1,
  2,
  3,
};

const size_t fly_bowl_visible_backlights[FLY_BOWL_COUNT] =
{
  0,
  1,
  2,
  3,
};

const size_t fan_high_voltages[FLY_BOWL_COUNT] =
{
  0,
  1,
  2,
  3,
};

const size_t indicator_low_voltages[FLY_BOWL_COUNT] =
{
  0,
  1,
  2,
  3,
};

// Pins

// Units

// Properties
const bool fly_bowls_enabled_default[FLY_BOWL_COUNT] =
{
  fly_bowls_enabled_element_default,
  fly_bowls_enabled_element_default,
  fly_bowls_enabled_element_default,
  fly_bowls_enabled_element_default,
};

// Parameters

// Functions

// Callbacks

// Errors
}
}
#endif
