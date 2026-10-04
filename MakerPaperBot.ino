#include <Arduino.h>
#include <AccelStepper.h>
#include "pins_mightyboard_revh.h"


// DRIVER mode = a STEP pin and a DIR pin (what the BotStep drivers use).

static const long  MOVE_STEPS = 3200;   // ~1 rev at 1/16 microstepping
static const float MAX_SPEED  = 2000;   // steps per second
static const float ACCEL      = 4000;   // steps per second^2

AccelStepper yStepper(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper zStepper(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

static void setupAxis(AccelStepper &s, uint8_t enablePin) {
  s.setEnablePin(enablePin);
  s.setPinsInverted(false, false, true);  // third arg: enable is active LOW
  s.setMinPulseWidth(10);                 // microseconds, conservative
  s.setMaxSpeed(MAX_SPEED);
  s.setAcceleration(ACCEL);
  s.enableOutputs();                      // drives the enable pin LOW
  s.moveTo(MOVE_STEPS);
}

void setup() {
  setupAxis(yStepper, Y_ENABLE);
  setupAxis(zStepper, Z_ENABLE);
}

void loop() {
  // Reverse each axis when it reaches its target. run() must be called often.
  if (yStepper.distanceToGo() == 0) {
    yStepper.moveTo(yStepper.currentPosition() == 0 ? MOVE_STEPS : 0);
  }
  if (zStepper.distanceToGo() == 0) {
    zStepper.moveTo(zStepper.currentPosition() == 0 ? MOVE_STEPS : 0);
  }
  yStepper.run();
  zStepper.run();
}