#include "main.h"

class DrivePID
{
    public:
    struct PIDVars
        {
            double Kp;
            double Ki;
            double Kd;
            PIDVars(double Kp_, double Ki_, double Kd_):Kp(Kp_), Ki(Ki_), Kd(Kd_)
            {}
        };
    private:
        Drivetrain* dTrain;
        Odometry* Odom;
    public:
        
        double Target_Heading;
        int timeOutLenght = 100000;
        double ShortestAngle(double angle);
        DrivePID(Drivetrain* dTrain_, Odometry* Odom_);
        void driveDistance(double inches, double maxPct, PIDVars variable, double Ka);
        //void driveDistance_Vel(double inches, double maxSpeed, PIDVars variable);
        void Turn(double Target, double MaxSpeed, PIDVars Vars, double ExitError = 1, double speedTol = 4);
        void Swing(double Target, double LeftSpeed, double RightSpeed, PIDVars Vars, double ExitError = 1 , double speedTol = 4);

};

