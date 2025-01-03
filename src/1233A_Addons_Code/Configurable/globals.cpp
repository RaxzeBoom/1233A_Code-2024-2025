#include "main.h"
//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//Drive Motor Configation
pros::Motor Intake(-7,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);
pros::MotorGroup WallMech({16, -6},pros::v5::MotorGear::green,pros::v5::MotorUnits::degrees);
pros::Rotation WallMechRotation(17);
Drivetrain drivetrain(
/*Left Motors Ports*/
    {-8    ,9    ,-10} ,
/*Right Motors Ports*/
    {18      ,19     ,-20} ,
/*IMUs Ports*/ 
    {5} , 
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
Pnumatics Mogo(
    /*Port*/
    {'A'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_Y,
    /*Reverse*/
    false
);
Pnumatics IntakeLift(
    /*Port*/
    {'B'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_B,
    /*Reverse*/
    false
);
Pnumatics Doinker(
    /*Port*/
    {'C'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_DOWN,
    /*Reverse*/
    false
);