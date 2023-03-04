/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\user                                             */
/*    Created:      Thu Nov 03 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// fl                   motor         10              
// bl                   motor         7               
// fr                   motor         1               
// br                   motor         2               
// Controller1          controller                    
// roller               motor         16              
// expa                 motor         18              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

competition Competition;

void pre_auton(){
  expa.set(true);
  intake.setVelocity(250, pct);
  vexcodeInit();
}


void autonomous() {
  l();
}

void usercontrol() {
  enableDrivePD = false;
  autocat = false;
  Controller1.ButtonA.pressed(expansion);
  while(1){
    Intakes();
    Cata();
    expansion();
    catapultTest();
    int ljoy, rjoy;
    if(true){
      if(abs(Controller1.Axis3.value()) > THRESH || abs(Controller1.Axis1.value()) > THRESH){
        ljoy = Controller1.Axis3.value()+Controller1.Axis1.value();
        rjoy = Controller1.Axis3.value() - Controller1.Axis1.value();
        set_tank(ljoy, rjoy);
      }else{
        set_tank(0,0);
        brake_drive();
      }
    }else{
      ljoy = abs(Controller1.Axis3.value()) > THRESH ? Controller1.Axis3.value() :0;
      rjoy = abs(Controller1.Axis2.value()) > THRESH ? Controller1.Axis2.value() :0;
      set_tank(ljoy, rjoy);
    }
    wait(20, msec);
  }
}

int main() {
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  pre_auton();

  while(true){
    // Controller2.Screen.print(flywheel.velocity(rpm));
    // Controller2.Screen.newLine();
    wait(100, msec);
  }
}
