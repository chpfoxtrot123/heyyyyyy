#include "vex.h"

const int THRESH = 10;
const int SCALE = 100;

void set_tank(int left, int right){
  fl.spin(forward, left*SCALE, voltageUnits::mV);
  ml.spin(forward, left*SCALE, voltageUnits::mV);
  bl.spin(forward, left*SCALE, voltageUnits::mV);
  fr.spin(forward, right*SCALE, voltageUnits::mV);
  mr.spin(forward, right*SCALE, voltageUnits::mV);
  br.spin(forward, right*SCALE, voltageUnits::mV);
}

void brake_drive(){
  fl.setStopping(brake);
  ml.setStopping(brake);
  bl.setStopping(brake);
  fr.setStopping(brake);
  mr.setStopping(brake);
  br.setStopping(brake);
}

void coast_drive(){
  fl.setStopping(coast);
  ml.setStopping(coast);
  bl.setStopping(coast);
  fr.setStopping(coast);
  mr.setStopping(coast);
  br.setStopping(coast);
}





void Cata(){
  catapult.setVelocity(50, pct);
  catapult.setStopping(hold);
  catapult.setMaxTorque(100, pct);
  if(Controller1.ButtonR1.pressing()){
    if(!R1Pressed){
      catapult.spin(fwd);
      Limit.released(catapultStop2);
    } 
  }else{
      R1Pressed = false;
  }if(!loaded){
    catapult.spin(fwd);
    loaded = true;
    Limit.pressed(catapultStop);
  }
  
}

void Intakes(){
  intake.setVelocity(100, pct);
  intake.setMaxTorque(100, pct);
  if(Controller1.ButtonL1.pressing()){
    intake.spin(fwd);
  }else if(Controller1.ButtonL2.pressing()){
    intake.spin(reverse);
  }else{
    intake.stop(coast);
  }
}

bool R1Pressed = false, loaded = false;
void catapultStop(){
  
  catapult.stop(hold);
}

void catapultStop2(){
  catapult.stop(hold);
  loaded = false;
}

void expansion(){
  if(Controller1.ButtonB.pressing()){
    expa.set(false);
  }
}

bool R2pressed = false;
void catapultTest(){
  catapult.setVelocity(100, pct);
  catapult.setMaxTorque(100, pct);
  if(Controller1.ButtonR2.pressing()){
    if(!R2pressed)
      catapult.spinFor(fwd, 3.0045*360, deg);
    R2pressed = true;
  }else{
    R2pressed = false;
  }
}


 

