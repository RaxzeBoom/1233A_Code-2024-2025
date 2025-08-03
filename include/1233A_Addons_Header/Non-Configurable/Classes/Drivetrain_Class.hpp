#include "main.h"

class Drivetrain {
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
    enum Brake_Type{
        HOLD,
        BRAKE,
        COAST
    };

    public: 
    std::vector<pros::Motor> leftMotors;
    std::vector<pros::Motor> rightMotors;
    std::vector<pros::IMU> IMU_List;
    int timeOutLenght = 100000;
    double current_Max_RPM;
    double Base_Width;
    double StraightTPI;
    double Target_Heading;
    bool RPM_PID_State = true;
    bool Drivetype = false;
    void Set_Drive_Motors(std::vector<pros::Motor>& motors, double speed);
    void Set_Drive_Motors_Vel(std::vector<pros::Motor>& motors, double speed);
    void Tank_Control();
    void Arcade_Control();
    double Get_Position(char side);
    double Get_RPM(char side);
    double Get_Temp();
    void Reset_Motor_Position();
    public:
    Drivetrain(const std::vector<int>& leftMotorPorts, const std::vector<int>& rightMotorPorts, const std::vector<int>& IMU_Ports ,double StraightTPI_);
    void Initialize();
    void Driver_Control();
    void Set_Side_Drivetrain(char side , double speed);
    void Set_Drivetrain(double Left_Side_Speed, double Right_Side_Speed);
    void Set_Drivetrain_Vel(double Left_Side_Speed, double Right_Side_Speed);
    double Get_Heading();
    void Set_Heading(double heading_);
    void Change_Brake_Type(Brake_Type Type);
    void driveDistance(double speed, double time);
    void driveDistance(std::vector<double> speed, double time);
    void driveDistance(double inches, double maxPct, Straight_PID_Var variable);
    void driveDistance_Vel(double inches, double maxSpeed, Straight_PID_Var variable);
    void Turn(double angle, double maxTurnSpeed, Turn_PID_Var variable);
    void Turn(double angle, double maxTurnSpeed, Turn_PID_Var variable , double headingTol , double speedTol);
    void Swing(double angle, double maxTurnSpeed, char side, Swing_PID_Var variable);
};



 














