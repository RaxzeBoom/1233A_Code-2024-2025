#include "main.h"
    class OdometryPID
    {
    private:
        Drivetrain* dTrain;
        Odometry* Odom;
    public:
        OdometryPID(Drivetrain* dTrain_ , Odometry* Odom_);
        void turnToHeading(int target);
    };
    