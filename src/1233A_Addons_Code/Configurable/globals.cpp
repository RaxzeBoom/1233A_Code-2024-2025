#include "main.h"
//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//Drive Motor Configation
pros::Motor Intake(21,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);
pros::Motor WallMech(-20,pros::v5::MotorGear::green,pros::v5::MotorUnits::degrees);
pros::Rotation WallMechRotation(2);
Drivetrain drivetrain(
/*Left Motors Ports*/
    {-9    ,-8    ,-7} ,
/*Right Motors Ports*/
    {6      ,5     ,4 } ,
/*IMUs Ports*/ 
    {3} , 
/*Wheel Size*/
    2.75, 
/*Gear Ratio{Powered,Driven}*/
    {36,48});
Odometry Odom(
/*Drivetrain*/
    &drivetrain ,
/*Robot Width*/
    13.5,
/*Middle Distance*/
    0,
/*Horizontal Tracker Port*/
    4,
/*Vertical Tracker Port*/
    5,
/*Vertical Degrees Per an inch*/
    1,
/*Horizontal Degrees Per an inch*/
    1
);
Ramsete RamseteController(
/*Drivetrain*/
    &drivetrain, 
/*Odometry*/
    &Odom
);
Pnumatics Mogo(
    /*Port*/
    {'A'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_Y,
    /*Reverse*/
    false
);
Pnumatics Doinker(
    /*Port*/
    {'B'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_DOWN,
    /*Reverse*/
    false
);