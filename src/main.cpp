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
void WallMechPidTask(void* param)
{
	while (true)
	{
		WallMech_PID();
	}
	
	
}
void initialize() {
	
	pros::delay(300); 
	Start_UI();
	drivetrain.Initialize();
	WallMechRotation.reset_position();
	pros::screen::touch_callback(UI_Touch, TOUCH_PRESSED);
	//pros::Task  Odem_Update(GUI);
	pros::Task  WMPT(WallMechPidTask);
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
	Intake.set_brake_mode(MOTOR_BRAKE_COAST);
	WallMech.set_brake_mode(MOTOR_BRAKE_HOLD);
	TrackerOn = true;
	drivetrain.Change_Brake_Type(Drivetrain::COAST);
	WallMech.set_brake_mode(MOTOR_BRAKE_BRAKE);
	while (true) {

		drivetrain.Driver_Control();
		Driver_Intake();
		Driver_WallMech();
		Driver_WmPID();
		Mogo.Control();
		Doinker.Control();
		pros::delay(20);

	}
}





