#include "main.h"
//Intake Config
int Driver_Intake_Speed = 127;

//WallMech Config
int Driver_WallMech_Speed = 127;
double DriverWallMechAngle = 330;
double DriverWallMechAngleEnd = 200;
double WallMechPidVar[3] = {1.3,.0003,0};
