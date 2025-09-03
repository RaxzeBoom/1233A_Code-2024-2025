#include "main.h"

class Drivetrain {
    public: 
    enum Brake_Type{
        HOLD,
        BRAKE,
        COAST
    };

    public: 
    std::vector<pros::Motor> leftMotors;
    std::vector<pros::Motor> rightMotors;
    std::vector<pros::IMU> IMU_List;
    double current_Max_RPM;
    double StraightTPI;
    double Base_Width;
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
};



 














