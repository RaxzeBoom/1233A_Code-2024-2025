#include "main.h"
    class OdometryPID
    {
    private:
        Drivetrain* dTrain;
        Odometry* Odom;
    public:
        struct point
        {
            double x;
            double y;
        };
        struct PIDVars
        {
            double Kp;
            double Ki;
            double Kd;
            PIDVars(double Kp_, double Ki_, double Kd_):Kp(Kp_), Ki(Ki_), Kd(Kd_)
            {}
        };
        
        OdometryPID(Drivetrain* dTrain_ , Odometry* Odom_);
        double NormalToVex(double angle);
        double VexToNormal(double angle);
        double RadtoDeg(double Rad);
        double ShortestAngle(double angle);
        void WaitTillDone();
        void TurnToHeading(double Target, double MaxSpeed, PIDVars Vars);
        void TurnToPoint(point Point, double MaxSpeed, PIDVars Vars);
        void GoToPoint(point Point, double MaxSpeed, PIDVars DisVars, PIDVars AngleVars);
    };
    