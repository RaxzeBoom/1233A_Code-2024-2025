#include "main.h"
extern double WallMech_Target;
#include <string.h>
DrivePID::PIDVars Alfa_Turn(
    /*kP*/
    .58,
    /*kI*/
    0.015,
    /*kD*/
    0
    );
DrivePID::PIDVars Beta_Turn(
    /*kP*/
    .4,
    /*kI*/
    0.010,
    /*kD*/
    0
    );
DrivePID::PIDVars Alfa_Swing(
    /*kP*/
    .76,
    /*kI*/
    0.015,
    /*kD*/
    0
    );
DrivePID::PIDVars Alfa_Straight(
    /*kP*/
    .0018,
    /*kI*/
    0,
    /*kD*/
    0
    );
DrivePID::PIDVars Beta_Straight(
    /*kP*/
    .004,
    /*kI*/
    0,
    /*kD*/
    0
    );
extern int Auto_Num;
extern int Change;
extern bool TrackerOn;
extern bool Unstuck;
Auto_Info Auto_Programs[] = {
    //  Name  ,   Display Name  ,  Description  ,  Auto that should be ran
    {"7BlockLeft  ","7BlockLeft  ",
    {"One High Middle 2 Long Goal"},
    Auton_1},
    //-------------------------------------------------
    {"7BlockRight ","7BlockRight ",
    {"One Low Middle 2 Long Goal"},
    Auton_2},
    //-------------------------------------------------
    {"4BlockPLeft ","4BlockPLeft ",
    {"DEFULT"},
    Auton_3},
    //-------------------------------------------------
    {"4BlockPRight","4BlockPRight",
    {"DEFULT"},
    Auton_4},
    //-------------------------------------------------
    {"SoloAWP     ","SoloAWP     ",
    {"DEFULT"},
    Auton_5},
    //-------------------------------------------------
    {"DEFULT 6","Auto 6",
    {"DEFULT"},
    Auton_6},
    //-------------------------------------------------
    {"LeftSideR   ","LeftSideR   ",
    {"One High Middle 2 Long Goal"},
    Auton_7},
    //-------------------------------------------------
    {"RightSideR  ","RightSideR  ",
    {"One Low Middle 2 Long Goal"},
    Auton_8},
    //-------------------------------------------------
    {"DEFULT 9","Auto 9",
    {"DEFULT"},
    Auton_9},
    //-------------------------------------------------
    {"DEFULT 10","Auto 10",
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
    {"DEFULT 13","Auto 13",
    {"DEFULT"},
    Auton_13},
    //-------------------------------------------------
    {"skills2","skills2",
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
    {"Backwards   ","Backwards   ",
    {"DEFULT"},
    Auton_17},
    //-------------------------------------------------
    {"Nothing     ","Nothing     ",
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

//Start of blue side autos
extern double DriverWallMechAngleRest;
extern double DriverWallMechAngleLoad;
extern double DriverWallMechAngleShoot;
extern double DriverWallMechAngleStake;
extern bool colorType;
extern bool WallMechPid;
//Positive Side
void Auton_1()
{
    PIDController.timeOutLenght = 1000;
    Unstuck = true;
    PIDController.driveDistance(34,100,Alfa_Straight,5);
    MatchLoad.Toggle();
    PIDController.Turn(-90,50,Alfa_Turn,3,100);
    Intake.SpinMotor(0,127);
    PIDController.driveDistance(12,100,Alfa_Straight,5);
    pros::delay(50);
    PIDController.driveDistance(-24,100,Alfa_Straight,5);
    MatchLoad.Toggle();
    drivetrain.Set_Drivetrain(-80,-80);
    Intake.SpinMotor({0,1},{127,127});
    pros::delay(1200);
    drivetrain.Set_Drivetrain(0,0);
    drivetrain.Set_Drivetrain(40,40);
    pros::delay(50);
    drivetrain.Set_Drivetrain(-10,90);
    pros::delay(700);
    drivetrain.Set_Drivetrain(0,0);
    PIDController.Target_Heading = 140;
    PIDController.Turn(140,12,Beta_Turn,5,100);
    Intake.StopMotor(1);
    PIDController.driveDistance(24,40,Alfa_Straight,5);
    MatchLoad.Toggle();
    pros::delay(250);
    PIDController.Turn(-45,30,Alfa_Turn,5,100);
    PIDController.driveDistance(-12.5,100,Alfa_Straight,5);
    drivetrain.Set_Drivetrain(-10,-10);
    MiddleBlock.Toggle();
    Intake.SpinMotor({0,1},{127,-127});
    pros::delay(2000);
    MiddleBlock.Toggle();
    Intake.StopAllMotors();
    PIDController.driveDistance(4,100,Alfa_Straight,5);
}

void Auton_2()
{
    
    PIDController.timeOutLenght = 1000;
    Unstuck = true;
    PIDController.driveDistance(34,100,Alfa_Straight,5);
    MatchLoad.Toggle();
    PIDController.Turn(90,50,Alfa_Turn,3,100);
    Intake.SpinMotor(0,127);
    PIDController.driveDistance(12,100,Alfa_Straight,5);
    pros::delay(0);
    PIDController.driveDistance(-24,100,Alfa_Straight,5);
    MatchLoad.Toggle();
    drivetrain.Set_Drivetrain(-80,-80);
    Intake.SpinMotor({0,1},{127,127});
    pros::delay(1400);
    drivetrain.Set_Drivetrain(0,0);
    drivetrain.Set_Drivetrain(40,40);
    pros::delay(50);
    drivetrain.Set_Drivetrain(90,-10);
    pros::delay(700);
    drivetrain.Set_Drivetrain(0,0);
    PIDController.Target_Heading = 220;
    PIDController.Turn(220,12,Beta_Turn,5,100);
    Intake.StopMotor(1);
    PIDController.driveDistance(24,40,Alfa_Straight,5);
    MatchLoad.Toggle();
    pros::delay(250);
    PIDController.driveDistance(-12,80,Alfa_Straight,5);
    drivetrain.Set_Drivetrain(-90,10);
    pros::delay(700);
    drivetrain.Set_Drivetrain(-80,-80);
    Intake.SpinMotor({0,1},{127,127});
    pros::delay(2000);
    drivetrain.Set_Drivetrain(100,100);
    pros::delay(200);
    drivetrain.Set_Drivetrain(-80,-80);
    
}
void Auton_3()
{
    PIDController.timeOutLenght = 1000;
    Intake.SpinMotor(0,127);
    PIDController.Turn(-12,6,Beta_Turn,2,4);
    PIDController.timeOutLenght = 1250;
    PIDController.driveDistance(16,80,Alfa_Straight,2);
    MatchLoad.Toggle();
    PIDController.driveDistance(10,30,Alfa_Straight,2);
    Intake.SpinMotor(0,127);
    pros::delay(250);
    PIDController.Turn(-115,100,Alfa_Turn);
    PIDController.driveDistance(29,115,Alfa_Straight,1.5);
    PIDController.Turn(180,90,Alfa_Turn);
    PIDController.timeOutLenght = 250;
    PIDController.driveDistance(-8,115,Alfa_Straight,1.5);
    PIDController.timeOutLenght = 1250;
    drivetrain.Set_Drivetrain(-80,-80);
    pros::delay(500);
    Descore.Toggle();
    Intake.SpinMotor({0,1},{127,127});
    pros::delay(1750);
    Descore.Toggle();
    Intake.StopAllMotors();
    PIDController.driveDistance(14,90,Alfa_Straight,1.5);
    PIDController.Turn(235,100,Alfa_Turn);
    PIDController.driveDistance(-13,90,Alfa_Straight,1.5);
    PIDController.Turn(180,100,Alfa_Turn);
    PIDController.driveDistance(-16,100,Alfa_Straight,1.5);
}
//Negitive Side
void Auton_4()
{
    PIDController.timeOutLenght = 1000;
    Intake.SpinMotor(0,127);
    PIDController.Turn(12,6,Beta_Turn,2,4);
    PIDController.timeOutLenght = 1250;
    PIDController.driveDistance(16,80,Alfa_Straight,2);
    MatchLoad.Toggle();
    PIDController.driveDistance(10,30,Alfa_Straight,2);
    Intake.SpinMotor(0,127);
    pros::delay(250);
    PIDController.Turn(115,100,Alfa_Turn);
    PIDController.driveDistance(30,115,Alfa_Straight,1.5);
    PIDController.Turn(180,90,Alfa_Turn);
    PIDController.timeOutLenght = 250;
    PIDController.driveDistance(-8,115,Alfa_Straight,1.5);
    PIDController.timeOutLenght = 1250;
    drivetrain.Set_Drivetrain(-80,-80);
    pros::delay(500);
    Descore.Toggle();
    Intake.SpinMotor({0,1},{127,127});
    pros::delay(1750);
    Descore.Toggle();
    Intake.StopAllMotors();
    PIDController.driveDistance(14,90,Alfa_Straight,1.5);
    PIDController.Turn(235,100,Alfa_Turn);
    PIDController.driveDistance(-13,90,Alfa_Straight,1.5);
    PIDController.Turn(180,100,Alfa_Turn);
    PIDController.driveDistance(-16,100,Alfa_Straight,1.5);

}
void Auton_5()
{
    PIDController.timeOutLenght = 1000;
    Unstuck = true;
    PIDController.driveDistance(33,100,Alfa_Straight,5);
    MatchLoad.Toggle();
    PIDController.Turn(90,50,Alfa_Turn,3,100);
    Intake.SpinMotor(0,127);
    PIDController.driveDistance(12,100,Alfa_Straight,5);
    pros::delay(0);
    PIDController.driveDistance(-24,100,Alfa_Straight,5);
    MatchLoad.Toggle();
    drivetrain.Set_Drivetrain(-80,-80);
    Intake.SpinMotor({0,1},{127,127});
    pros::delay(1200);
    drivetrain.Set_Drivetrain(0,0);
    PIDController.Swing(195,100,40,Alfa_Swing, 3 , 100);
    Intake.StopMotor(1);
    PIDController.driveDistance(24,40,Alfa_Straight,5);
    MatchLoad.Toggle();
    PIDController.Target_Heading = 180;
    PIDController.driveDistance(12,90,Alfa_Straight,5);
    MatchLoad.Toggle();
    PIDController.driveDistance(50,90,Alfa_Straight,5);
    MatchLoad.Toggle();
    PIDController.Turn(135,30,Alfa_Swing, 3 , 100);
    PIDController.driveDistance(-13,40,Alfa_Straight,5);
    drivetrain.Set_Drivetrain(-10,-10);
    MiddleBlock.Toggle();
    Intake.SpinMotor({0,1},{127,-127});
    pros::delay(1500);
    MiddleBlock.Toggle();
    Intake.StopAllMotors();
    PIDController.driveDistance(65,80,Alfa_Straight,5);
    PIDController.Turn(90,30,Alfa_Swing, 3 , 100);
    PIDController.driveDistance(-10,40,Alfa_Straight,5);
    drivetrain.Set_Drivetrain(-80,-80);
    Intake.SpinMotor({0,1},{127,127});
}
void Auton_6()
{

}
//Start of red side autos

//Start of postive sides
void Auton_7()
{
    

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
    PIDController.timeOutLenght = 1250;
    PIDController.driveDistance(35,80,Alfa_Straight,2);
    MatchLoad.Toggle();
    Intake.SpinMotor(0,127);
    PIDController.Turn(90,100,Alfa_Turn);
    PIDController.timeOutLenght = 750;
    pros::delay(500);
    drivetrain.Set_Drivetrain(100,100);
    pros::delay(300);
    drivetrain.Set_Drivetrain(40,40);
    for (size_t i = 0; i < 4; i++)
    {
        pros::delay(1000);
        drivetrain.Set_Drivetrain(-20,-20);
        pros::delay(100);
        drivetrain.Set_Drivetrain(40,40);
    }
    drivetrain.Set_Drivetrain(0,0);
    PIDController.driveDistance(-8,80,Alfa_Straight,2);
    MatchLoad.Toggle();
    PIDController.Turn(-45,100,Alfa_Turn);
    PIDController.driveDistance(20,80,Alfa_Straight,2);
    PIDController.Turn(-85,100,Alfa_Turn);
    PIDController.timeOutLenght = 3000;
    PIDController.driveDistance(70,80,Alfa_Straight,2);
    PIDController.Turn(-45,100,Alfa_Turn);
    PIDController.driveDistance(-8,80,Alfa_Straight,2);
    drivetrain.Set_Drivetrain(-120,-20);
    pros::delay(1000);
    Intake.SpinMotor({0,1},{127,127});
    pros::delay(3000);
    Intake.StopAllMotors();
    Intake.SpinMotor(0,127);
    PIDController.Target_Heading = -90;
    PIDController.driveDistance(14,80,Alfa_Straight,2);
    PIDController.timeOutLenght = 750;
    MatchLoad.Toggle();
    pros::delay(500);
    drivetrain.Set_Drivetrain(100,100);
    pros::delay(300);
    drivetrain.Set_Drivetrain(40,40);
    for (size_t i = 0; i < 4; i++)
    {
        pros::delay(1000);
        drivetrain.Set_Drivetrain(-20,-20);
        pros::delay(100);
        drivetrain.Set_Drivetrain(40,40);
        
    }
    drivetrain.Set_Drivetrain(0,0);
    PIDController.driveDistance(-8,80,Alfa_Straight,2);
    drivetrain.Set_Drivetrain(-100,-100);
    pros::delay(1000);
    Intake.SpinMotor({0,1},{127,127});
    pros::delay(3000);
    PIDController.Target_Heading = -90;
    MatchLoad.Toggle();
    PIDController.driveDistance(12,80,Alfa_Straight,2);
    PIDController.Turn(-135,100,Alfa_Turn);
    PIDController.driveDistance(-18,80,Alfa_Straight,2);
    PIDController.Turn(-92,100,Alfa_Turn);
     PIDController.timeOutLenght = 3000;
    PIDController.driveDistance(-80,80,Alfa_Straight,2);
     PIDController.timeOutLenght = 1250;
    PIDController.Turn(180,100,Alfa_Turn);
    PIDController.driveDistance(30,80,Alfa_Straight,2);
    PIDController.Turn(135,100,Alfa_Turn);
    PIDController.driveDistance(4,80,Alfa_Straight,2);
    drivetrain.Set_Drivetrain(60,0);
    pros::delay(400);
    PIDController.Target_Heading = 180;
    PIDController.driveDistance(4,80,Alfa_Straight,2);
    MatchLoad.Toggle();
    pros::delay(500);
    drivetrain.Set_Drivetrain(100,100);
    pros::delay(400);
    drivetrain.Set_Drivetrain(127,127);
    pros::delay(750);
    drivetrain.Set_Drivetrain(0,0);
}
void Auton_14()
{
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(200);
    drivetrain.Set_Drivetrain(127,127);
    pros::delay(2500);
    drivetrain.Set_Drivetrain(0,0);
    
}
void Auton_15()
{

}
void Auton_16()
{
    Intake.SpinMotor(0,127);
    drivetrain.driveDistance(127,600);
}
void Auton_17()
{
    drivetrain.Set_Drivetrain(-50,-50);
    pros::delay(400);
    drivetrain.Set_Drivetrain(0,0);
}
void Auton_18()
{
    //Do nothing


}
