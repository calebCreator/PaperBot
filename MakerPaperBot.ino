#include <Arduino.h>
#include <AccelStepper.h>
#include "pins_mightyboard_revh.h"


// DRIVER mode = a STEP pin and a DIR pin (what the BotStep drivers use).

static const long  STEPS_PER_REV = 200 * 16;   // ~1 rev at 1/16 microstepping
static const float MAX_SPEED  = 2000;   // steps per second
static const float ACCEL      = 8000;   // steps per second^2


//Create stepper motor objects
AccelStepper yStepper(AccelStepper::DRIVER, Y_STEP_PIN, Y_DIR_PIN);
AccelStepper zStepper(AccelStepper::DRIVER, Z_STEP_PIN, Z_DIR_PIN);

static void initStepper(AccelStepper &s, uint8_t enablePin) {
  s.setEnablePin(enablePin);
  s.setPinsInverted(false, false, true);  // third arg: enable is active LOW
  s.setMinPulseWidth(10);                 // microseconds, conservative
  s.setMaxSpeed(MAX_SPEED);
  s.setAcceleration(ACCEL);
  s.enableOutputs();                      // drives the enable pin LOW, to enable the stepper motor
  s.moveTo(0);
}

void setup() {
  initStepper(yStepper, Y_ENABLE);
  initStepper(zStepper, Z_ENABLE);
}

// void loop() {
//   // Reverse each axis when it reaches its target. run() must be called often.
//   if (yStepper.distanceToGo() == 0) {
//     if (yStepper.currentPosition() == 0) {
//       yStepper.moveTo(STEPS_PER_REV);
//     } else {
//       yStepper.moveTo(0);
//     }
//   }
//   if (zStepper.distanceToGo() == 0) {
//     if (zStepper.currentPosition() == 0) {
//       zStepper.moveTo(STEPS_PER_REV);
//     } else {
//       zStepper.moveTo(0);
//     }
//   }
//   yStepper.run();
//   zStepper.run();
// }

//This function runs a stepper until it reaches its target position
void run_to_target(AccelStepper *steppers[], int count){
  bool anyLeft = true;
  while (anyLeft){
    anyLeft = false;
    for (int i = 0; i < count; i++){
      steppers[i]->run();
      if(steppers[i]->distanceToGo() != 0){
        //Flag that loop still needs to wait
        anyLeft = true;
      }
    }
  }
}

void run_to_target(AccelStepper &a) {
  AccelStepper *list[] = {&a};
  run_to_target(list, 1);
}

int targets[] = {0, int(STEPS_PER_REV/4), STEPS_PER_REV/2};
int num_targets = sizeof(targets)/ sizeof(targets[0]); //Calculate real size

AccelStepper *steppers[] = {&yStepper, &zStepper};
int num_steppers = sizeof(steppers)/ sizeof(steppers[0]);

// void loop() {
//   //Set target position
//   yStepper.moveTo(STEPS_PER_REV * 2);
//   //Repeat until at position
//   run_to_target(yStepper);

//   delay(1000);

//   //Set target position
//   yStepper.moveTo(0);
//   //Repeat until at position
//   run_to_target(yStepper);

//   delay(1000);
  
// }
// Like delay(ms), but keeps stepping every stepper toward its target.
void run_for(AccelStepper *steppers[], int count, unsigned long ms) {
  unsigned long start = millis();
  while (millis() - start < ms) {
    for (int i = 0; i < count; i++) {
      steppers[i]->run();
    }
  }
}

// Single-motor wrapper.
void run_for(AccelStepper &s, unsigned long ms) {
  AccelStepper *list[] = { &s };
  run_for(list, 1, ms);
}


void loop(){
  for(int i = 0; i < num_targets; i++){
    yStepper.moveTo(long(targets[i]));
    zStepper.moveTo(-targets[i]);
    run_to_target(steppers, num_steppers);
    run_for(steppers, num_steppers, 200);
  }
  //run_for(steppers, num_steppers, 1000);
}
