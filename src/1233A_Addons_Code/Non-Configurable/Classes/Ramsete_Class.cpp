#include "main.h"
extern bool TrackerOn;
    Ramsete::Ramsete(Drivetrain* dTrain_ , Odometry* Tracker_)
    {
        dTrain = dTrain_;
        Tracker = Tracker_;
    }

    void Ramsete::Controller(double d, double b)
    {
        // In Rads
        double Theta = dTrain->Get_Heading()* M_PI/180;
        // Finding global frame error
        double XGerror = Xd - Tracker->position.x;
        double YGerror = Yd - Tracker->position.y;
        double AngleError = Ad - Theta;
        // Finding Local frame error
        double xError = (cos(Theta) * XGerror) + (sin(Theta) * YGerror);
        double yError = (-sin(Theta) * XGerror) + (cos(Theta) * YGerror);
        //  Computing Output Velocities
        double k = 2 * d * sqrt(pow(Wd,2) + (b * pow(Vd,2)));
        double V = Vd * cos(AngleError) + k * xError;
        double W = Wd + k * AngleError + ((b* Vd * sin(AngleError) * yError)/AngleError);
        // Find Velocity
        double linearMotorVelcity = V/dTrain->Wheel_Diameter;
        double angularMotorVelcity = W/dTrain->Wheel_Diameter;
        // Find side outputs
        double left = linearMotorVelcity + angularMotorVelcity;
        double right = linearMotorVelcity - angularMotorVelcity;
        // Moves the Bot
        dTrain->Set_Drivetrain(left,right);
    }
    void Ramsete::Start()
    {
        startTime = pros::micros();
    }
    void Ramsete::Reader(double Path[][7])
    {
        if(Path[index][5] == 0)
        {
            TrackerOn = false;
        } else{

        if(!(Path[index + 1][5]*100000) > (u_int64_t)pros::micros)
        {
            index++;
        }
        Xd = Path[index][0];
        Yd = Path[index][1];
        Ad = Path[index][2];
        Vd = Path[index][3];
        Wd = Path[index][4];
        }
    }