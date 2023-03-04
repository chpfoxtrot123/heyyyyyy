#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain Brain;

// VEXcode device constructors
motor fl = motor(PORT11, ratio6_1, true);
motor ml = motor(PORT19, ratio6_1, true);
motor bl = motor(PORT20, ratio6_1, false);
motor fr = motor(PORT2, ratio6_1, false);
motor mr = motor(PORT17, ratio6_1, true);
motor br = motor(PORT18, ratio6_1, false);
inertial DrivetrainInertial = inertial(PORT12);
motor_group leftDrive = motor_group(fl, bl, ml);
motor_group rightDrive = motor_group(fr, br, mr);
smartdrive Drivetrain = smartdrive(leftDrive, rightDrive, DrivetrainInertial, 319.19, 320, 40, mm, 1);
controller Controller1 = controller(primary);
motor intake = motor(PORT1, ratio18_1, true);
motor catapult = motor(PORT21, ratio36_1, false);
encoder ltrack = encoder(Brain.ThreeWirePort.F);
encoder rtrack = encoder(Brain.ThreeWirePort.G);
limit Limit = limit(Brain.ThreeWirePort.D);

digital_out expa = digital_out(Brain.ThreeWirePort.C);

// VEXcode gg
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
   Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain Inertial
  wait(200, msec);
  DrivetrainInertial.calibrate();
  Brain.Screen.print("Calibrating Inertial for Drivetrain");
  // wait for the Inertial calibration process to finish
  while (DrivetrainInertial.isCalibrating()) {
    wait(25, msec);
  }
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}