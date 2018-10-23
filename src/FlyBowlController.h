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

private:
  modular_server::Property properties_[fly_bowl_controller::constants::PROPERTY_COUNT_MAX];
  modular_server::Parameter parameters_[fly_bowl_controller::constants::PARAMETER_COUNT_MAX];
  modular_server::Function functions_[fly_bowl_controller::constants::FUNCTION_COUNT_MAX];
  modular_server::Callback callbacks_[fly_bowl_controller::constants::CALLBACK_COUNT_MAX];

  // Handlers

};

#endif
