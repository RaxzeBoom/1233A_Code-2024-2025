#include "main.h"

class Odometry
{
public:
    struct point
    {
        double x;
        double y;
    };
    point position = {0,0};
    double tpi = 1 , middleTpi = 1;
private:
    Drivetrain* dTrain;
    bool Updating = false;
    double middleWheel;
    double verticalOffset;
    double middleDist;
    pros::v5::Rotation* horizontalSensor;
    pros::v5::Rotation* verticalSensor;

public:
    bool Using_Middle_Wheel = false;
    Odometry(Drivetrain* dTrain_ , double verticalOffset , double middleDist_, int horizontalPort, int verticalPort, double tpi_, double  middleTPI_);
    void Update();

};





