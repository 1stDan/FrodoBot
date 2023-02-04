#include "vex.h"
#include "RobotFunctions.h"
#include "robot-config.h"


#include <iostream>
using namespace vex;

bool intaking = false;
bool intakePosition = false;
bool catapultWind = true;
long int prevValue = -1;

void catapultLogic() {
  if (catapultWind) {
    windUp();
  }

  if (rollerOptical.isNearObject()) {
    std::cout << rollerOptical.color() << std::endl;
  }

  controller1.ButtonL2.pressed(shootDisks);
  controller1.ButtonR1.pressed(intakeToggle);
  controller1.ButtonR2.pressed(reverseIntake);

  // intake logic
}

void manualWindUp() { thrower.spin(reverse, 100, pct); }

void manualStopThrower() { thrower.stop(); }

void windUp() {

  if (catapultLimit.value() == prevValue) {
    thrower.spin(reverse, 100, pct);
  } else {
    catapultWind = !catapultWind;
    thrower.stop();
  }
}

void shootDisks() {
  thrower.setTimeout(1200, msec);
  thrower.spinFor(reverse, 1200, msec);
  thrower.setTimeout(0, msec);
  catapultWind = true;
  prevValue = catapultLimit.value();
}

void intakeToggle() {
  if (intaking) {
    intake.stop();
  } else {
    if (intakePosition) {
      intake.spin(forward, 100, pct);
    } else {
      { intake.spin(reverse, 100, pct); }
    }
  }
  intaking = !intaking;
}

void reverseIntake() { intakePosition = !intakePosition; }

// bool doIntakeOut = false;
// bool doIntakeIn = false;
// bool intakeToggleBuffering = false;
// void intakeToggle(){
//   if(controller1.ButtonR1.pressing())
//   {
//     if (!intakeToggleBuffering) {

//       intakeToggleBuffering = true;
//       doIntakeOut = !doIntakeOut;
//       doIntakeIn = false;
//       if (doIntakeOut) {
//         controller1.rumble("-");
//       } else {
//         controller1.rumble("..");
//       }
//     }
//   }
//   else if (controller1.ButtonR2.pressing()) {
//     if (!intakeToggleBuffering) {
//       intakeToggleBuffering = true;
//       doIntakeIn = !doIntakeIn;
//       doIntakeOut = false;
//       if (doIntakeIn) {
//         controller1.rumble(".");
//       } else {
//         controller1.rumble("..");
//       }
//     }
//   }
//   else {
//     // controller1.rumble(".");
//     intakeToggleBuffering = false;
//   }

//   if (doIntakeOut) {
//     intake.spin(fwd, 100, pct);
//   } else if (doIntakeIn) {
//     intake.spin(directionType::rev, 100, pct);
//   } else {
//     intake.stop();
//   }
//  }
