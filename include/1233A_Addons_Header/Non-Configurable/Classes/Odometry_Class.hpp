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
    double Heading;
    double HorizTPI = 1 , LeftTPI = 1, RightTPI = 1;
public:
    Drivetrain* dTrain;
    bool Updating = false;
    double HorizOffset;
    double LeftOffset;
    double RightOffset;
    pros::v5::Rotation LeftTracker;
    pros::v5::Rotation RightTracker;
    pros::v5::Rotation HorizTracker;

public:
    Odometry(Drivetrain* dTrain_ , double HorizOffset_ , double LeftOffset_, double RightOffset_, int LeftPort, int RightPort, int HorizPort, double LeftTPI_, double RightTPI_, double  HorizTPI_);
    void Update();

};





