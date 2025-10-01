#include "main.h"

OdometryPID::OdometryPID(Drivetrain* dTrain_ , Odometry* Odom_)
{
    dTrain = dTrain_;
    Odom = Odom_;
}

void OdometryPID::TurnToHeading(double Target, double MaxSpeed, PIDVars)
{   
    //K = error * kP + totalerror * kI + (PrevError - Error * kD)
}