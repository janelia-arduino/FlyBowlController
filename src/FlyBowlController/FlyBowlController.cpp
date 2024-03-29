// ----------------------------------------------------------------------------
// FlyBowlController.cpp
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
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
  modular_server::Pin & btn_a_pin = modular_server_.pin(modular_device_base::constants::btn_a_pin_name);

  modular_server::Pin & btn_b_pin = modular_server_.pin(modular_device_base::constants::btn_b_pin_name);

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

  modular_server::Parameter & intensity_parameter = modular_server_.parameter(backlight_controller::constants::intensity_parameter_name);

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
  step_duration_parameter.setUnits(digital_controller::constants::ms_units);

  // Functions
  modular_server::Function & set_ir_backlights_and_fans_on_at_power_function = modular_server_.createFunction(constants::set_ir_backlights_and_fans_on_at_power_function_name);
  set_ir_backlights_and_fans_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::setIrBacklightsAndFansOnAtPowerHandler));
  set_ir_backlights_and_fans_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_ir_backlights_and_fans_on_at_intensity_function = modular_server_.createFunction(constants::set_ir_backlights_and_fans_on_at_intensity_function_name);
  set_ir_backlights_and_fans_on_at_intensity_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::setIrBacklightsAndFansOnAtIntensityHandler));
  set_ir_backlights_and_fans_on_at_intensity_function.addParameter(intensity_parameter);

  modular_server::Function & set_visible_backlights_and_indicators_on_at_power_function = modular_server_.createFunction(constants::set_visible_backlights_and_indicators_on_at_power_function_name);
  set_visible_backlights_and_indicators_on_at_power_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::setVisibleBacklightsAndIndicatorsOnAtPowerHandler));
  set_visible_backlights_and_indicators_on_at_power_function.addParameter(power_parameter);

  modular_server::Function & set_visible_backlights_and_indicators_on_at_intensity_function = modular_server_.createFunction(constants::set_visible_backlights_and_indicators_on_at_intensity_function_name);
  set_visible_backlights_and_indicators_on_at_intensity_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::setVisibleBacklightsAndIndicatorsOnAtIntensityHandler));
  set_visible_backlights_and_indicators_on_at_intensity_function.addParameter(intensity_parameter);

  modular_server::Function & add_visible_backlights_pwm_function = modular_server_.createFunction(constants::add_visible_backlights_pwm_function_name);
  add_visible_backlights_pwm_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::addVisibleBacklightsPwmHandler));
  add_visible_backlights_pwm_function.addParameter(intensity_parameter);
  add_visible_backlights_pwm_function.addParameter(pulse_delay_parameter);
  add_visible_backlights_pwm_function.addParameter(pulse_period_parameter);
  add_visible_backlights_pwm_function.addParameter(pulse_on_duration_parameter);
  add_visible_backlights_pwm_function.addParameter(pulse_count_parameter);
  add_visible_backlights_pwm_function.setResultTypeLong();

  modular_server::Function & add_experiment_step_function = modular_server_.createFunction(constants::add_experiment_step_function_name);
  add_experiment_step_function.attachFunctor(makeFunctor((Functor0 *)0,*this,&FlyBowlController::addExperimentStepHandler));
  add_experiment_step_function.addParameter(intensity_parameter);
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
  modular_server::Callback & set_ir_backlights_and_fans_on_callback = modular_server_.createCallback(constants::set_ir_backlights_and_fans_on_callback_name);
  set_ir_backlights_and_fans_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setIrBacklightsAndFansOnHandler));

  modular_server::Callback & set_ir_backlights_and_fans_off_callback = modular_server_.createCallback(constants::set_ir_backlights_and_fans_off_callback_name);
  set_ir_backlights_and_fans_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setIrBacklightsAndFansOffHandler));

  modular_server::Callback & toggle_ir_backlights_and_fans_callback = modular_server_.createCallback(constants::toggle_ir_backlights_and_fans_callback_name);
  toggle_ir_backlights_and_fans_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::toggleIrBacklightsAndFansHandler));
  toggle_ir_backlights_and_fans_callback.attachTo(btn_b_pin,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & set_visible_backlights_and_indicators_on_callback = modular_server_.createCallback(constants::set_visible_backlights_and_indicators_on_callback_name);
  set_visible_backlights_and_indicators_on_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setVisibleBacklightsAndIndicatorsOnHandler));

  modular_server::Callback & set_visible_backlights_and_indicators_off_callback = modular_server_.createCallback(constants::set_visible_backlights_and_indicators_off_callback_name);
  set_visible_backlights_and_indicators_off_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::setVisibleBacklightsAndIndicatorsOffHandler));

  modular_server::Callback & toggle_visible_backlights_and_indicators_callback = modular_server_.createCallback(constants::toggle_visible_backlights_and_indicators_callback_name);
  toggle_visible_backlights_and_indicators_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::toggleVisibleBacklightsAndIndicatorsHandler));
  toggle_visible_backlights_and_indicators_callback.attachTo(btn_a_pin,modular_server::constants::pin_mode_interrupt_falling);

  modular_server::Callback & remove_all_experiment_steps_callback = modular_server_.createCallback(constants::remove_all_experiment_steps_callback_name);
  remove_all_experiment_steps_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::removeAllExperimentStepsHandler));

  modular_server::Callback & run_experiment_callback = modular_server_.createCallback(constants::run_experiment_callback_name);
  run_experiment_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::runExperimentHandler));

  modular_server::Callback & stop_experiment_callback = modular_server_.createCallback(constants::stop_experiment_callback_name);
  stop_experiment_callback.attachFunctor(makeFunctor((Functor1<modular_server::Pin *> *)0,*this,&FlyBowlController::stopExperimentHandler));
}


void FlyBowlController::setIrBacklightAndFanOnAtPower(size_t fly_bowl,
  double power)
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
    size_t fly_bowl_ir_backlight = constants::fly_bowl_ir_backlights[fly_bowl];
    double power_lower_bound = getPowerLowerBound(irBacklightToDigitalChannel(fly_bowl_ir_backlight));
    if (power > power_lower_bound)
    {
      setFanOn(fly_bowl);
    }
    else
    {
      setFanOff(fly_bowl);
    }
    BacklightController::setIrBacklightOnAtPower(fly_bowl_ir_backlight,power);
  }
}

void FlyBowlController::setIrBacklightAndFanOnAtIntensity(size_t fly_bowl,
  double intensity)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  size_t fly_bowl_ir_backlight = constants::fly_bowl_ir_backlights[fly_bowl];
  double power = irBacklightIntensityToPower(fly_bowl_ir_backlight,intensity);
  setIrBacklightAndFanOnAtPower(fly_bowl,power);
}

void FlyBowlController::setIrBacklightAndFanOn(size_t fly_bowl)
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
    size_t fly_bowl_ir_backlight = constants::fly_bowl_ir_backlights[fly_bowl];
    double intensity = getIrBacklightIntensityWhenOn(fly_bowl_ir_backlight);
    double intensity_lower_bound = getIrBacklightIntensityLowerBound(fly_bowl_ir_backlight);
    if (intensity > intensity_lower_bound)
    {
      setFanOn(fly_bowl);
    }
    else
    {
      setFanOff(fly_bowl);
    }
    BacklightController::setIrBacklightOn(fly_bowl_ir_backlight);
  }
}

void FlyBowlController::setIrBacklightAndFanOff(size_t fly_bowl)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  size_t fly_bowl_ir_backlight = constants::fly_bowl_ir_backlights[fly_bowl];
  BacklightController::setIrBacklightOff(fly_bowl_ir_backlight);
  setFanOff(fly_bowl);
}

void FlyBowlController::toggleIrBacklightAndFan(size_t fly_bowl)
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
    size_t fly_bowl_ir_backlight = constants::fly_bowl_ir_backlights[fly_bowl];
    BacklightController::toggleIrBacklight(fly_bowl_ir_backlight);
    double intensity = getIrBacklightIntensity(fly_bowl_ir_backlight);
    double intensity_lower_bound = getIrBacklightIntensityLowerBound(fly_bowl_ir_backlight);
    if (intensity > intensity_lower_bound)
    {
      setFanOn(fly_bowl);
    }
    else
    {
      setFanOff(fly_bowl);
    }
  }
}

void FlyBowlController::setIrBacklightsAndFansOnAtPower(double power)
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setIrBacklightAndFanOnAtPower(fly_bowl,power);
  }
}

void FlyBowlController::setIrBacklightsAndFansOnAtIntensity(double intensity)
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setIrBacklightAndFanOnAtIntensity(fly_bowl,intensity);
  }
}

void FlyBowlController::setIrBacklightsAndFansOn()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setIrBacklightAndFanOn(fly_bowl);
  }
}

void FlyBowlController::setIrBacklightsAndFansOff()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setIrBacklightAndFanOff(fly_bowl);
  }
}

void FlyBowlController::toggleIrBacklightsAndFans()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    toggleIrBacklightAndFan(fly_bowl);
  }
}

void FlyBowlController::setVisibleBacklightAndIndicatorOnAtPower(size_t fly_bowl,
  double power)
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
    size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
    double power_lower_bound = getPowerLowerBound(visibleBacklightToDigitalChannel(fly_bowl_visible_backlight));
    if (power > power_lower_bound)
    {
      setIndicatorOn(fly_bowl);
    }
    else
    {
      setIndicatorOff(fly_bowl);
    }
    BacklightController::setVisibleBacklightOnAtPower(fly_bowl_visible_backlight,power);
  }
}

void FlyBowlController::setVisibleBacklightAndIndicatorOnAtIntensity(size_t fly_bowl,
  double intensity)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
  double power = visibleBacklightIntensityToPower(fly_bowl_visible_backlight,intensity);
  setVisibleBacklightAndIndicatorOnAtPower(fly_bowl,power);
}

void FlyBowlController::setVisibleBacklightAndIndicatorOn(size_t fly_bowl)
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
    size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
    double intensity = getVisibleBacklightIntensityWhenOn(fly_bowl_visible_backlight);
    double intensity_lower_bound = getVisibleBacklightIntensityLowerBound(fly_bowl_visible_backlight);
    if (intensity > intensity_lower_bound)
    {
      setIndicatorOn(fly_bowl);
    }
    else
    {
      setIndicatorOff(fly_bowl);
    }
    BacklightController::setVisibleBacklightOn(fly_bowl_visible_backlight);
  }
}

void FlyBowlController::setVisibleBacklightAndIndicatorOff(size_t fly_bowl)
{
  if (fly_bowl >= getFlyBowlCount())
  {
    return;
  }

  size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
  BacklightController::setVisibleBacklightOff(fly_bowl_visible_backlight);
  setIndicatorOff(fly_bowl);
}

void FlyBowlController::toggleVisibleBacklight(size_t fly_bowl)
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
    size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
    BacklightController::toggleVisibleBacklight(fly_bowl_visible_backlight);
    double intensity = getVisibleBacklightIntensity(fly_bowl_visible_backlight);
    double intensity_lower_bound = getVisibleBacklightIntensityLowerBound(fly_bowl_visible_backlight);
    if (intensity > intensity_lower_bound)
    {
      setIndicatorOn(fly_bowl);
    }
    else
    {
      setIndicatorOff(fly_bowl);
    }
  }
}

void FlyBowlController::setVisibleBacklightsAndIndicatorsOnAtPower(double power)
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setVisibleBacklightAndIndicatorOnAtPower(fly_bowl,power);
  }
}

void FlyBowlController::setVisibleBacklightsAndIndicatorsOnAtIntensity(double intensity)
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setVisibleBacklightAndIndicatorOnAtIntensity(fly_bowl,intensity);
  }
}

void FlyBowlController::setVisibleBacklightsAndIndicatorsOn()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setVisibleBacklightAndIndicatorOn(fly_bowl);
  }
}

void FlyBowlController::setVisibleBacklightsAndIndicatorsOff()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    setVisibleBacklightAndIndicatorOff(fly_bowl);
  }
}

void FlyBowlController::toggleVisibleBacklightsAndIndicators()
{
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    toggleVisibleBacklight(fly_bowl);
  }
}

digital_controller::constants::PwmId FlyBowlController::addVisibleBacklightsPwm(double intensity,
  long pulse_delay,
  long pulse_period,
  long pulse_on_duration,
  long pulse_count)
{
  uint32_t channels_dummy = 0;
  digital_controller::constants::PwmId pwm_id = addPwm(channels_dummy,
    intensity,
    pulse_delay,
    pulse_period,
    pulse_on_duration,
    pulse_count,
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::visibleBacklightAndIndicatorStartPulseHandler),
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::visibleBacklightAndIndicatorStopPulseHandler),
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::visibleBacklightAndIndicatorStartPwmHandler),
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::visibleBacklightAndIndicatorStopPwmHandler));
  if (pwm_id.index >= 0)
  {
    pwm_infos_[pwm_id.index].intensity = intensity;
  }
  return pwm_id;
}

int FlyBowlController::addExperimentStep(double intensity,
  long pulse_period,
  long pulse_on_duration,
  long pulse_count,
  long sequence_off_duration,
  long sequence_count,
  double step_delay,
  long step_duration)
{
  if (experiment_steps_.full())
  {
    return constants::NO_EXPERIMENT_STEP_SPACE_LEFT_INDEX;
  }
  constants::ExperimentStep experiment_step;
  experiment_step.intensity = intensity;
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

  stopAllPwm();
  event_controller_.clearAllEvents();
  setVisibleBacklightsAndIndicatorsOff();

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

  EventId stop_experiment_step_event_id = event_controller_.addEventUsingDelay(
    makeFunctor((Functor1<int> *)0,*this,&FlyBowlController::stopExperimentStepHandler),
    experiment_step.step_duration);
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

  experiment_status_.pwm_id = addVisibleBacklightsPwm(experiment_step.intensity,
    pulse_delay,
    experiment_step.pulse_period,
    experiment_step.pulse_on_duration,
    experiment_step.pulse_count);
}

void FlyBowlController::stopExperimentStep()
{
  event_controller_.clear(experiment_status_.start_sequence_event_id);
  stopPwm(experiment_status_.pwm_id);

  setVisibleBacklightsAndIndicatorsOff();

  experiment_status_.experiment_step_index++;
  const size_t experiment_step_index = experiment_status_.experiment_step_index;

  if (experiment_step_index == experiment_steps_.size())
  {
    stopExperiment();
    return;
  }
  startExperimentStep();
}

void FlyBowlController::setFlyBowlEnabledHandler(size_t fly_bowl)
{
  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

  if (!fly_bowl_enabled)
  {
    setIrBacklightAndFanOff(fly_bowl);
    setVisibleBacklightAndIndicatorOff(fly_bowl);
  }
}

void FlyBowlController::setIrBacklightsAndFansOnAtPowerHandler()
{
  double power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setIrBacklightsAndFansOnAtPower(power);
}

void FlyBowlController::setIrBacklightsAndFansOnAtIntensityHandler()
{
  double intensity;
  modular_server_.parameter(backlight_controller::constants::intensity_parameter_name).getValue(intensity);

  setIrBacklightsAndFansOnAtIntensity(intensity);
}

void FlyBowlController::setIrBacklightsAndFansOnHandler(modular_server::Pin * pin_ptr)
{
  setIrBacklightsAndFansOn();
}

void FlyBowlController::setIrBacklightsAndFansOffHandler(modular_server::Pin * pin_ptr)
{
  setIrBacklightsAndFansOff();
}

void FlyBowlController::toggleIrBacklightsAndFansHandler(modular_server::Pin * pin_ptr)
{
  toggleIrBacklightsAndFans();
}

void FlyBowlController::setVisibleBacklightsAndIndicatorsOnAtPowerHandler()
{
  double power;
  modular_server_.parameter(digital_controller::constants::power_parameter_name).getValue(power);

  setVisibleBacklightsAndIndicatorsOnAtPower(power);
}

void FlyBowlController::setVisibleBacklightsAndIndicatorsOnAtIntensityHandler()
{
  double intensity;
  modular_server_.parameter(backlight_controller::constants::intensity_parameter_name).getValue(intensity);

  setVisibleBacklightsAndIndicatorsOnAtIntensity(intensity);
}

void FlyBowlController::setVisibleBacklightsAndIndicatorsOnHandler(modular_server::Pin * pin_ptr)
{
  setVisibleBacklightsAndIndicatorsOn();
}

void FlyBowlController::setVisibleBacklightsAndIndicatorsOffHandler(modular_server::Pin * pin_ptr)
{
  setVisibleBacklightsAndIndicatorsOff();
}

void FlyBowlController::toggleVisibleBacklightsAndIndicatorsHandler(modular_server::Pin * pin_ptr)
{
  toggleVisibleBacklightsAndIndicators();
}

void FlyBowlController::addVisibleBacklightsPwmHandler()
{
  double intensity;
  modular_server_.parameter(backlight_controller::constants::intensity_parameter_name).getValue(intensity);
  long pulse_delay;
  modular_server_.parameter(constants::pulse_delay_parameter_name).getValue(pulse_delay);
  long pulse_period;
  modular_server_.parameter(constants::pulse_period_parameter_name).getValue(pulse_period);
  long pulse_on_duration;
  modular_server_.parameter(constants::pulse_on_duration_parameter_name).getValue(pulse_on_duration);
  long pulse_count;
  modular_server_.parameter(constants::pulse_count_parameter_name).getValue(pulse_count);

  digital_controller::constants::PwmId pwm_id = addVisibleBacklightsPwm(intensity,
    pulse_delay,
    pulse_period,
    pulse_on_duration,
    pulse_count);
  returnPwmIndexResponse(pwm_id.index);
}

void FlyBowlController::addExperimentStepHandler()
{
  double intensity;
  modular_server_.parameter(backlight_controller::constants::intensity_parameter_name).getValue(intensity);
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
  long step_duration;
  modular_server_.parameter(constants::step_duration_parameter_name).getValue(step_duration);

  int experiment_step_index = addExperimentStep(intensity,
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

    modular_server_.response().write(backlight_controller::constants::intensity_parameter_name,
      experiment_step.intensity);
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

void FlyBowlController::visibleBacklightAndIndicatorStartPulseHandler(int pwm_index)
{
  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

    if (fly_bowl_enabled)
    {
      size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
      double intensity = pwm_infos_[pwm_index].intensity;
      setVisibleBacklightAndIndicatorOnAtIntensity(fly_bowl_visible_backlight,intensity);
    }
  }
}

void FlyBowlController::visibleBacklightAndIndicatorStopPulseHandler(int pwm_index)
{
  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

    if (fly_bowl_enabled)
    {
      size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
      setVisibleBacklightOff(fly_bowl_visible_backlight);
    }
  }
}

void FlyBowlController::visibleBacklightAndIndicatorStartPwmHandler(int pwm_index)
{
}

void FlyBowlController::visibleBacklightAndIndicatorStopPwmHandler(int pwm_index)
{
  bool fly_bowl_enabled;
  modular_server::Property & fly_bowls_enabled_property = modular_server_.property(constants::fly_bowls_enabled_property_name);
  for (size_t fly_bowl=0; fly_bowl<getFlyBowlCount(); ++fly_bowl)
  {
    fly_bowls_enabled_property.getElementValue(fly_bowl,fly_bowl_enabled);

    if (fly_bowl_enabled)
    {
      size_t fly_bowl_visible_backlight = constants::fly_bowl_visible_backlights[fly_bowl];
      setVisibleBacklightAndIndicatorOff(fly_bowl_visible_backlight);
    }
  }

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
