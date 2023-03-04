using namespace vex;

extern brain Brain;

// VEXcode devices
extern motor fl;
extern motor bl;
extern motor ml;
extern motor fr;
extern motor br;
extern motor mr;
extern controller Controller1;
extern motor catapult;
extern motor_group leftDrive;
extern motor_group rightDrive;
extern smartdrive Drivetrain;
extern motor intake;
extern inertial DrivetrainInertial;
extern digital_out expa;
extern encoder ltrack;
extern encoder rtrack;
extern limit Limit;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );