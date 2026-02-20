#include "main.h"
extern bool WallMechPid;
bool TrackerOn = true;
extern bool Toggle_GUI;
bool Unstuck = false;
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
void ChassisControl(void* param)
{
	while(true)
	{
		Odom.Update();
		pros::delay(20);
	}
}
void IntakeUnstuck(void* param)
{
	while (true)
	{
		while(Unstuck)
		{
			Intake.Unstuck(0,-40,400,{0},{-127});
			pros::delay(50);
		}
		pros::delay(50);
	}
	
}

void initialize() {
	
	
	pros::delay(200); 
	drivetrain.Initialize();
	Start_UI();
	pros::screen::touch_callback(UI_Touch, TOUCH_PRESSED);
	pros::Task Upstuck(IntakeUnstuck);
	//pros::Task  GUITASK(GUI);
	//pros::Task ChassisMovement(ChassisControl);
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
	//Auton_2();
 	Run_Auto();
 
} 

/**
 * Runs the operator control code
 * 
 */


//extern pros::Task RPM_Task;
void opcontrol() {
	TopRoller.set_brake_mode(MOTOR_BRAKE_COAST);
	BottomRoller.set_brake_mode(MOTOR_BRAKE_COAST);
	Unstuck = false;
	//TrackerOn = false;
	drivetrain.Change_Brake_Type(Drivetrain::COAST);
	
	while (true) {
		drivetrain.Driver_Control();
		Intake.MainControl();
		MatchLoad.Control();
		Descore.Control();
		MiddleBlock.Control_Hold();
		pros::delay(20);

	}
	pros::delay(20000);
}





