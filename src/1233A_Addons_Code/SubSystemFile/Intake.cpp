#include "main.h"
extern int DriverIntakeInSpeed[3];
extern int DriverIntakeOutSpeed[3];
extern int DriverScoremidSpeed[3];
extern int DriverScoreHighSpeed[3];
extern int Driver_FrontRoller_Speed;
extern int Driver_TopRoller_Speed;
extern int Driver_TankRoller_Speed;
extern pros::controller_digital_e_t IntakeInButton;
extern pros::controller_digital_e_t IntakeOutButton;
extern pros::controller_digital_e_t ScoremidButton;
extern pros::controller_digital_e_t ScoreHighButton;
extern pros::controller_digital_e_t FrontRollerFwdButton;
extern pros::controller_digital_e_t FrontRollerRevButton;
extern pros::controller_digital_e_t TankRollerFwdButton;
extern pros::controller_digital_e_t TankRollerRevButton;
extern pros::controller_digital_e_t TopRollerFwdButton;
extern pros::controller_digital_e_t TopRollerRevButton;
extern pros::controller_digital_e_t ModeSwitchButton;




void SetFrontRoller(int power)
{
    FrontRoller.move(power);
}
void StopFrontRoller()
{
    FrontRoller.brake();
}
void SetTopRoller(int power)
{
    TopRoller.move(power);
}
void StopTopRoller()
{
    TopRoller.brake();
}
void SetTankRoller(int power)
{
    TankRoller.move(power);
}
void StopTankRoller()
{
    TankRoller.brake();
}

void IntakeIn(int FrontPower, int TankPower, int TopPower)
{
    SetFrontRoller(FrontPower); //Neg
    SetTankRoller(-TankPower); //Neg
    //SetTopRoller(TopPower); //Pos
}
void IntakeOut(int FrontPower, int TankPower, int TopPower)
{
    SetFrontRoller(-FrontPower); //Pos
    SetTankRoller(TankPower); //Pos
    //SetTopRoller(TopPower); //Pos
}
void Scoremid(int FrontPower, int TankPower, int TopPower)
{
    SetFrontRoller(-FrontPower); //Neg
    SetTankRoller(TankPower); //Pos
    SetTopRoller(TopPower); //Pos
}
void ScoreHigh(int FrontPower, int TankPower, int TopPower)
{
    SetFrontRoller(-FrontPower); //Neg
    SetTankRoller(TankPower); //Pos
    SetTopRoller(-TopPower); //Neg
}
void StopAll()
{
    StopFrontRoller();
    StopTankRoller();
    StopTopRoller();
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
    }else if (controller.get_digital(ScoremidButton))
    {
        Scoremid(DriverScoremidSpeed[0],DriverScoremidSpeed[1],DriverScoremidSpeed[2]);
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
    }else if (controller.get_digital(FrontRollerRevButton))
    {
        SetFrontRoller(-Driver_FrontRoller_Speed);
    }else if (controller.get_digital(TankRollerFwdButton))
    {
        SetTankRoller(Driver_TankRoller_Speed);
    }else if (controller.get_digital(TankRollerRevButton))
    {
        SetTankRoller(-Driver_TankRoller_Speed);
    }else if (controller.get_digital(TopRollerFwdButton))
    {
        SetTopRoller(Driver_TopRoller_Speed);
    }else if (controller.get_digital(TopRollerRevButton))
    {
        SetTopRoller(-Driver_TopRoller_Speed);
    }else
    {
        StopAll();
    }
        
   }
}