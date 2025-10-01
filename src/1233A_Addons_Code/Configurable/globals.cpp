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
    {0} , 
/*Straight TPI*/
    1110.8+50,
/*Motor RPM*/
    600
);
Odometry Odom(
/*Drivetrain*/
    &drivetrain ,
/*Horiz Offset*/
    7.5,
/*Left Offset*/
    7.5,
/*Right Offset*/
    7.5,
/*Left Tracker Port*/
    4,
/*Right Tracker Port*/
    4,
/*Horiz Tracker Port*/
    5,
/*Left ticks per inch*/
    1,
/*Right ticks per inch*/
    1,
/*Horiz ticks per inch*/
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