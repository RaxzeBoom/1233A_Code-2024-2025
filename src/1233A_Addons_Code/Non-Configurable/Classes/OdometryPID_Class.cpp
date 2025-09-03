#include "main.h"

OdometryPID::OdometryPID(Drivetrain* dTrain_ , Odometry* Odom_)
{
    dTrain = dTrain_;
    Odom = Odom_;
}

void OdometryPID::turnToHeading(int target)
{   
    dTrain->Get_Heading();
}