#include "main.h"
//Intake Config
int Driver_Intake_Speed = 127;
int Driver_TopRoller_Speed =127;
//WallMech Config
int Driver_WallMech_Speed = 127;
double DriverWallMechAngleRest = 360;
double DriverWallMechAngleLoad = 323;
double DriverWallMechAngleShoot = 200;
double DriverWallMechAngleStake = 150;
double WallMechPidVar[3] = {2,.0003,0};
