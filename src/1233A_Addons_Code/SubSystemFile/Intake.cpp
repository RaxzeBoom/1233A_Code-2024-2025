#include "main.h"
extern int DriverIntakeInSpeed[3];
extern int DriverIntakeOutSpeed[3];
extern int DriverScoreMidSpeed[3];
extern int DriverScoreHighSpeed[3];
extern int Driver_FrontRoller_Speed;
extern int Driver_HoodRoller_Speed;
extern int Driver_MiddleRoller_Speed;
extern pros::controller_digital_e_t IntakeInButton;
extern pros::controller_digital_e_t IntakeOutButton;
extern pros::controller_digital_e_t ScoreMidButton;
extern pros::controller_digital_e_t ScoreHighButton;
extern pros::controller_digital_e_t FrontRollerFwdButton;
extern pros::controller_digital_e_t FrontRollerRevButton;
extern pros::controller_digital_e_t MiddleRollerFwdButton;
extern pros::controller_digital_e_t MiddleRollerRevButton;
extern pros::controller_digital_e_t HoodRollerFwdButton;
extern pros::controller_digital_e_t HoodRollerRevButton;
extern pros::controller_digital_e_t ModeSwitchButton;
int ButtonPress[6];



void SetFrontRoller(int power)
{
    FrontRoller.move(power);
}
void StopFrontRoller()
{
    FrontRoller.brake();
}
void SetHoodRoller(int power)
{
    HoodRoller.move(power);
}
void StopHoodRoller()
{
    HoodRoller.brake();
}
void SetMiddleRoller(int power)
{
    MiddleRoller.move(power);
}
void StopMiddleRoller()
{
    MiddleRoller.brake();
}

void IntakeIn(int FrontPower, int MiddlePower, int HoodPower)
{
    SetFrontRoller(-FrontPower); 
    SetMiddleRoller(-MiddlePower); 
    SetHoodRoller(-HoodPower); 
}
void IntakeOut(int FrontPower, int MiddlePower, int HoodPower)
{
    SetFrontRoller(FrontPower); 
    SetMiddleRoller(MiddlePower); 
    SetHoodRoller(HoodPower); 
}
void ScoreMid(int FrontPower, int MiddlePower, int HoodPower)
{
    SetFrontRoller(-FrontPower); 
    SetMiddleRoller(-MiddlePower); 
    //SetHoodRoller(HoodPower); 
}
void ScoreHigh(int FrontPower, int MiddlePower, int HoodPower)
{
    SetFrontRoller(FrontPower); 
    SetMiddleRoller(MiddlePower); 
    //SetHoodRoller(-HoodPower); 
}
void StopAll()
{
    StopFrontRoller();
    StopMiddleRoller();
    StopHoodRoller();
}
bool DriverIntakeMode = false; //False = Muti Control True = Single Control
void DriverIntakeModeControl()
{
    if(controller.get_digital(ModeSwitchButton))
        {
          if(DriverIntakeMode == false) {DriverIntakeMode = true;}
          else {DriverIntakeMode = false;}
          while((controller.get_digital(ModeSwitchButton))){
             pros::delay(10);
          } 
        }
}
void Driver_Intake() {
   if(DriverIntakeMode == false)
   {
    if (controller.get_digital(IntakeInButton))
    {
        IntakeIn(DriverIntakeInSpeed[0],DriverIntakeInSpeed[1],DriverIntakeInSpeed[2]);
    }else if (controller.get_digital(IntakeOutButton))
    {
        IntakeOut(DriverIntakeOutSpeed[0],DriverIntakeOutSpeed[1],DriverIntakeOutSpeed[2]);
    }else if (controller.get_digital(ScoreMidButton))
    {
        ScoreMid(DriverScoreMidSpeed[0],DriverScoreMidSpeed[1],DriverScoreMidSpeed[2]);
    }else if (controller.get_digital(ScoreHighButton))
    {
        ScoreHigh(DriverScoreHighSpeed[0],DriverScoreHighSpeed[1],DriverScoreHighSpeed[2]);
    }else
    {
        StopAll();
    }
   }
   
   if(DriverIntakeMode == true)
   {
    if (controller.get_digital(FrontRollerFwdButton))
    {
        SetFrontRoller(Driver_FrontRoller_Speed);
        ButtonPress[0] = 1;
    }
    else {ButtonPress[0] = 0;}
    if (controller.get_digital(FrontRollerRevButton))
    {
        SetFrontRoller(-Driver_FrontRoller_Speed);
    ButtonPress[1] = 1;
    }
    else {ButtonPress[1] = 0;}
    if (controller.get_digital(MiddleRollerFwdButton))
    {
        SetMiddleRoller(Driver_MiddleRoller_Speed);
    ButtonPress[2] = 1;
    }
    else {ButtonPress[2] = 0;}
    if (controller.get_digital(MiddleRollerRevButton))
    {
        SetMiddleRoller(-Driver_MiddleRoller_Speed);
    ButtonPress[3] = 1;
    }
    else {ButtonPress[3] = 0;}
    if (controller.get_digital(HoodRollerFwdButton))
    {
        SetHoodRoller(Driver_HoodRoller_Speed);
    ButtonPress[4] = 1;
    }
    else {ButtonPress[4] = 0;}
    if (controller.get_digital(HoodRollerRevButton))
    {
        SetHoodRoller(-Driver_HoodRoller_Speed);
    ButtonPress[5] = 1;
    }
    else {ButtonPress[5] = 0;}
    if(std::find(std::begin(ButtonPress),std::end(ButtonPress),1) == std::end(ButtonPress))
    {
        StopAll();
    }
    }
}