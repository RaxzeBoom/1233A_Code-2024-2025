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
        };
        OdometryPID(Drivetrain* dTrain_ , Odometry* Odom_);
        void TurnToHeading(double Target, double MaxSpeed, PIDVars);
        void TurnToPoint(point Point);
        void GoToPoint(point Point);
    };
    