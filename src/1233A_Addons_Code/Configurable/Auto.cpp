#include "main.h"
#include "1233A_Addons_Header/SubSystemHeader/WallMech.hpp"
extern double WallMech_Target;
#include <string.h>
Drivetrain::Straight_PID_Var Alfa_Straight(
    /*kP*/
    .070,
    /*kI*/
    0.005,
    /*kD*/
    0.0,
    /*kA*/
    3.5,
    /*kAI*/
    0
    );
Drivetrain::Straight_PID_Var Beta_Straight(
    /*kP*/
    .9,
    /*kI*/
    0.005,
    /*kD*/
    0.0,
    /*kA*/
    4,
    /*kAI*/
    0
    );
Drivetrain::Turn_PID_Var Alfa_Turn(
    /*kP*/
    .9,
    /*kI*/
    0.016,
    /*kD*/
    0,
    /*Passive Power*/
    true
    );
Drivetrain::Turn_PID_Var Beta_Turn(
    /*kP*/
    .4,
    /*kI*/
    0.015,
    /*kD*/
    0.06,
    /*Passive Power*/
    false
    );
Drivetrain::Swing_PID_Var Alfa_Swing(
    /*kP*/
    1.3,
    /*kI*/
    0.016,
    /*kD*/
    0.0
    );
extern int Auto_Num;
extern int Change;
extern bool TrackerOn;
extern bool Unstuck;

Auto_Info Auto_Programs[] = {
    //  Name  ,   Display Name  ,  Description  ,  Auto that should be ran
    {"B-POS-Ring  ","B-POS-Ring  ",
    {"Goal Rush where we get 3 rings between 2 goals"},
    Auton_1},
    //-------------------------------------------------
    {"B-POS-Bar   ","B-POS-Bar    ",
    {"Goal Rush where we get 2 rings and touch bar"},
    Auton_2},
    //-------------------------------------------------
    {"B-POS-Corner","B-POS-Corner",
    {"Goal Rush where we get 2 rings and go to corner"},
    Auton_3},
    //-------------------------------------------------
    {"B-NEG       ","B-NEG       ",
    {"DEFULT"},
    Auton_4},
    //-------------------------------------------------
    {"DEFULT 5","Auto 5",
    {"DEFULT"},
    Auton_5},
    //-------------------------------------------------
    {"DEFULT 6","Auto 6",
    {"DEFULT"},
    Auton_6},
    //-------------------------------------------------
    {"R-POS-Ring  ","R-POS-Ring  ",
    {"Goal Rush where we get 3 rings between 2 goals"},
    Auton_7},
    //-------------------------------------------------
    {"R-POS-Bar   ","R-POS-Bar    ",
    {"Goal Rush where we get 2 rings and touch bar"},
    Auton_8},
    //-------------------------------------------------
    {"R-POS-Corner","R-POS-Corner",
    {"Goal Rush where we get 2 rings and go to corner"},
    Auton_9},
    //-------------------------------------------------
    {"R-NEG       ","R-NEG       ",
    {"DEFULT"},
    Auton_10},
    //-------------------------------------------------
    {"DEFULT 11","Auto 11",
    {"DEFULT"},
    Auton_11},
    //-------------------------------------------------
    {"DEFULT 12","Auto 12",
    {"DEFULT"},
    Auton_12},
    //-------------------------------------------------
    {"Skills      ","Skills      ",
    {"DEFULT"},
    Auton_13},
    //-------------------------------------------------
    {"DEFULT 15","Auto 15",
    {"DEFULT"},
    Auton_14},
    //-------------------------------------------------
    {"DEFULT 15","Auto 15",
    {"DEFULT"},
    Auton_15},
    //-------------------------------------------------
    {"DEFULT 16","Auto 16",
    {"DEFULT"},
    Auton_16},
    //-------------------------------------------------
    {"Forward","Forward",
    {"DEFULT"},
    Auton_17},
    //-------------------------------------------------
    {"Nothing","Nothing",
    {"Does Nothing"},
    Auton_18}
};
extern bool TrackerOn;

void Run_Auto()
{
    Auto_Programs[Auto_Num-1].Current_Auto();
}

void Marco_Skills()
{
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
    {

    }
}
/*
double Path_[1000][7];
double Kp = 1;
double Kd = 1;
void Updater()
{
    
    while(TrackerOn)
    {
        Odom.Update();
        RamseteController.Reader(Path_);
        RamseteController.Controller(Kd,Kp);
        pros::delay(10);
    }
}
#include <string>
//Start of close side autos
void Auton_1()
{
double Path[][7] =
{ {10,20,90,100,0.03,0.04,0},{12,20,90,100,0.28,0.08,1},{14,20,89.99,100,2.04,0.12,2},
{16,20,89.9,100,11.2,0.16,3},{18,20,89.4,29.43,30,0.23,4},{19.98,20.02,87.38,9.26,30,0.44,5},
{21.91,20.11,81.12,3.79,30,0.92,6},{23.69,20.39,66.86,2.44,30,1.59,7},{25.18,21.03,46.9,3.27,30,2.07,8},
{26.32,22.1,32.53,7.27,30,2.3,9},{27.21,23.49,25.72,19.68,30,2.39,10},{27.96,25.05,23.08,100,22.9,2.43,11},
{28.66,26.68,22.18,2.42,30,3.17,12},{29.33,28.34,0,0,-30,4.29,13},{29.33,28.34,33.58,1.73,-30,4.76,14},
{29.78,29.02,47.78,1.18,-30,5.42,15},{30.36,29.54,67.54,2.39,-30,5.76,16},{31.1,29.85,77.67,2.28,-30,6.14,17},
{31.95,30.03,89,100,0.83,6.18,18},{33.89,30.07,88.96,100,1.86,6.22,19},{35.83,30.1,88.88,100,3.83,6.26,20},
{37.77,30.14,88.72,100,7.34,6.3,21},{39.7,30.18,88.41,100,13.27,6.34,22},{41.6,30.24,87.85,100,22.92,6.38,23},
{43.47,30.31,86.91,35.39,30,6.43,24},{45.28,30.4,85.37,21.33,30,6.51,25},{47,30.54,82.94,12.77,30,6.64,26},
{48.6,30.74,79.17,7.47,30,6.84,27},{50.03,31.01,73.31,4.26,30,7.14,28},{51.26,31.38,64.27,2.44,30,7.59,29},
{52.25,31.86,50.7,1.55,30,8.2,30},{52.99,32.46,32.38,1.31,30,8.86,31},{53.45,33.19,12.58,3.03,30,9.15,32},
{53.64,34.05,-3.91,2.54,-30,9.54,33},{53.57,35.03,-15.48,4.42,-30,9.8,34},{53.27,36.11,-23.14,7.65,-30,9.97,35},
{52.77,37.29,-28.18,12.79,-30,10.08,36},{52.09,38.56,-31.54,20.65,-30,10.16,37},{51.28,39.88,-33.8,32.49,-30,10.21,38},
{50.36,41.26,-35.33,100,-27.05,10.25,39},{49.35,42.68,-36.37,100,-17.59,10.29,40},{48.29,44.12,-37.07,100,-11.44,10.33,41},
{47.18,45.58,-37.53,100,-7.38,10.37,42},{46.05,47.06,-37.83,100,-4.72,10.41,43},{44.89,48.55,-38.03,100,-2.97,10.45,44},
{43.73,50.04,-38.15,100,-1.84,10.49,45},{42.55,51.53,-38.23,100,-1.13,10.53,46},{41.37,53.03,-38.28,100,-0.68,10.57,47},
{40.19,54.53,-38.3,100,-0.4,10.61,48},{39,56.03,-38.32,100,-0.23,10.65,49},{37.82,57.53,-38.33,100,-0.13,10.69,50},
{36.63,59.04,-38.34,100,-0.07,10.73,51},{35.44,60.54,-38.34,100,-0.02,10.77,52},{34.25,62.04,-38.34,100,7.09,10.79,53},
{33.66,62.79,-38.19,3.99,30,11.03,54},{33.07,63.54,-31,100,6.77,11.05,55},{32.57,64.37,-30.86,100,0.14,11.07,56},
{32.08,65.19,-30.85,100,-0,11.11,57},{31.1,66.84,-30.85,100,0,11.15,58},{30.12,68.48,-30.85,100,0,11.19,59},
{29.13,70.13,-30.85,100,0,11.23,60},{28.15,71.78,-30.85,100,0,11.27,61},{27.16,73.42,-30.85,100,0,11.31,62},
{26.18,75.07,-30.85,100,0,11.35,63},{25.2,76.72,-30.85,100,0,11.39,64},{24.21,78.36,-30.85,100,0.01,11.43,65},
{23.23,80.01,-30.85,100,0.09,11.47,66},{22.24,81.66,-30.85,100,0.59,11.51,67},{21.26,83.3,-30.82,100,3,11.55,68},
{20.28,84.95,-30.7,100,12.21,11.59,69},{19.3,86.6,-30.18,33.94,30,11.65,70},{18.35,88.24,-28.5,12.43,30,11.8,71},
{17.46,89.87,-24.03,5.32,30,12.13,72},{16.75,91.47,-14.16,4.25,30,12.5,73},{16.36,93.01,2.91,2.22,-30,13.16,74},
{16.43,94.48,22.75,3.06,-30,13.65,75},{17.01,95.85,37.4,6.08,-30,13.92,76},{18.01,97.16,45.52,13.65,-30,14.05,77},
{19.29,98.42,49.46,32.14,-30,14.11,78},{20.73,99.65,51.22,100,-17.14,14.15,79},{22.24,100.86,51.96,100,-6.54,14.19,80},
{23.79,102.07,52.24,100,-2.34,14.23,81},{25.35,103.28,52.34,100,-0.79,14.27,82},{26.91,104.49,52.37,100,-0.25,14.31,83},
{28.48,105.7,52.39,100,-0.08,14.35,84},{30.05,106.9,52.39,100,-0.02,14.39,85},{31.61,108.11,52.39,100,-0.01,14.43,86},
{33.18,109.32,52.39,100,-0,14.47,87},{34.75,110.53,52.39,100,-0,14.51,88},{36.31,111.73,52.39,100,-0,14.55,89}
};

memcpy(Path_,Path,sizeof(Path));
Kp = 1;
Kd = 1;
Odom.position.x = Path[0][0];
Odom.position.y = Path[0][1];
RamseteController.Start();
pros::Task  RamseteUpdate(Updater);

switch (RamseteController.index)
{
case 0:
    break;

default:
    break;
}
}
*/

//Start of blue side autos
extern double DriverWallMechAngleRest;
extern double DriverWallMechAngleLoad;
extern double DriverWallMechAngleShoot;
//Positive Side
void Auton_1()
{
   WallMech_Target = DriverWallMechAngleShoot;
    drivetrain.driveDistance(-15.4, 100, Alfa_Straight);
    IntakeLift.Toggle();
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(300);
    Mogo.Toggle();
    pros::delay(100);  
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(48, 100, Alfa_Turn,4,5);
    SetIntake(100);
    drivetrain.driveDistance(24, 100, Alfa_Straight);
    IntakeLift.Toggle();
    drivetrain.driveDistance(-24, 100, Alfa_Straight);
    drivetrain.Turn(135, 40, Alfa_Turn,20,200);
    Mogo.Toggle();
    drivetrain.Turn(-92.5, 70, Alfa_Turn,4,5);
    Unstuck = false;
    SetIntake(80);
    drivetrain.driveDistance(27, 100, Alfa_Straight);
    pros::delay(55);
    StopIntake();
    drivetrain.Turn(0, 100, Alfa_Turn,4,9);
    drivetrain.driveDistance(-6, 100, Alfa_Straight);
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(200);
    Mogo.Toggle();
    pros::delay(100);  
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.driveDistance(18, 100, Alfa_Straight);
    drivetrain.Turn(120, 120, Alfa_Turn, 10, 100);
    drivetrain.driveDistance(30,127,Alfa_Straight);
   
}

void Auton_2()
{
    // RED 
    drivetrain.driveDistance(-28,90,Alfa_Straight);
    drivetrain.Turn(30,90,Alfa_Turn);  
    drivetrain.driveDistance(-7.5,90,Alfa_Straight);
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(200);
    Mogo.Toggle();
    pros::delay(100);
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(0,110,Alfa_Turn); 
    drivetrain.driveDistance(21,80 ,Beta_Straight);
    pros::delay(200);
    StopIntake();
    drivetrain.Turn(-135,65,Alfa_Turn); 
    Mogo.Toggle();
    drivetrain.Turn(90,65,Alfa_Turn); 
    drivetrain.driveDistance(-19,80,Alfa_Straight);
    drivetrain.Set_Drivetrain(-40,-40);
    pros::delay(300);
    Mogo.Toggle();
    pros::delay(100);
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(-35,110,Alfa_Turn); 
    IntakeLift.Toggle();
    drivetrain.driveDistance(34,80,Beta_Straight);
    WallMech_Target = DriverWallMechAngleShoot;
    drivetrain.Turn(135,110,Alfa_Turn);
    drivetrain.driveDistance(34,80,Beta_Straight); 
}
void Auton_3()
{
    drivetrain.driveDistance(-28,90,Alfa_Straight);
    drivetrain.Turn(30,90,Alfa_Turn);  
    drivetrain.driveDistance(-7.5,90,Alfa_Straight);
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(200);
    Mogo.Toggle();
    pros::delay(100);
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(0,110,Alfa_Turn); 
    drivetrain.driveDistance(21,80 ,Beta_Straight);
    pros::delay(200);
    StopIntake();
    drivetrain.Turn(-135,65,Alfa_Turn); 
    Mogo.Toggle();
    drivetrain.Turn(90,65,Alfa_Turn); 
    drivetrain.driveDistance(-19,80,Alfa_Straight);
    drivetrain.Set_Drivetrain(-40,-40);
    pros::delay(300);
    Mogo.Toggle();
    pros::delay(100);
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(-35,110,Alfa_Turn); 
    IntakeLift.Toggle();
    drivetrain.driveDistance(34,80,Beta_Straight);
    WallMech_Target = DriverWallMechAngleShoot;
    drivetrain.Turn(135,110,Alfa_Turn);
    drivetrain.driveDistance(34,80,Beta_Straight); 
}
//Negitive Side
void Auton_4()
{
    WallMech_Target = DriverWallMechAngleShoot;
    drivetrain.driveDistance(-15.4, 100, Alfa_Straight);
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(300);
    Mogo.Toggle();
    pros::delay(100);  
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(-92, 100, Alfa_Turn);
    drivetrain.driveDistance(14, 80, Alfa_Straight);
    drivetrain.driveDistance(-2,100, Alfa_Straight);
    drivetrain.Turn(-162, 100, Alfa_Turn);//166
    drivetrain.driveDistance(14, 100, Alfa_Straight);
    drivetrain.driveDistance(-4, 100, Alfa_Straight);
    drivetrain.Turn(-146, 100, Alfa_Turn);//128
    drivetrain.driveDistance(8, 100, Alfa_Straight);
    drivetrain.driveDistance(-5, 100, Alfa_Straight);
    drivetrain.Turn(-270,60, Alfa_Turn);
    drivetrain.driveDistance(20,127,Alfa_Straight);
}
void Auton_5()
{
    // 2 GOAL RED 
    WallMech_Target = DriverWallMechAngleShoot;
    drivetrain.driveDistance(-15.4, 100, Alfa_Straight);
    IntakeLift.Toggle();
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(300);
    Mogo.Toggle();
    pros::delay(100);  
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(-48, 100, Alfa_Turn,4,5);
    SetIntake(100);
    drivetrain.driveDistance(24, 100, Alfa_Straight);
    IntakeLift.Toggle();
    drivetrain.driveDistance(-24, 100, Alfa_Straight);
    drivetrain.Turn(-135, 40, Alfa_Turn,20,200);
    Mogo.Toggle();
    drivetrain.Turn(92.5, 70, Alfa_Turn,4,5);
    Unstuck = false;
    SetIntake(80);
    drivetrain.driveDistance(27, 100, Alfa_Straight);
    pros::delay(55);
    StopIntake();
    drivetrain.Turn(0, 100, Alfa_Turn,4,9);
    drivetrain.driveDistance(-6, 100, Alfa_Straight);
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(200);
    Mogo.Toggle();
    pros::delay(100);  
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.driveDistance(18, 100, Alfa_Straight);
    drivetrain.Turn(-120, 120, Alfa_Turn, 10, 100);
    drivetrain.driveDistance(30,127,Alfa_Straight);
}
void Auton_6()
{

}
//Start of red side autos

//Start of postive sides
void Auton_7()
{
    //USE USE USE USE USE USE USE
    WallMech_Target = DriverWallMechAngleShoot;
    drivetrain.driveDistance(-15.4, 100, Alfa_Straight);
    IntakeLift.Toggle();
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(300);
    Mogo.Toggle();
    pros::delay(100);  
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(48, 100, Alfa_Turn,4,5);
    SetIntake(100);
    drivetrain.driveDistance(24, 100, Alfa_Straight);
    IntakeLift.Toggle();
    drivetrain.driveDistance(-24, 100, Alfa_Straight);
    drivetrain.Turn(135, 40, Alfa_Turn,20,200);
    Mogo.Toggle();
    drivetrain.Turn(-92.5, 70, Alfa_Turn,4,5);
    Unstuck = false;
    SetIntake(80);
    drivetrain.driveDistance(27, 100, Alfa_Straight);
    pros::delay(55);
    StopIntake();
    drivetrain.Turn(0, 100, Alfa_Turn,4,9);
    drivetrain.driveDistance(-6, 100, Alfa_Straight);
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(200);
    Mogo.Toggle();
    pros::delay(100);  
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.driveDistance(18, 100, Alfa_Straight);
    drivetrain.Turn(120, 120, Alfa_Turn, 10, 100);
    drivetrain.driveDistance(30,127,Alfa_Straight);
}
void Auton_8()
{
    
}
void Auton_9()
{
    
}
//Start of negitive sides
void Auton_10()
{
    // 4 ring red side
    WallMech_Target = DriverWallMechAngleShoot;
    drivetrain.driveDistance(-15.4, 100, Alfa_Straight);
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(300);
    Mogo.Toggle();
    pros::delay(100);  
    drivetrain.Set_Drivetrain(0,0);
    SetIntake(127);
    drivetrain.Turn(92, 100, Alfa_Turn);
    drivetrain.driveDistance(14, 80, Alfa_Straight);
    drivetrain.driveDistance(-2,100, Alfa_Straight);
    drivetrain.Turn(162, 100, Alfa_Turn);//166
    drivetrain.driveDistance(14, 100, Alfa_Straight);
    drivetrain.driveDistance(-4, 100, Alfa_Straight);
    drivetrain.Turn(146, 100, Alfa_Turn);//128
    drivetrain.driveDistance(8, 100, Alfa_Straight);
    drivetrain.driveDistance(-5, 100, Alfa_Straight);
    drivetrain.Turn(270,60, Alfa_Turn);
    drivetrain.driveDistance(20,127,Alfa_Straight);

}
void Auton_11()
{

}
void Auton_12()
{

}
//Start of Other programs
void Auton_13()
{
    SetIntake(127);
    pros::delay(650);
    StopIntake();
    drivetrain.driveDistance(11, 100, Alfa_Straight);
    drivetrain.Turn(-90, 100, Alfa_Turn);
    drivetrain.driveDistance(-12, 100, Alfa_Straight);
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(200);
    Mogo.Toggle();
    pros::delay(100);  
    SetIntake(127);
    drivetrain.Turn(-8, 100, Alfa_Turn);
    drivetrain.driveDistance(15, 100, Alfa_Straight);
    drivetrain.Turn(50, 100, Alfa_Turn);
    drivetrain.driveDistance(43, 110, Alfa_Straight);
    drivetrain.driveDistance(-13, 100, Alfa_Straight);
    drivetrain.Turn(175, 100, Alfa_Turn);
    drivetrain.driveDistance(14, 100, Alfa_Straight);
    drivetrain.driveDistance(14, 100, Alfa_Straight);
    pros::delay(300);
    drivetrain.driveDistance(16, 100, Alfa_Straight);
    drivetrain.driveDistance(-8, 100, Alfa_Straight);
    drivetrain.Turn(90, 100, Alfa_Turn);
    drivetrain.driveDistance(8, 100, Alfa_Straight);
    drivetrain.Turn(-30, 100, Alfa_Turn);
    drivetrain.driveDistance(-10, 100, Alfa_Straight);
    SetIntake(-127);
    pros::delay(100);
    Mogo.Toggle();
    drivetrain.driveDistance(14, 100, Alfa_Straight);
    StopIntake();
    drivetrain.Turn(90, 100, Alfa_Turn);
    drivetrain.driveDistance(40, 500);
    drivetrain.Set_Heading(90);
    drivetrain.driveDistance(-35, 75, Alfa_Straight);
    pros::delay(100);
    drivetrain.driveDistance(-30, 75, Alfa_Straight);
    pros::delay(100);
    drivetrain.driveDistance(-10, 45, Alfa_Straight);
    Mogo.Toggle();
    SetIntake(127);
    drivetrain.Set_Heading(180);
    pros::delay(100);
    drivetrain.driveDistance(17,50,Alfa_Straight);
    drivetrain.Turn(-90,50,Alfa_Turn);
    drivetrain.driveDistance(24,50,Alfa_Straight);
    drivetrain.Set_Heading(180);
    drivetrain.driveDistance(50,70,Alfa_Straight);


    
}
//Backup
void Auton_14()
{
    
}
void Auton_15()
{

}
void Auton_16()
{
    pros::delay(2000);
    drivetrain.Turn(90,110,Alfa_Turn);
    pros::delay(200);
    drivetrain.Turn(180,110,Alfa_Turn);
    pros::delay(200);
    drivetrain.Turn(270,110,Alfa_Turn);
    pros::delay(200);
    drivetrain.Turn(0,110,Alfa_Turn);
}
void Auton_17()
{
    drivetrain.Set_Drivetrain(50,50);
    pros::delay(400);
    drivetrain.Set_Drivetrain(0,0);
}
void Auton_18()
{
    //Do nothing
    drivetrain.Turn(-45,90,Alfa_Turn);  
    drivetrain.driveDistance(-19,50,Alfa_Straight);
    drivetrain.Turn(40,90,Alfa_Turn);
    drivetrain.driveDistance(-12,50,Alfa_Straight);
    drivetrain.Set_Drivetrain(-40,-40);
    pros::delay(500);
    Mogo.Toggle();
    pros::delay(100);
    drivetrain.Set_Drivetrain(0,0);
    drivetrain.Turn(80,90,Alfa_Turn);  
    SetIntake(127);
    drivetrain.driveDistance(24,70,Beta_Straight);
    drivetrain.Turn(-170,90,Alfa_Turn); 
    drivetrain.driveDistance(-36,90,Alfa_Straight);
}
