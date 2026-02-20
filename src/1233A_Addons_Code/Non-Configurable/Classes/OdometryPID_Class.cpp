#include "main.h"

OdometryPID::OdometryPID(Drivetrain* dTrain_ , Odometry* Odom_) 
: dTrain(dTrain_) , Odom(Odom_)
{}

double OdometryPID::NormalToVex(double angle)
{
    return ((angle * -1) + 90);
}
double OdometryPID::VexToNormal(double angle)
{
    return ((angle - 90) * -1);
}
double OdometryPID::RadtoDeg(double Rad)
{
    return Rad * (180/M_PI);
}
double OdometryPID::ShortestAngle(double angle)
{
    return fmod(angle+180,360)-180;
}
void OdometryPID::WaitTillDone()
{
    //TODO change Odom PID to use tasks to allow commands to be run mid PID loop
}
// Using a simple PID loop to turn to a target heading
void OdometryPID::TurnToHeading(double Target, double MaxSpeed, PIDVars Vars)
{   
    dTrain->Change_Brake_Type(Drivetrain::BRAKE);
    double ExitError = 0.1; //Variable to easily change PID exit Conditions
    double IntergalStart = 15; // Variable to easily change when Intergal should start gaining

    //Pos = right Pos error = left forward right backwards
    //K = error * kP + totalerror * kI + (PrevError - Error * kD)
    double Error, TotalError, PrevError, DeltaError;
    while (true)
    {

        Error = fmod((Target - ShortestAngle(RadtoDeg(Odom->Heading))) + 180,360)-180; // Finds the shortest angle towards target
        DeltaError = (PrevError - Error);

        double K = Error * Vars.Kp + TotalError * Vars.Ki + DeltaError * Vars.Kd; // Main PID loop 

        K = std::clamp(K,-MaxSpeed,MaxSpeed); // Makes sure K isn't outside the range of Max Speed

        double LSpeed = K; //Sets the left side to postive because clockwise is postive degress and the left side forwards makes the robot turn clockwise
        double RSpeed =-K;

        if(fabs(Error) > IntergalStart)
        {
            TotalError = 0; //Sets the Total error to 0 if it too far away from it target preventing large I gains when turning
        }
        if(fabs(Error) < .5)// Not really neccesay due to loop closing at 1, but is here for future use
        {
            TotalError = 0; //Resets Total error when it gets close to its target to prevent over shoot.
        }
        if(fabs(Error) < ExitError)
        {
            dTrain->Set_Drivetrain(0,0);
            return; // Exits the loop when close to target
        }

        dTrain->Set_Drivetrain(LSpeed,RSpeed); //Sets the drive motor to the PID output

        TotalError = TotalError + Error; 
        PrevError = Error;

        pros::delay(10); //delay in loop to prevent resorce hogging.
    }
}
//Same as Turn to Heading execpt accept a point to point towards 
void OdometryPID::TurnToPoint(point Point, double MaxSpeed, PIDVars Vars)
{
    dTrain->Change_Brake_Type(Drivetrain::BRAKE);
    //Calculate heading from current pos and target pos to look at then plug the target into turn to heading
    double DeltaX = Point.x - Odom->position.x; //Finds the differnt of the X and Y points to calculate the angle of the vector
    double DeltaY = Point.y - Odom->position.y;
    double angle = atan2(Point.y,Point.x);
    double target = NormalToVex(angle); // convernt normal angle to vex angle by revesing the direction and adding 90
    TurnToHeading(target, MaxSpeed, Vars); // Pass the target onto the PID loop
}

void OdometryPID::GoToPoint(point Point, double MaxSpeed, PIDVars DisVars, PIDVars AngleVars)
{
    dTrain->Change_Brake_Type(Drivetrain::BRAKE);
    //Calcs a vector to follow and will try to return to vector if thrown off

    double ExitError = 1; //Variable to easily change PID exit Conditions
    double IntergalStart = 0; // Variable to easily change when Intergal should start gaining

    double DeltaX, DeltaY, Angle, DeltaAngle, IntialAngle, Distance, VectorDistance; //Define Variables for later use
    double DistanceError, TargetAngle, AngleError;
    double TotalDistanceError, DeltaDistanceError, PrevDistanceError, TotalAngleError, DeltaAngleError, PrevAngleError;
    DeltaX = Point.x - Odom->position.x; //Finds the differnt of the X and Y points to calculate the angle of the vector
    DeltaY = Point.y - Odom->position.y;
    Angle = atan2(DeltaY,DeltaX);
    IntialAngle = NormalToVex(Angle); // convernt normal angle to vex angle by revesing the direction and adding 90
    while(true)
    {
        DeltaX = Point.x - Odom->position.x; 
        DeltaY = Point.y - Odom->position.y;
        Angle = atan2(DeltaY,DeltaX); //Find the angle of a new vector
        Angle = NormalToVex(Angle); // Convernt the angle to Vex field angle
        // Finds the differnt between the Intial vector angle and the it is at now
        // To find the angle to turn to get back onto the vecotr
        DeltaAngle = IntialAngle - Angle; 
        Distance = sqrt(pow(DeltaX,2) + pow(DeltaY,2)); // Finds the magnitude of the new vector
        // This new vector the intial vector forms a right triangle allowing to calcuting the reminding distance of the Intial Vector.
        VectorDistance = Distance * cos(VexToNormal(DeltaAngle)); 
        DistanceError = VectorDistance;
        TargetAngle = IntialAngle - (DeltaAngle * 2); // Calucates a angle that will turn the robot toward the intation vector allowing it to get back onto it
        AngleError = fmod((TargetAngle - ShortestAngle(RadtoDeg(Odom->Heading))) + 180,360)-180; //Calclates the error of the angle of the bot needs to follow
        DeltaDistanceError = PrevDistanceError - DistanceError; // Calculates the change in Error for Distance
        double Kdis = DistanceError * DisVars.Kp + TotalDistanceError * DisVars.Ki + DeltaDistanceError * DisVars.Kd; // Main distance PID loop 
        DeltaAngleError = PrevAngleError - AngleError; // Calculates the change in Error for Angle
        double Kang = AngleError * AngleVars.Kp + TotalAngleError * AngleVars.Ki + DeltaAngleError * AngleVars.Kd; // Main Angle PID loop 
        
        double LSpeed = Kdis + Kang; // Finds each sides speed by add or subtrating the PID angle from output of the distance PID
        double RSpeed = Kdis - Kang;

        if(fabs(AngleError) > IntergalStart)
        {
            TotalAngleError = 0; //Sets the Total error to 0 if it too far away from it target preventing large I gains when turning
        }
        if(fabs(AngleError) < .5)// Not really neccesay due to loop closing at 1, but is here for future use
        {
            TotalAngleError = 0; //Resets Total error when it gets close to its target to prevent over shoot.
        }
        if(fabs(DistanceError) < ExitError) //Exits based on distance toward target
        {
            return; // Exits the loop when close to target
        }

        LSpeed = std::clamp(LSpeed,-MaxSpeed,MaxSpeed);// Makes sure the speed in within the Maxspeed
        RSpeed = std::clamp(RSpeed,-MaxSpeed,MaxSpeed);

        dTrain->Set_Drivetrain(LSpeed,RSpeed);

        TotalAngleError += AngleError;
        TotalDistanceError += DistanceError;
        PrevAngleError = AngleError;
        PrevDistanceError = DistanceError;

        pros::delay(10); // delay in loop to prevent resorce hogging.
    }
}