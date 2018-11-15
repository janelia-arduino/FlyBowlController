// ----------------------------------------------------------------------------
// FlyBowlController.h
//
//
// Authors:
// Peter Polidoro peterpolidoro@gmail.com
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

  void setIrBacklightOnAtIntensity(size_t fly_bowl,
    double intensity);
  void setIrBacklightOn(size_t fly_bowl);
  void setIrBacklightOff(size_t fly_bowl);
  void toggleIrBacklight(size_t fly_bowl);
  void setIrBacklightsOnAtIntensity(double intensity);
  void setIrBacklightsOn();
  void setIrBacklightsOff();
  void toggleIrBacklights();

  void setVisibleBacklightOnAtIntensity(size_t fly_bowl,
    double intensity);
  void setVisibleBacklightOn(size_t fly_bowl);
  void setVisibleBacklightOff(size_t fly_bowl);
  void toggleVisibleBacklight(size_t fly_bowl);
  void setVisibleBacklightsOnAtIntensity(double intensity);
  void setVisibleBacklightsOn();
  void setVisibleBacklightsOff();
  void toggleVisibleBacklights();

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
    double step_duration);

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
  void setIrBacklightsOnAtIntensityHandler();
  void setIrBacklightsOnHandler(modular_server::Pin * pin_ptr);
  void setIrBacklightsOffHandler(modular_server::Pin * pin_ptr);
  void toggleIrBacklightsHandler(modular_server::Pin * pin_ptr);
  void setVisibleBacklightsOnAtIntensityHandler();
  void setVisibleBacklightsOnHandler(modular_server::Pin * pin_ptr);
  void setVisibleBacklightsOffHandler(modular_server::Pin * pin_ptr);
  void toggleVisibleBacklightsHandler(modular_server::Pin * pin_ptr);
  void addVisibleBacklightsPwmHandler();
  void addExperimentStepHandler();
  void getExperimentStepsHandler();
  void getExperimentStatusHandler();
  void removeAllExperimentStepsHandler(modular_server::Pin * pin_ptr);
  void runExperimentHandler(modular_server::Pin * pin_ptr);
  void stopExperimentHandler(modular_server::Pin * pin_ptr);

  void visibleBacklightStartPulseHandler(int pwm_index);
  void visibleBacklightStopPulseHandler(int pwm_index);
  void visibleBacklightStartPwmHandler(int pwm_index);
  void visibleBacklightStopPwmHandler(int pwm_index);

  void startSequenceHandler(int arg);
  void stopExperimentStepHandler(int arg);
};

#endif
