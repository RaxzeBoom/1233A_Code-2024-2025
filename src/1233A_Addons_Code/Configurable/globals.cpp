#include "main.h"
//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//Drive Motor Configation
pros::Motor FrontRoller(5,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);
pros::Motor MiddleRoller(-15,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);
pros::Motor HoodRoller(-8,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);

Drivetrain drivetrain(
/*Left Motors Ports*/
    {-2    ,-4    ,-14} ,
/*Right Motors Ports*/
    {18      ,19     ,21} ,
/*IMUs Ports*/ 
    {13} , 
/*Straight TPI*/
    1110.8+50
);
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
DrivePID PIDController(
    &drivetrain
);
Pnumatics MatchLoad(
    /*Port*/
    {'A'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_Y,
    /*Reverse*/
    false
);
Pnumatics MiddleBlock(
    /*Port*/
    {'B'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_X,
    /*Reverse*/
    false
);