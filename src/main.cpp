#include "main.h"
extern bool WallMechPid;
bool TrackerOn = true;
extern bool Toggle_GUI;
void UI_Touch() {
	 pros::screen_touch_status_s_t status = pros::screen::touch_status();
	 pros::screen::set_pen(pros::Color::green);
	 Touch_Checker(status.x, status.y);
 }
void GUI(void* param)
{
	while (!Toggle_GUI)
	{
		pros::delay(60);
	}
	Start_GUI();
}


void initialize() {
	
	pros::delay(300); 
	Start_UI();
	drivetrain.Initialize();
	pros::screen::touch_callback(UI_Touch, TOUCH_PRESSED);
	//pros::Task  Odem_Update(GUI);
}

/**
 * Runs while the robot is in the disabled state of Field Management System
 */
void disabled() {}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 */
void competition_initialize() {}

/**
 * Runs the user autonomous code
 */ 
void autonomous() {
 	Run_Auto();
    //Auton_13();
	  
} 

/**
 * Runs the operator control code
 * 
 */


//extern pros::Task RPM_Task;
void opcontrol() {
	FrontRoller.set_brake_mode(MOTOR_BRAKE_COAST);
	TankRoller.set_brake_mode(MOTOR_BRAKE_COAST);
	TopRoller.set_brake_mode(MOTOR_BRAKE_COAST);

	TrackerOn = false;
	drivetrain.Change_Brake_Type(Drivetrain::COAST);
	
	while (true) {
		
		drivetrain.Driver_Control();
		DriverIntakeModeControl();
		Driver_Intake();
		
		MatchLoad.Control();
		pros::delay(20);

	}
	pros::delay(20000);
}





