#include "main.h"
    //Makes a Drivetrain Class for controlling drivetrain functions{All Left Motor Ports | All Right Motor Ports | All IMUs | The wheel diamter | Driven gear then Powered gear}
    Drivetrain::Drivetrain(const std::vector<int>& leftMotorPorts, const std::vector<int>& rightMotorPorts, const std::vector<int>& IMU_Ports , double StraightTPI_, int MotorRPM_) {
        for (int port : leftMotorPorts) {
            leftMotors.emplace_back(port,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);
        }
        for (int port : rightMotorPorts) {
            rightMotors.emplace_back(port,pros::v5::MotorGear::blue,pros::v5::MotorUnits::degrees);
        }
        if(IMU_Ports[0] == 0)
        {
            UsingIMU = false;
        }
        else
        {
            UsingIMU = true;
            for (int port : IMU_Ports){
                IMU_List.emplace_back(port);
            }
        }
        MotorRPM = MotorRPM_;
        StraightTPI = StraightTPI_;
    }
    //Sets a list of Motors to a set speed up to 127
    void Drivetrain::Set_Drive_Motors(std::vector<pros::Motor>& motors, double speed) {
        for (pros::Motor motor : motors) {
            motor.move(speed);
        }
    }
    //Sets a list of Motors to a set speed converted to velocity.
    void Drivetrain::Set_Drive_Motors_Vel(std::vector<pros::Motor>& motors, double speed) {
        for (pros::Motor motor : motors) {
            motor.move_velocity(speed*(MotorRPM/127));
        }
    }
    //Give basic tank drive in driver control
    void Drivetrain::Tank_Control()
    {
        Set_Drivetrain(controller.get_analog(ANALOG_LEFT_Y),controller.get_analog(ANALOG_RIGHT_Y));
    }
    //Give basic split arcade in driver control
    void Drivetrain::Arcade_Control()
    {
        double left = (controller.get_analog(ANALOG_LEFT_Y) + controller.get_analog(ANALOG_RIGHT_X));
        double right = (controller.get_analog(ANALOG_LEFT_Y) - controller.get_analog(ANALOG_RIGHT_X));
        Set_Drivetrain(left, right);
    }
    //Lets the driver switct bewteen Tank & arcade using down arrow.
    void Drivetrain::Driver_Control()
    {
        if(Drivetype == false){Tank_Control();} else{Arcade_Control();}
        if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT) & false)
        {
          if(Drivetype == false) {Drivetype = true;}
          else {Drivetype = false;}
          while((controller.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT))){
             pros::delay(10);
          } 
        }
    }
    //More user friendly way to set a side of the drivetrian 'L' or'l' for left & 'R' or 'r' for right
    void Drivetrain::Set_Side_Drivetrain(char side , double speed)
    {
        if(side == 'l' ^ 'L')
        {
        Set_Drive_Motors(rightMotors , speed);
        } else if(side == 'r' ^ 'R')
        {
        Set_Drive_Motors(leftMotors , speed); 
        } else
        { return;}
    }
    //Sets each side of the drivetrain going from left to right
    void Drivetrain::Set_Drivetrain(double Left_Side_Speed, double Right_Side_Speed)
    {
        Set_Drive_Motors(leftMotors , Left_Side_Speed);
        Set_Drive_Motors(rightMotors , Right_Side_Speed);
    }
    void Drivetrain::Set_Drivetrain_Vel(double Left_Side_Speed, double Right_Side_Speed)
    {
        Set_Drive_Motors_Vel(leftMotors , Left_Side_Speed);
        Set_Drive_Motors_Vel(rightMotors , Right_Side_Speed);
    }
    //Runs basic commands for drivetrain
    void Drivetrain::Initialize(){
        //if(UsingIMU == false) return;
        for (pros::Imu IMU : IMU_List){
            IMU.reset(true);
            IMU.set_data_rate(25);
        }
    }
    //Resets the Motor positions while stoping them
    void Drivetrain::Reset_Motor_Position()
    {

        for (pros::Motor Motor : leftMotors)
        {
            Motor.brake();
            Motor.tare_position();
        }
        for (pros::Motor Motor : rightMotors)
        {
            Motor.brake();
            Motor.tare_position();
        }
    }
    //Get the average positions of one side of the drivetrain 'L' or'l' for left & 'R' or 'r' for right
    double Drivetrain::Get_Position(char side)
    {
        double Total_Ticks = 0;
        if(side == 'l' ^ 'L')
        {
            for (pros::Motor Motor_Check : leftMotors)
            {
                Total_Ticks = Total_Ticks + Motor_Check.get_position();
                
            }
            return Total_Ticks/leftMotors.size();
        } else if(side == 'r' ^ 'R')
        {
            for (pros::Motor Motor_Check : rightMotors)
            {
                Total_Ticks = Total_Ticks + Motor_Check.get_position();
            }
            return Total_Ticks/rightMotors.size();
        } 
       
        return 0;
    }   
    //Get the average RPM of one side of the drivetrain 'L' or'l' for left & 'R' or 'r' for right
    double Drivetrain::Get_RPM(char side)
    {
        double Total_RPM;
        if(side == 'l' ^ 'L')
        {
            for (pros::Motor Motor_Check : leftMotors)
            {
                Total_RPM+= Motor_Check.get_actual_velocity();
            }
            return Total_RPM/leftMotors.size();
        } else if(side == 'r' ^ 'R')
        {
            for (pros::Motor Motor_Check : rightMotors)
            {
                Total_RPM+= Motor_Check.get_actual_velocity();
            }
            return Total_RPM/rightMotors.size();
        } 
        return 0;
    }
    double Drivetrain::Get_Temp()
    {
        double Total_Temp;
        for (pros::Motor Motor_Check : leftMotors)
        {
            Total_Temp+= Motor_Check.get_actual_velocity();
        }
        return Total_Temp/(leftMotors.size() + rightMotors.size());
    }
    //Get the average heading from the IMU
    double Drivetrain::Get_Heading(){
        if(UsingIMU == false) return 0;
        double total = 0;
        for(pros::Imu IMU : IMU_List){
            total = total + IMU.get_heading();//fmod((IMU.get_heading()+180), 360.0)-180.0;//IMU.get_heading();
        }
        total = total/IMU_List.size();
        return total; //= (total < 0 ? 180 + (180 + total) : total);
    }
    //Sets the heading on all IMU
    void Drivetrain::Set_Heading(double heading_){
        if(UsingIMU == false) return;
        for(pros::Imu IMU : IMU_List){
            IMU.set_heading(heading_);
        }
    }
   //Changes the Brake Type for the drivetrain {B for Brake C for Coast H for Hold}
    void Drivetrain::Change_Brake_Type(Brake_Type Type)
    {
        pros::v5::MotorBrake prosBrakeType;
        switch (Type)
        {
        case BRAKE:
            prosBrakeType = pros::v5::MotorBrake::brake;
            break;
        case COAST:
            prosBrakeType = pros::v5::MotorBrake::coast;
            break;
        case HOLD:
            prosBrakeType = pros::v5::MotorBrake::hold;
            break;
        default:
            prosBrakeType = pros::v5::MotorBrake::coast;
            break;
        }
        for (pros::Motor Motor : leftMotors){
            Motor.set_brake_mode(prosBrakeType);
        }
        for (pros::Motor Motor : rightMotors){
            Motor.set_brake_mode(prosBrakeType);
        }
    }
    //Drive at a set speed for a time in Msec
    void Drivetrain::driveDistance(double speed, double time){
        Set_Drivetrain(speed,speed);
        pros::delay(time);
        Set_Drivetrain(0,0);
    }
    //Drive at a set speed(Controled for each side) for a time in Msec
    void Drivetrain::driveDistance(std::vector<double> speed, double time){
        Set_Drivetrain_Vel(speed.at(0),speed.at(1));
        pros::delay(time);
        Set_Drivetrain(0,0);
    }
    

