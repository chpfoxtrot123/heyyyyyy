#include "vex.h"
double facing;

void spinRoller(int b, double a){
  if(b==-1)
    intake.spinFor(reverse, a, sec);
  if(b==0)
    intake.spinFor(fwd, a, sec);
}
void spinExpa(){
 // expa.setVelocity(90, pct);
 // expa.spinFor(fwd, 10, sec);
}

void strafeR(double rot){
  bl.spinFor(reverse, rot, deg, false);
  br.spinFor(fwd, rot, deg, false);
  fr.spinFor(reverse, rot, deg, false);
  fl.spinFor(fwd, rot, deg, true);
}
void strafeL(double rot){
  bl.spinFor(fwd, rot, deg, false);
  br.spinFor(reverse, rot, deg, false);
  fr.spinFor(fwd, rot, deg, false);
  fl.spinFor(reverse, rot, deg, true);
}

//these are for skills auto

void go(double a, double b, bool c){
  Drivetrain.setDriveVelocity(a, pct);
  Drivetrain.driveFor(forward, b, inches, c);
}
void turnRight(double a, double b){
  facing=DrivetrainInertial.heading();
  Drivetrain.setTurnVelocity(a, pct);
  if((DrivetrainInertial.heading()+b) >= 360){
    Drivetrain.turnToHeading(facing+b-360, degrees, true);
  }else if((DrivetrainInertial.heading()+b) < 360){
    Drivetrain.turnToHeading(facing+b, degrees, true);
  }
}
void turnLeft(double a, double b){
  facing=DrivetrainInertial.heading();
Drivetrain.setTurnVelocity(a, pct);
if((DrivetrainInertial.heading()-b) <= 0){
    Drivetrain.turnToHeading(facing-b+360, degrees, true);
  }else if((DrivetrainInertial.heading()+b) > 0){
    Drivetrain.turnToHeading(facing+b, degrees, true);
  }
}
void faceHeading(double a, double b){
  Drivetrain.setTurnVelocity(a, pct);
  Drivetrain.turnToHeading(b, degrees, true);
}
void eat(double a){
  intake.setVelocity(100,pct);
  intake.spinFor(a, degrees, false);
}

void test() {
  Controller1.Screen.print("tested");
}


bool load = false, stopped = false;
bool autocat = true;
int cata_auto() {
  while(autocat) {
    if(!load){
      catapult.spin(fwd);
      load = true;
    }
    if(Limit.pressing() && !stopped){
      stopped = true;
      catapultStop();
    } 
  }
  return 1;
}

void catapults(){
  catapult.stop(hold);
  load = false;
  stopped = false;
}

void shoot() {
  Controller1.Screen.print(stopped);
  catapult.spin(fwd);
  Limit.released(catapults);
}

void r() {
  enableDrivePD = true;
  vex::task PP(PDdrive);
  vex::task cc(cata_auto);
  PP.suspend();
  catapult.setVelocity(50, pct);
  catapult.setStopping(hold);
  catapult.setMaxTorque(100, pct);
  intake.setVelocity(90, pct);
  DrivetrainInertial.setHeading(0, deg);
  Drivetrain.setDriveVelocity(20, pct);

  Drivetrain.setTimeout(2.0, sec);
  Drivetrain.driveFor(7.0, inches, true);
  wait(100, msec);
  intake.spinFor(reverse, 150, deg);
  wait(100, msec);
  Drivetrain.driveFor(-7.0, inches, true);
  wait(100, msec);
  turnRight(30, 135);
  wait(100, msec);
  Drivetrain.setTimeout(5.0, sec);
  intake.spinFor(reverse, 5900, deg,false);
  Drivetrain.driveFor(40.0, inches, true);
  wait(100, msec);
  turnRight(30, -45);
  wait(100, msec);
  Drivetrain.driveFor(28.0, inches, true);
  wait(30, msec);
  Drivetrain.driveFor(3.0, inches, false);
  wait(100, msec);
  Drivetrain.driveFor(-10.0, inches, true);
  wait(100, msec);
  turnRight(30, 45);
  wait(100, msec);
  Drivetrain.driveFor(-20.0, inches, true);
  wait(100, msec);
  turnLeft(30, -90);
  wait(100, msec);
  expa.set(false);

  // PP.suspend();
  // Drivetrain.setDriveVelocity(15, pct);
  // Drivetrain.setTimeout(2.0, sec);
  // wait(1000, msec);
  // intake.setVelocity(100, pct);
  // intake.spinFor(reverse, 200, deg);
  // Drivetrain.driveFor(1.0, inches, false);
  // PP.suspend();
  // Drivetrain.setDriveVelocity(15, pct);
  // Drivetrain.setTimeout(2.0 , sec);
  // wait(1000, msec);//wait and roller 
  // Drivetrain.driveFor(1.0, inches, false);
  // intake.setVelocity(100, pct);
  // intake.spinFor(50, deg, true);//roller 
  // Drivetrain.driveFor(reverse, 5.0, inches,true);
  // wait(200,msec);
  
  // Drivetrain.setTimeout(5.0,sec);
  // PP.resume();
  // PD(1400, 1400);
  
}

//PD for drivetrain 
double kp = 0.0091;
double kd = 0.0055;

int desiredValue = 0;

int error;
int prevError = 0;  
int derivative;

bool enableDrivePD = true;
bool resetDriveSensors = false;
double lateralMotorPower=0;
void PD(double a, double t){//driving straight function
// don't use this function to drive for like very short distances(e.g. 6 inches or even 11)
  resetDriveSensors = true;//resets the motor positions
  desiredValue = a;// parameter a is the motor spinning value in degrees 
  //last time 1790 was the value for the robot to go from the very end to the mid point of the field
  // to use the value above about 1600 tho, use the overloaded function below and adjust the d value 
  //(add like idk 0.003 to the value now and see if it drives straight enough)
  
  wait(t, msec);// parameter t is the completion time for the driving in msec.
  Drivetrain.stop(brake); 
}//overloaded function of PID
void PD(double a, double p, double d, double t){
  resetDriveSensors = true;//resets the motor positions
  kp = p;// p = parameter for kp(directly responsible for speed)
  kd = d;// d = parameter for kd 
  desiredValue = a;
  wait(t, msec);
  //Drivetrain.stop(brake);
}

int PDdrive() {
  while(enableDrivePD){
    //reseting the sensor values mhm before we get down to business
  
    if(resetDriveSensors){
      resetDriveSensors = false;//switch off 
      fl.setPosition(0, deg);
      bl.setPosition(0,deg);
      ml.setPosition(0, deg);
      fr.setPosition(0,deg);
      br.setPosition(0, deg);
      mr.setPosition(0, deg);
      ltrack.setPosition(0, deg);
      rtrack.setPosition(0, deg);
    }
    //getting the position of the motors
 
    int flPos = fl.position(deg);
    int blPos = bl.position(deg);
    int mlPos = ml.position(deg);
    int frPos = fr.position(deg);
    int brPos = br.position(deg);
    int mrPos = mr.position(deg);
    int lPos = ltrack.position(deg);
    int rPos = rtrack.position(deg);

    //////////////////////////////////////////////////Lateral Movement PID...
    //Get the average
    int avgPos = (flPos + blPos + frPos + brPos + mrPos +mlPos + lPos + rPos)/8;
    //now comes the fun part
    //Proportional 
    error = avgPos - desiredValue; //displacement or pos
    //Derivative
    derivative = error - prevError;//takes the rate of change of the displacement, speed
    //Integral 
    // if(abs(error) < integralBound){ //if the distance is less than the bound
    //   totalError += error;
    // }else{
    //   totalError =0; //reset it to 0 
    // }

    // //let's cap the integral 
    // totalError = abs(totalError) > maxIntegral ? sign(totalError) * maxIntegral : totalError;
    //"control of the motors" statement
    lateralMotorPower = error*kp + derivative *kd;
    
    //////////////////////////////////////////////////////////////////////SPIN THEM ALL
    fl.spin(reverse, lateralMotorPower, voltageUnits::volt);
    bl.spin(reverse, lateralMotorPower, voltageUnits::volt);
    ml.spin(reverse, lateralMotorPower, voltageUnits::volt);
    fr.spin(reverse, lateralMotorPower, voltageUnits::volt);
    br.spin(reverse, lateralMotorPower, voltageUnits::volt);
    mr.spin(reverse, lateralMotorPower, voltageUnits::volt);
    prevError = error; //updates the prevError
    
   
    task::sleep(20); 
  }
  return 1;
}

