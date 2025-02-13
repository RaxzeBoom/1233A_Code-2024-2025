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
bool Unstuck = true;
void IntakeUnstuckTask(void* param)
{
	int counter = 0;
	while (true)
	{
		while (Unstuck)
		{
			controller.print(2,2,"%3d",Intake.get_voltage());
			
			if((Intake.get_voltage() > 4000 & Intake.get_voltage() < 8000) & Intake.get_efficiency() < 30)
			{
				if(counter >= 5)
				{
				SetIntake(-50);
				pros::delay(400);
				SetIntake(127);
				} 
				else
				{ 
				counter++;
				pros::delay(100);
				}
			}
			else
			{
				counter = 0;
			}
			pros::delay(20);
		}
		pros::delay(20);
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
	pros::Task  UST(IntakeUnstuckTask);
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
	//Auton_5();
	  
} 

/**
 * Runs the operator control code
 * 
 */


//extern pros::Task RPM_Task;
void opcontrol() {
	Unstuck = false;
	Intake.set_brake_mode(MOTOR_BRAKE_COAST);
	TrackerOn = true;
	drivetrain.Change_Brake_Type(Drivetrain::COAST);
	WallMech.set_brake_mode(MOTOR_BRAKE_BRAKE);
	while (true) {
		controller.print(2,2,"%3f",Intake.get_efficiency());
		drivetrain.Driver_Control();
		Driver_Intake();
		Driver_WallMech();
		Driver_WmPID();
		IntakeLift.Control();
		Mogo.Control();
		Doinker.Control();
		pros::delay(20);

	}
	pros::delay(20000);
}





