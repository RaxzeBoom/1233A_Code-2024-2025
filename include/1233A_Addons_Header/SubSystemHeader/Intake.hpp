#include "main.h"
void SetFrontRoller(int power);
void StopFrontRoller();
void SetTopRoller(int power);
void StopTopRoller();
void SetTankRoller(int power);
void StopTankRoller();

void IntakeIn(int FrontPower, int TankPower, int TopPower);
void IntakeOut(int FrontPower, int TankPower, int TopPower);
void Scoremid(int FrontPower, int TankPower, int TopPower);
void ScoreHigh(int FrontPower, int TankPower, int TopPower);
void StopAll();
void DriverIntakeModeControl();
void Driver_Intake();