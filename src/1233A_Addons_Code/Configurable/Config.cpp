#include "main.h"
//Intake Config
int Driver_Intake_Speed = 127;

//WallMech Config
int Driver_WallMech_Speed = 127;
double DriverWallMechAngleRest = 355;
double DriverWallMechAngleLoad = 340;
double DriverWallMechAngleShoot = 240;
double WallMechPidVar[3] = {2,.0003,0};
