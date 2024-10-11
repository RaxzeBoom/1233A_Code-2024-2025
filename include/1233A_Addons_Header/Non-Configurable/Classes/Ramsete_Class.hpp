#include "main.h"
extern bool TrackerOn;
class Ramsete
{

private:
    Drivetrain* dTrain;
    Odometry* Tracker;
    
    double Xd;
    double Yd;
    double Ad;
    double Wd;
    double Vd;
public:
    int startTime;
    int index;
    Ramsete(Drivetrain* dTrain_ , Odometry* Tracker_);
    void Controller(double d, double b);
    void Start();
    void Reader(double Path[][7]);

};
