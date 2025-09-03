#include "main.h"

class DrivePID
{
    public:
    struct Straight_PID_Var{
        double kP;
        double kI;
        double kD;
        double kA;
        double kAI;
        Straight_PID_Var(double kP_, double kI_, double kD_, double kA_, double kAI_);
        Straight_PID_Var();
    };
    struct Turn_PID_Var{
        double kP;
        double kI;
        double kD;
        bool Passive_Power;
        Turn_PID_Var(double kP_, double kI_, double kD_,  bool Passive_Power_);
        Turn_PID_Var();
    };
    struct Swing_PID_Var{
        double kP;
        double kI;
        double kD;
        Swing_PID_Var(double kP_, double kI_, double kD_);
        Swing_PID_Var();
    };
    private:
        Drivetrain* dTrain;
    public:
        
        double Target_Heading;
        int timeOutLenght = 100000;
        DrivePID(Drivetrain* dTrain_);
        void driveDistance(double inches, double maxPct, Straight_PID_Var variable);
        void driveDistance_Vel(double inches, double maxSpeed, Straight_PID_Var variable);
        void Turn(double angle, double maxTurnSpeed, Turn_PID_Var variable);
        void Turn(double angle, double maxTurnSpeed, Turn_PID_Var variable , double headingTol , double speedTol);
        void Swing(double angle, double maxTurnSpeed, char side, Swing_PID_Var variable);

};

