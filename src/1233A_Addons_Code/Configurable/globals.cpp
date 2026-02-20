#include "main.h"
//Controller
pros::Controller controller(pros::E_CONTROLLER_MASTER);
//Drive Motor Configation
pros::Motor BottomRoller(17,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);
pros::Motor TopRoller(-8,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);

MotorController::ControllerAssigner IntakeInControl(pros::E_CONTROLLER_DIGITAL_R1, {0} , {127});
MotorController::ControllerAssigner IntakeOutControl(pros::E_CONTROLLER_DIGITAL_R2, {0} , {-127});
MotorController::ControllerAssigner ScoreFwdControl(pros::E_CONTROLLER_DIGITAL_L1, {0,1} , {127,127});
MotorController::ControllerAssigner ScoreRevControl(pros::E_CONTROLLER_DIGITAL_L2, {0,1} , {127,-127});
MotorController Intake({&BottomRoller, &TopRoller,}, {IntakeInControl,IntakeOutControl,ScoreFwdControl,ScoreRevControl});



Drivetrain drivetrain(
/*Left Motors Ports*/
    {-11    ,-18    ,-19} ,
/*Right Motors Ports*/
    {2      ,3     ,4} ,
/*IMUs Ports*/ 
    {10} , 
/*Straight TPI*/
    1110.8+50,
/*Motor RPM*/
    600
);
Odometry Odom(
/*Drivetrain*/
    &drivetrain ,
/*Horiz Offset*/
    2,
/*Left Offset*/
    5.75,
/*Right Offset*/
    5.75,
/*Left Tracker Port*/
    12,
/*Right Tracker Port*/
    14,
/*Horiz Tracker Port*/
    13,
/*Left ticks per inch*/
    83250/24,
/*Right ticks per inch*/
    83250/24,
/*Horiz ticks per inch*/
    97250/24
);
OdometryPID OdomController(
/*Drivetrain*/
    &drivetrain,
/*Odometry*/
    &Odom
);
DrivePID PIDController(
    &drivetrain,
    &Odom
);
Pnumatics MatchLoad(
    /*Port*/
    {'A'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_RIGHT,
    /*Reverse*/
    false
);
Pnumatics Descore(
    /*Port*/
    {'B'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_Y,
    /*Reverse*/
    false
);
Pnumatics MiddleBlock(
    /*Port*/
    {'C'},
    /*Controller Button For Activation*/
    pros::E_CONTROLLER_DIGITAL_L2,
    /*Reverse*/
    false
);