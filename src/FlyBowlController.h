// ----------------------------------------------------------------------------
// FlyBowlController.h
//
//
// Authors:
// Peter Polidoro peter@polidoro.io
// ----------------------------------------------------------------------------
#ifndef FLY_BOWL_CONTROLLER_H
#define FLY_BOWL_CONTROLLER_H
#include <ArduinoJson.h>
#include <JsonStream.h>
#include <Array.h>
#include <Vector.h>
#include <ConstantVariable.h>
#include <Functor.h>

#include <ModularServer.h>
#include <ModularDeviceBase.h>
#include <DigitalController.h>
#include <BacklightController.h>

#include "FlyBowlController/Constants.h"


class FlyBowlController : public BacklightController
{
public:
  FlyBowlController();
  virtual void setup();

  void setIrBacklightAndFanOnAtPower(size_t fly_bowl,
    double power);
  void setIrBacklightAndFanOnAtIntensity(size_t fly_bowl,
    double intensity);
  void setIrBacklightAndFanOn(size_t fly_bowl);
  void setIrBacklightAndFanOff(size_t fly_bowl);
  void toggleIrBacklightAndFan(size_t fly_bowl);
  void setIrBacklightsAndFansOnAtPower(double power);
  void setIrBacklightsAndFansOnAtIntensity(double intensity);
  void setIrBacklightsAndFansOn();
  void setIrBacklightsAndFansOff();
  void toggleIrBacklightsAndFans();

  void setVisibleBacklightAndIndicatorOnAtPower(size_t fly_bowl,
    double power);
  void setVisibleBacklightAndIndicatorOnAtIntensity(size_t fly_bowl,
    double intensity);
  void setVisibleBacklightAndIndicatorOn(size_t fly_bowl);
  void setVisibleBacklightAndIndicatorOff(size_t fly_bowl);
  void toggleVisibleBacklight(size_t fly_bowl);
  void setVisibleBacklightsAndIndicatorsOnAtPower(double power);
  void setVisibleBacklightsAndIndicatorsOnAtIntensity(double intensity);
  void setVisibleBacklightsAndIndicatorsOn();
  void setVisibleBacklightsAndIndicatorsOff();
  void toggleVisibleBacklightsAndIndicators();

  digital_controller::constants::PwmId addVisibleBacklightsPwm(double intensity,
    long pulse_delay,
    long pulse_period,
    long pulse_on_duration,
    long pulse_count);

  int addExperimentStep(double intensity,
    long pulse_period,
    long pulse_on_duration,
    long pulse_count,
    long sequence_off_duration,
    long sequence_count,
    double step_delay,
    long step_duration);

  void removeAllExperimentSteps();
  void runExperiment();
  void stopExperiment();
  fly_bowl_controller::constants::ExperimentStatus getExperimentStatus();

private:
  modular_server::Property properties_[fly_bowl_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[fly_bowl_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[fly_bowl_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[fly_bowl_controller::constants::CALLBACK_COUNT_MAX];

  fly_bowl_controller::constants::PwmInfo pwm_infos_[digital_controller::constants::INDEXED_PWM_COUNT_MAX];

  Array<fly_bowl_controller::constants::ExperimentStep,
    fly_bowl_controller::constants::EXPERIMENT_STEP_COUNT_MAX> experiment_steps_;

  fly_bowl_controller::constants::ExperimentStatus experiment_status_;

  size_t getFlyBowlCount();

  void setFanOn(size_t fly_bowl);
  void setFanOff(size_t fly_bowl);

  void setIndicatorOn(size_t fly_bowl);
  void setIndicatorOff(size_t fly_bowl);

  void resetExperimentStatus();

  void startExperiment();
  void startExperimentStep();
  void startSequence();
  void stopExperimentStep();

  // Handlers
  void setFlyBowlEnabledHandler(size_t fly_bowl);
  void setIrBacklightsAndFansOnAtPowerHandler();
  void setIrBacklightsAndFansOnAtIntensityHandler();
  void setIrBacklightsAndFansOnHandler(modular_server::Pin * pin_ptr);
  void setIrBacklightsAndFansOffHandler(modular_server::Pin * pin_ptr);
  void toggleIrBacklightsAndFansHandler(modular_server::Pin * pin_ptr);
  void setVisibleBacklightsAndIndicatorsOnAtPowerHandler();
  void setVisibleBacklightsAndIndicatorsOnAtIntensityHandler();
  void setVisibleBacklightsAndIndicatorsOnHandler(modular_server::Pin * pin_ptr);
  void setVisibleBacklightsAndIndicatorsOffHandler(modular_server::Pin * pin_ptr);
  void toggleVisibleBacklightsAndIndicatorsHandler(modular_server::Pin * pin_ptr);
  void addVisibleBacklightsPwmHandler();
  void addExperimentStepHandler();
  void getExperimentStepsHandler();
  void getExperimentStatusHandler();
  void removeAllExperimentStepsHandler(modular_server::Pin * pin_ptr);
  void runExperimentHandler(modular_server::Pin * pin_ptr);
  void stopExperimentHandler(modular_server::Pin * pin_ptr);

  void visibleBacklightAndIndicatorStartPulseHandler(int pwm_index);
  void visibleBacklightAndIndicatorStopPulseHandler(int pwm_index);
  void visibleBacklightAndIndicatorStartPwmHandler(int pwm_index);
  void visibleBacklightAndIndicatorStopPwmHandler(int pwm_index);

  void startSequenceHandler(int arg);
  void stopExperimentStepHandler(int arg);
};

#endif
