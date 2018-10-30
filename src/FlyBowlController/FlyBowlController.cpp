// ----------------------------------------------------------------------------
// FlyBowlController.cpp
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
// ----------------------------------------------------------------------------
#include "../FlyBowlController.h"


using namespace fly_bowl_controller;

FlyBowlController::FlyBowlController()
{
}

void FlyBowlController::setup()
{
  // Parent Setup
  BacklightController::setup();

  // Reset Watchdog
  resetWatchdog();

  // Variable Setup

  // Set Device ID
  modular_server_.setDeviceName(constants::device_name);

  // Add Hardware

  // Pins

  // Add Firmware
  modular_server_.addFirmware(constants::firmware_info,
    properties_,
    parameters_,
    functions_,
    callbacks_);

  // Properties
  modular_server::Property & high_voltage_power_max_property = modular_server_.property(backlight_controller::constants::high_voltage_power_max_property_name);
  high_voltage_power_max_property.setRange(constants::fan_power_min,constants::fan_power_max);

  modular_server::Property & fly_bowls_enabled_property = modular_server_.createProperty(constants::fly_bowls_enabled_property_name,constants::fly_bowls_enabled_default);
  fly_bowls_enabled_property.attachPostSetElementValueFunctor(makeFunctor((Functor1<size_t> *)0,*this,&FlyBowlController::setFlyBowlEnabledHandler));

  // Parameters
  modular_server::Parameter & power_parameter = modular_server_.parameter(digital_controller::constants::power_parameter_name);

  // Functions
  modular_server::Function & set_ir_backlights_on_at_power_function = modular_server_.createFunction(fly_bowl_controller::constants::set_ir_backlights_on_at_power_function_name);
  set_ir_backlights_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::setIrBacklightsOnAtPowerHandler));
  set_ir_backlights_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_visible_backlights_on_at_power_function = modular_server_.createFunction(fly_bowl_controller::constants::set_visible_backlights_on_at_power_function_name);
  set_visible_backlights_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::setVisibleBacklightsOnAtPowerHandler));
  set_visible_backlights_on_at_power_function.addParameter(power_parameter);

  // Callbacks
  modular_server::Callback & set_ir_backlights_on_callback = modular_server_.createCallback(fly_bowl_controller::constants::set_ir_backlights_on_callback_name);
  set_ir_backlights_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setIrBacklightsOnHandler));

  modular_server::Callback & set_ir_backlights_off_callback = modular_server_.createCallback(fly_bowl_controller::constants::set_ir_backlights_off_callback_name);
  set_ir_backlights_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setIrBacklightsOffHandler));

  modular_server::Callback & set_visible_backlights_on_callback = modular_server_.createCallback(fly_bowl_controller::constants::set_visible_backlights_on_callback_name);
  set_visible_backlights_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setVisibleBacklightsOnHandler));

  modular_server::Callback & set_visible_backlights_off_callback = modular_server_.createCallback(fly_bowl_controller::constants::set_visible_backlights_off_callback_name);
  set_visible_backlights_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setVisibleBacklightsOffHandler));

}

void FlyBowlController::setIrBacklightOnAtPower(size_t fly_bowl,
  long power)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

  if (fly_bowl_enabled)
  {
    setFanOn(fly_bowl);
    BacklightController::setIrBacklightOnAtPower(constants::fly_bowl_ir_backlights[fly_bowl],power);
  }
}

void FlyBowlController::setIrBacklightOn(size_t fly_bowl)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

  if (fly_bowl_enabled)
  {
    setFanOn(fly_bowl);
    BacklightController::setIrBacklightOn(constants::fly_bowl_ir_backlights[fly_bowl]);
  }
}

void FlyBowlController::setIrBacklightOff(size_t fly_bowl)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  BacklightController::setIrBacklightOff(constants::fly_bowl_ir_backlights[fly_bowl]);
  setFanOff(fly_bowl);
}

void FlyBowlController::setIrBacklightsOnAtPower(long power)
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setIrBacklightOnAtPower(fly_bowl,power);
  }
}

void FlyBowlController::setIrBacklightsOn()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setIrBacklightOn(fly_bowl);
  }
}

void FlyBowlController::setIrBacklightsOff()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setIrBacklightOff(fly_bowl);
  }
}

void FlyBowlController::setVisibleBacklightOnAtPower(size_t fly_bowl,
  long power)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

  if (fly_bowl_enabled)
  {
    setIndicatorOn(fly_bowl);
    BacklightController::setVisibleBacklightOnAtPower(constants::fly_bowl_visible_backlights[fly_bowl],power);
  }
}

void FlyBowlController::setVisibleBacklightOn(size_t fly_bowl)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

  if (fly_bowl_enabled)
  {
    setIndicatorOn(fly_bowl);
    BacklightController::setVisibleBacklightOn(constants::fly_bowl_visible_backlights[fly_bowl]);
  }
}

void FlyBowlController::setVisibleBacklightOff(size_t fly_bowl)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  BacklightController::setVisibleBacklightOff(constants::fly_bowl_visible_backlights[fly_bowl]);
  setIndicatorOff(fly_bowl);
}

void FlyBowlController::setVisibleBacklightsOnAtPower(long power)
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setVisibleBacklightOnAtPower(fly_bowl,power);
  }
}

void FlyBowlController::setVisibleBacklightsOn()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setVisibleBacklightOn(fly_bowl);
  }
}

void FlyBowlController::setVisibleBacklightsOff()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setVisibleBacklightOff(fly_bowl);
  }
}

size_t FlyBowlController::getFlyBowlCount()
{
  return constants::FLY_BOWL_COUNT;
}

void FlyBowlController::setFanOn(size_t fly_bowl)
{
  setHighVoltageOn(constants::fan_high_voltages[fly_bowl]);
}

void FlyBowlController::setFanOff(size_t fly_bowl)
{
  setHighVoltageOff(constants::fan_high_voltages[fly_bowl]);
}

void FlyBowlController::setIndicatorOn(size_t fly_bowl)
{
  setLowVoltageOn(constants::indicator_low_voltages[fly_bowl]);
}

void FlyBowlController::setIndicatorOff(size_t fly_bowl)
{
  setLowVoltageOff(constants::indicator_low_voltages[fly_bowl]);
}

// Handlers must be non-blocking (avoid 'delay')
//
// modular_server_.parameter(parameter_name).getValue(value) value type must be either:
// fixed-point number (int, long, etc.)
// floating-point number (float, double)
// bool
// const char *
// ArduinoJson::JsonArray *
// ArduinoJson::JsonObject *
// const ConstantString *
//
// For more info read about ArduinoJson parsing https://github.com/janelia-arduino/ArduinoJson
//
// modular_server_.property(property_name).getValue(value) value type must match the property default type
// modular_server_.property(property_name).setValue(value) value type must match the property default type
// modular_server_.property(property_name).getElementValue(element_index,value) value type must match the property array element default type
// modular_server_.property(property_name).setElementValue(element_index,value) value type must match the property array element default type

void FlyBowlController::setFlyBowlEnabledHandler(size_t fly_bowl)
{
  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

  if (!fly_bowl_enabled)
  {
    setIrBacklightOff(fly_bowl);
    setVisibleBacklightOff(fly_bowl);
  }
}

void FlyBowlController::setIrBacklightsOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setIrBacklightsOnAtPower(power);
}

void FlyBowlController::setIrBacklightsOnHandler(modular_server::Pin * pin_ptr)
{
  setIrBacklightsOn();
}

void FlyBowlController::setIrBacklightsOffHandler(modular_server::Pin * pin_ptr)
{
  setIrBacklightsOff();
}

void FlyBowlController::setVisibleBacklightsOnAtPowerHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setVisibleBacklightsOnAtPower(power);
}

void FlyBowlController::setVisibleBacklightsOnHandler(modular_server::Pin * pin_ptr)
{
  setVisibleBacklightsOn();
}

void FlyBowlController::setVisibleBacklightsOffHandler(modular_server::Pin * pin_ptr)
{
  setVisibleBacklightsOff();
}
