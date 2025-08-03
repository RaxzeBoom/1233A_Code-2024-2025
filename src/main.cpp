#include "main.h"
extern bool WallMechPid;
bool DriverintakeOn = true;
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

bool colorSortState = false;
bool colorType = false; //false = blue true = red
bool NO = true;
void colorSortTask(void* param)
{
	//Color Sort Setting
	//---------------------------------------------------------//
	const double red = 10;
	const double blue = 220;
	const double colorDiff = 10;
	const double senseDelay = 15; // in miliseconds
	const double speedChange = -45;
	const double changeDelay = 130;
	double color = 0;
	//---------------------------------------------------------//
	while (true)
	{
		while (colorSortState)
		{
			controller.clear();
			controller.print(2,2,"%3f",colorSort.get_hue());
			color = colorSort.get_hue();
			//Blue
			if(NO)
			{
			if(!colorType)
			{
				controller.print(1,2,"keep blue");
				if((red - colorDiff) < color & color < (red + colorDiff))
				{
					DriverintakeOn = false;
					SetIntake(0);
					pros::delay(senseDelay);
					SetIntake(speedChange);
					pros::delay(changeDelay);
					SetIntake(127);
					DriverintakeOn = true;
				}
			}
			//Red
			if(colorType)
			{
				controller.print(1,2,"keep red");
				if((blue - colorDiff) < color & color < (blue + colorDiff))
				{
					DriverintakeOn = false;
					SetIntake(0);
					pros::delay(senseDelay);
					SetIntake(speedChange);
					pros::delay(changeDelay);
					SetIntake(127);
					DriverintakeOn = true;
				}
			}
		}
		else{
			controller.print(1,2,"No");
		}
			
		}
		pros::delay(20);
	}
	
}
void initialize() {
	
	pros::delay(300); 
	Start_UI();
	colorSort.set_led_pwm(100);
	drivetrain.Initialize();
	WallMechRotation.reset_position();
	pros::screen::touch_callback(UI_Touch, TOUCH_PRESSED);
	//pros::Task  Odem_Update(GUI);
	pros::Task  WMPT(WallMechPidTask);
	pros::Task  UST(IntakeUnstuckTask);
	pros::Task  CSST(colorSortTask);
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
	Unstuck = false;
	Intake.set_brake_mode(MOTOR_BRAKE_COAST);
	TrackerOn = true;
	drivetrain.Change_Brake_Type(Drivetrain::COAST);
	WallMech.set_brake_mode(pros::E_MOTOR_BRAKE_COAST);
	while (true) {
		
		drivetrain.Driver_Control();
		//Driver_Intake();
		SetIntake(100);
		Driver_WallMech();
		Driver_WmPID();
		IntakeLift.Control();
		Mogo.Control();
		Doinker.Control();
		pros::delay(20);

	}
	pros::delay(20000);
}





