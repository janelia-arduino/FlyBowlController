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

  // Experiment Status Setup
  resetExperimentStatus();

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

  initializeEnabledMasks();

  // Parameters
  modular_server::Parameter & power_parameter = modular_server_.parameter(digital_controller::constants::power_parameter_name);

  modular_server::Parameter & pulse_delay_parameter = modular_server_.createParameter(constants::pulse_delay_parameter_name);
  pulse_delay_parameter.setRange(constants::pulse_delay_min,constants::pulse_delay_max);
  pulse_delay_parameter.setUnits(digital_controller::constants::ms_units);

  modular_server::Parameter & pulse_period_parameter = modular_server_.createParameter(constants::pulse_period_parameter_name);
  pulse_period_parameter.setRange(constants::pulse_period_min,constants::pulse_period_max);
  pulse_period_parameter.setUnits(digital_controller::constants::ms_units);

  modular_server::Parameter & pulse_on_duration_parameter = modular_server_.createParameter(constants::pulse_on_duration_parameter_name);
  pulse_on_duration_parameter.setRange(constants::pulse_on_duration_min,constants::pulse_on_duration_max);
  pulse_on_duration_parameter.setUnits(digital_controller::constants::ms_units);

  modular_server::Parameter & pulse_count_parameter = modular_server_.createParameter(constants::pulse_count_parameter_name);
  pulse_count_parameter.setRange(constants::pulse_count_min,constants::pulse_count_max);
  pulse_count_parameter.setUnits(digital_controller::constants::ms_units);

  modular_server::Parameter & sequence_off_duration_parameter = modular_server_.createParameter(constants::sequence_off_duration_parameter_name);
  sequence_off_duration_parameter.setRange(constants::sequence_off_duration_min,constants::sequence_off_duration_max);
  sequence_off_duration_parameter.setUnits(digital_controller::constants::ms_units);

  modular_server::Parameter & sequence_count_parameter = modular_server_.createParameter(constants::sequence_count_parameter_name);
  sequence_count_parameter.setRange(constants::sequence_count_min,constants::sequence_count_max);
  sequence_count_parameter.setUnits(digital_controller::constants::ms_units);

  modular_server::Parameter & step_delay_parameter = modular_server_.createParameter(constants::step_delay_parameter_name);
  step_delay_parameter.setRange(constants::step_delay_min,constants::step_delay_max);
  step_delay_parameter.setUnits(constants::seconds_units);

  modular_server::Parameter & step_duration_parameter = modular_server_.createParameter(constants::step_duration_parameter_name);
  step_duration_parameter.setRange(constants::step_duration_min,constants::step_duration_max);
  step_duration_parameter.setUnits(constants::seconds_units);

  // Functions
  modular_server::Function & set_ir_backlights_on_at_power_function = modular_server_.createFunction(constants::set_ir_backlights_on_at_power_function_name);
  set_ir_backlights_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::setIrBacklightsOnAtPowerHandler));
  set_ir_backlights_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_visible_backlights_on_at_power_function = modular_server_.createFunction(constants::set_visible_backlights_on_at_power_function_name);
  set_visible_backlights_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::setVisibleBacklightsOnAtPowerHandler));
  set_visible_backlights_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & add_visible_backlights_pwm_function = modular_server_.createFunction(constants::add_visible_backlights_pwm_function_name);
  add_visible_backlights_pwm_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::addVisibleBacklightsPwmHandler));
  add_visible_backlights_pwm_function.addParameter(power_parameter);
  add_visible_backlights_pwm_function.addParameter(pulse_delay_parameter);
  add_visible_backlights_pwm_function.addParameter(pulse_period_parameter);
  add_visible_backlights_pwm_function.addParameter(pulse_on_duration_parameter);
  add_visible_backlights_pwm_function.addParameter(pulse_count_parameter);
  add_visible_backlights_pwm_function.setResultTypeLong();

  modular_server::Function & add_experiment_step_function = modular_server_.createFunction(constants::add_experiment_step_function_name);
  add_experiment_step_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::addExperimentStepHandler));
  add_experiment_step_function.addParameter(power_parameter);
  add_experiment_step_function.addParameter(pulse_period_parameter);
  add_experiment_step_function.addParameter(pulse_on_duration_parameter);
  add_experiment_step_function.addParameter(pulse_count_parameter);
  add_experiment_step_function.addParameter(sequence_off_duration_parameter);
  add_experiment_step_function.addParameter(sequence_count_parameter);
  add_experiment_step_function.addParameter(step_delay_parameter);
  add_experiment_step_function.addParameter(step_duration_parameter);
  add_experiment_step_function.setResultTypeLong();

  modular_server::Function & get_experiment_steps_function = modular_server_.createFunction(constants::get_experiment_steps_function_name);
  get_experiment_steps_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::getExperimentStepsHandler));
  get_experiment_steps_function.setResultTypeArray();
  get_experiment_steps_function.setResultTypeObject();

  modular_server::Function & get_experiment_status_function = modular_server_.createFunction(constants::get_experiment_status_function_name);
  get_experiment_status_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::getExperimentStatusHandler));
  get_experiment_status_function.setResultTypeObject();

  // Callbacks
  modular_server::Callback & set_ir_backlights_on_callback = modular_server_.createCallback(constants::set_ir_backlights_on_callback_name);
  set_ir_backlights_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setIrBacklightsOnHandler));

  modular_server::Callback & set_ir_backlights_off_callback = modular_server_.createCallback(constants::set_ir_backlights_off_callback_name);
  set_ir_backlights_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setIrBacklightsOffHandler));

  modular_server::Callback & set_visible_backlights_on_callback = modular_server_.createCallback(constants::set_visible_backlights_on_callback_name);
  set_visible_backlights_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setVisibleBacklightsOnHandler));

  modular_server::Callback & set_visible_backlights_off_callback = modular_server_.createCallback(constants::set_visible_backlights_off_callback_name);
  set_visible_backlights_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setVisibleBacklightsOffHandler));

  modular_server::Callback & remove_all_experiment_steps_callback = modular_server_.createCallback(constants::remove_all_experiment_steps_callback_name);
  remove_all_experiment_steps_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::removeAllExperimentStepsHandler));

  modular_server::Callback & run_experiment_callback = modular_server_.createCallback(constants::run_experiment_callback_name);
  run_experiment_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::runExperimentHandler));

  modular_server::Callback & stop_experiment_callback = modular_server_.createCallback(constants::stop_experiment_callback_name);
  stop_experiment_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::stopExperimentHandler));
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

digital_controller::constants::PwmId FlyBowlController::addVisibleBacklightsPwm(long power,
  long pulse_delay,
  long pulse_period,
  long pulse_on_duration,
  long pulse_count)
{
  uint32_t visible_backlight_channels = 0;
  uint32_t indicator_channels = 0;
  const uint32_t bit = 1;
  size_t channel;
  size_t fly_bowl_visible_backlight;
  size_t indicator_low_voltage;
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
    channel = visibleBacklightToDigitalChannel(fly_bowl_visible_backlight);
    visible_backlight_channels |= (bit << channel);

    indicator_low_voltage = constants::indicator_low_voltages[fly_bowl];
    channel = lowVoltageToDigitalChannel(indicator_low_voltage);
    indicator_channels |= (bit << channel);
  }
  digital_controller::constants::PwmId pwm_id = addPwm(visible_backlight_channels,
    power,
    pulse_delay,
    pulse_period,
    pulse_on_duration,
    pulse_count,
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::visibleBacklightStartPulseHandler),
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::visibleBacklightStopPulseHandler),
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::visibleBacklightStartPwmHandler),
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::visibleBacklightStopPwmHandler));
  if (pwm_id.index >= 0)
  {
    pwm_infos_[pwm_id.index].visible_backlight_channels = visible_backlight_channels;
    pwm_infos_[pwm_id.index].power = power;
    pwm_infos_[pwm_id.index].indicator_channels = indicator_channels;
  }
  return pwm_id;
}

int FlyBowlController::addExperimentStep(long power,
  long pulse_period,
  long pulse_on_duration,
  long pulse_count,
  long sequence_off_duration,
  long sequence_count,
  double step_delay,
  double step_duration)
{
  if (experiment_steps_.full())
  {
    return constants::NO_EXPERIMENT_STEP_SPACE_LEFT_INDEX;
  }
  constants::ExperimentStep experiment_step;
  experiment_step.power = power;
  experiment_step.pulse_period = pulse_period;
  experiment_step.pulse_on_duration = pulse_on_duration;
  experiment_step.pulse_count = pulse_count;
  experiment_step.sequence_off_duration = sequence_off_duration;
  experiment_step.sequence_count = sequence_count;
  experiment_step.step_delay = step_delay;
  experiment_step.step_duration = step_duration;

  experiment_steps_.push_back(experiment_step);

  int experiment_step_index = experiment_steps_.size() - 1;
  return experiment_step_index;
}

void FlyBowlController::removeAllExperimentSteps()
{
  experiment_steps_.clear();
}

void FlyBowlController::runExperiment()
{
  if ((experiment_steps_.size() == 0) || (event_controller_.eventsAvailable() == 0))
  {
    return;
  }

  startExperiment();
}

void FlyBowlController::stopExperiment()
{
  stopAllPwm();
  event_controller_.clearAllEvents();
  resetExperimentStatus();
}

constants::ExperimentStatus FlyBowlController::getExperimentStatus()
{
  return experiment_status_;
}

void FlyBowlController::initializeEnabledMasks()
{
  ir_backlights_enabled_mask_ = 0;
  visible_backlights_enabled_mask_ = 0;
  high_voltages_enabled_mask_ = 0;
  low_voltages_enabled_mask_ = 0;

  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);

  const uint32_t bit = 1;
  size_t channel;
  size_t fly_bowl_ir_backlight;
  size_t fly_bowl_visible_backlight;
  size_t fan_high_voltage;
  size_t indicator_low_voltage;
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

    if (fly_bowl_enabled)
    {
      fly_bowl_ir_backlight = constants::fly_bowl_ir_backlights[fly_bowl];
      channel = irBacklightToDigitalChannel(fly_bowl_ir_backlight);
      ir_backlights_enabled_mask_ |= (bit << channel);

      fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
      channel = visibleBacklightToDigitalChannel(fly_bowl_visible_backlight);
      visible_backlights_enabled_mask_ |= (bit << channel);

      fan_high_voltage = constants::fan_high_voltages[fly_bowl];
      channel = highVoltageToDigitalChannel(fan_high_voltage);
      high_voltages_enabled_mask_ |= (bit << channel);

      indicator_low_voltage = constants::indicator_low_voltages[fly_bowl];
      channel = lowVoltageToDigitalChannel(indicator_low_voltage);
      low_voltages_enabled_mask_ |= (bit << channel);
    }
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

void FlyBowlController::resetExperimentStatus()
{
  experiment_status_.state_ptr = &constants::state_experiment_not_running_string;
  experiment_status_.experiment_step_index = 0;
  experiment_status_.sequence_index = 0;
  experiment_status_.sequence_count = 0;
}

void FlyBowlController::startExperiment()
{
  experiment_status_.state_ptr = &constants::state_experiment_running_string;

  startExperimentStep();
}

void FlyBowlController::startExperimentStep()
{
  if (event_controller_.eventsAvailable() == 0)
  {
    stopExperiment();
    return;
  }

  const size_t experiment_step_index = experiment_status_.experiment_step_index;
  const constants::ExperimentStep experiment_step = experiment_steps_[experiment_step_index];

  experiment_status_.sequence_index = 0;
  experiment_status_.sequence_count = experiment_step.sequence_count;

  long sequence_delay = experiment_step.step_delay * constants::ms_per_second;

  long sequence_period = experiment_step.pulse_period * experiment_step.pulse_count;
  sequence_period += experiment_step.sequence_off_duration;

  experiment_status_.start_sequence_event_id = event_controller_.addRecurringEventUsingDelay(
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::startSequenceHandler),
    sequence_delay,
    sequence_period,
    experiment_step.sequence_count);
  event_controller_.enable(experiment_status_.start_sequence_event_id);

  long step_duration_ms = experiment_step.step_duration * constants::ms_per_second;

  EventId stop_experiment_step_event_id = event_controller_.addEventUsingDelay(
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::stopExperimentStepHandler),
    step_duration_ms);
  event_controller_.enable(stop_experiment_step_event_id);
}

void FlyBowlController::startSequence()
{
  if (event_controller_.eventsAvailable() == 0)
  {
    stopExperiment();
    return;
  }

  const size_t experiment_step_index = experiment_status_.experiment_step_index;
  const constants::ExperimentStep experiment_step = experiment_steps_[experiment_step_index];

  long pulse_delay = 0;

  experiment_status_.pwm_id = addVisibleBacklightsPwm(experiment_step.power,
    pulse_delay,
    experiment_step.pulse_period,
    experiment_step.pulse_on_duration,
    experiment_step.pulse_count);
}

void FlyBowlController::stopExperimentStep()
{
  event_controller_.clear(experiment_status_.start_sequence_event_id);
  stopPwm(experiment_status_.pwm_id);

  setVisibleBacklightsOff();

  experiment_status_.experiment_step_index++;
  const size_t experiment_step_index = experiment_status_.experiment_step_index;

  if (experiment_step_index == experiment_steps_.size())
  {
    stopExperiment();
    return;
  }
  startExperimentStep();
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
  const uint32_t bit = 1;
  size_t channel;
  size_t fly_bowl_ir_backlight = constants::fly_bowl_ir_backlights[fly_bowl];
  channel = irBacklightToDigitalChannel(fly_bowl_ir_backlight);
  if (fly_bowl_enabled)
  {
    ir_backlights_enabled_mask_ |= (bit << channel);
  }
  else
  {
    ir_backlights_enabled_mask_ &= ~(bit << channel);
  }

  size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
  channel = visibleBacklightToDigitalChannel(fly_bowl_visible_backlight);
  if (fly_bowl_enabled)
  {
    visible_backlights_enabled_mask_ |= (bit << channel);
  }
  else
  {
    visible_backlights_enabled_mask_ &= ~(bit << channel);
  }

  size_t fan_high_voltage = constants::fan_high_voltages[fly_bowl];
  channel = highVoltageToDigitalChannel(fan_high_voltage);
  if (fly_bowl_enabled)
  {
    high_voltages_enabled_mask_ |= (bit << channel);
  }
  else
  {
    high_voltages_enabled_mask_ &= ~(bit << channel);
  }

  size_t indicator_low_voltage = constants::indicator_low_voltages[fly_bowl];
  channel = lowVoltageToDigitalChannel(indicator_low_voltage);
  if (fly_bowl_enabled)
  {
    low_voltages_enabled_mask_ |= (bit << channel);
  }
  else
  {
    low_voltages_enabled_mask_ &= ~(bit << channel);
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

void FlyBowlController::addVisibleBacklightsPwmHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);
  long pulse_delay;
  modular_server_.parameter(constants::pulse_delay_parameter_name).getValue(pulse_delay);
  long pulse_period;
  modular_server_.parameter(constants::pulse_period_parameter_name).getValue(pulse_period);
  long pulse_on_duration;
  modular_server_.parameter(constants::pulse_on_duration_parameter_name).getValue(pulse_on_duration);
  long pulse_count;
  modular_server_.parameter(constants::pulse_count_parameter_name).getValue(pulse_count);

  digital_controller::constants::PwmId pwm_id = addVisibleBacklightsPwm(power,
    pulse_delay,
    pulse_period,
    pulse_on_duration,
    pulse_count);
  returnPwmIndexResponse(pwm_id.index);
}

void FlyBowlController::addExperimentStepHandler()
{
  long power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);
  long pulse_period;
  modular_server_.parameter(constants::pulse_period_parameter_name).getValue(pulse_period);
  long pulse_on_duration;
  modular_server_.parameter(constants::pulse_on_duration_parameter_name).getValue(pulse_on_duration);
  long pulse_count;
  modular_server_.parameter(constants::pulse_count_parameter_name).getValue(pulse_count);
  long sequence_off_duration;
  modular_server_.parameter(constants::sequence_off_duration_parameter_name).getValue(sequence_off_duration);
  long sequence_count;
  modular_server_.parameter(constants::sequence_count_parameter_name).getValue(sequence_count);
  double step_delay;
  modular_server_.parameter(constants::step_delay_parameter_name).getValue(step_delay);
  double step_duration;
  modular_server_.parameter(constants::step_duration_parameter_name).getValue(step_duration);

  int experiment_step_index = addExperimentStep(power,
    pulse_period,
    pulse_on_duration,
    pulse_count,
    sequence_off_duration,
    sequence_count,
    step_delay,
    step_duration);

  if (experiment_step_index == constants::NO_EXPERIMENT_STEP_SPACE_LEFT_INDEX)
  {
    modular_server_.response().returnError(constants::no_experiment_step_space_left_error);
  }
  else
  {
    modular_server_.response().returnResult(experiment_step_index);
  }
}

void FlyBowlController::getExperimentStepsHandler()
{
  modular_server_.response().writeResultKey();
  modular_server_.response().beginArray();

  for (size_t step_i=0; step_i<experiment_steps_.size(); ++step_i)
  {
    constants::ExperimentStep & experiment_step = experiment_steps_[step_i];
    modular_server_.response().beginObject();

    modular_server_.response().write(digital_controller::constants::power_parameter_name,
      experiment_step.power);
    modular_server_.response().write(constants::pulse_period_parameter_name,
      experiment_step.pulse_period);
    modular_server_.response().write(constants::pulse_on_duration_parameter_name,
      experiment_step.pulse_on_duration);
    modular_server_.response().write(constants::pulse_count_parameter_name,
      experiment_step.pulse_count);
    modular_server_.response().write(constants::sequence_off_duration_parameter_name,
      experiment_step.sequence_off_duration);
    modular_server_.response().write(constants::sequence_count_parameter_name,
      experiment_step.sequence_count);
    modular_server_.response().write(constants::step_delay_parameter_name,
      experiment_step.step_delay);
    modular_server_.response().write(constants::step_duration_parameter_name,
      experiment_step.step_duration);

    modular_server_.response().endObject();
  }

  modular_server_.response().endArray();

}

void FlyBowlController::getExperimentStatusHandler()
{
  constants::ExperimentStatus experiment_status = experiment_status_;

  modular_server_.response().writeResultKey();

  modular_server_.response().beginObject();

  modular_server_.response().write(constants::state_string,
    experiment_status.state_ptr);
  modular_server_.response().write(constants::experiment_step_index_string,
    experiment_status.experiment_step_index);
  modular_server_.response().write(constants::experiment_step_count_string,
    experiment_steps_.size());
  modular_server_.response().write(constants::sequence_index_string,
    experiment_status.sequence_index);
  modular_server_.response().write(constants::sequence_count_string,
    experiment_status.sequence_count);

  modular_server_.response().endObject();
}

void FlyBowlController::removeAllExperimentStepsHandler(modular_server::Pin * pin_ptr)
{
  removeAllExperimentSteps();
}

void FlyBowlController::runExperimentHandler(modular_server::Pin * pin_ptr)
{
  runExperiment();
}

void FlyBowlController::stopExperimentHandler(modular_server::Pin * pin_ptr)
{
  stopExperiment();
}

void FlyBowlController::visibleBacklightStartPulseHandler(int pwm_index)
{
  uint32_t visible_backlight_channels = pwm_infos_[pwm_index].visible_backlight_channels;
  visible_backlight_channels &= visible_backlights_enabled_mask_;
  long power = pwm_infos_[pwm_index].power;
  setChannelsOnAtPower(visible_backlight_channels,power);

  uint32_t indicator_channels = pwm_infos_[pwm_index].indicator_channels;
  indicator_channels &= low_voltages_enabled_mask_;
  setChannelsOn(indicator_channels);
}

void FlyBowlController::visibleBacklightStopPulseHandler(int pwm_index)
{
  uint32_t visible_backlight_channels = pwm_infos_[pwm_index].visible_backlight_channels;
  visible_backlight_channels &= visible_backlights_enabled_mask_;
  setChannelsOff(visible_backlight_channels);
}

void FlyBowlController::visibleBacklightStartPwmHandler(int pwm_index)
{
}

void FlyBowlController::visibleBacklightStopPwmHandler(int pwm_index)
{
  uint32_t visible_backlight_channels = pwm_infos_[pwm_index].visible_backlight_channels;
  visible_backlight_channels &= visible_backlights_enabled_mask_;
  setChannelsOff(visible_backlight_channels);

  uint32_t indicator_channels = pwm_infos_[pwm_index].indicator_channels;
  indicator_channels &= low_voltages_enabled_mask_;
  setChannelsOff(indicator_channels);

  if (experiment_status_.state_ptr == &constants::state_experiment_running_string)
  {
    experiment_status_.sequence_index++;
  }
}

void FlyBowlController::startSequenceHandler(int arg)
{
  startSequence();
}

void FlyBowlController::stopExperimentStepHandler(int arg)
{
  stopExperimentStep();
}
