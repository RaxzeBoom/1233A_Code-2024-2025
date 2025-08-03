#include "main.h"
extern int Driver_WallMech_Speed;
extern double WallMechPidVar[3];
extern double DriverWallMechAngleRest;
extern double DriverWallMechAngleLoad;
extern double DriverWallMechAngleShoot;
extern double DriverWallMechAngleStake;
double WallMech_Target = DriverWallMechAngleRest;
bool WallMechPid = false;
void SetWallMech(int power)
{
    WallMech.move(power);
}
void StopWallMech()
{
    WallMech.brake();
}
void Driver_WallMech() {
    int WallMechpower = 0;
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        WallMechpower = Driver_WallMech_Speed;
        WallMechPid = false;
        if(WallMechPid == false)
        {
        SetWallMech(WallMechpower);
        }
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        WallMechpower = Driver_WallMech_Speed*-1;
        WallMechPid = false;
        if(WallMechPid == false)
        {
        SetWallMech(WallMechpower);
        }
    }else if(WallMechPid == false)
    {
        StopWallMech();
    }
   
}
void Driver_WmPID(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X))
    {
        WallMech_Target = DriverWallMechAngleRest;
        WallMechPid = true;
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2))
    {
        WallMech_Target = DriverWallMechAngleLoad;
        WallMechPid = true;
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1))
    {
        WallMech_Target = DriverWallMechAngleShoot;
        WallMechPid = true;
    }
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
    {
        WallMech_Target = DriverWallMechAngleStake;
        WallMechPid = true;
    }
}
void WallMech_PID()
{
    double tot_error;
    double prev_error;
    while (true)
    {
        if(WallMechPid)
        {
            double error = -(fmod((WallMech_Target-(WallMechRotation.get_angle()/100) + 180.0), 360.0)-180.0);

            double output = error * WallMechPidVar[0];
            double pos = WallMechRotation.get_angle()/100;
            
            if((pos < 210 & pos > 130) & !(WallMech_Target < 210 & WallMech_Target > 130))
            {
                output = -fabs(output);
            }
            /*
            if(((pos < 360 & pos > 300) || (pos < 80 & pos > 0)) & !((WallMech_Target < 360 & WallMech_Target > 300) || (WallMech_Target < 80 & WallMech_Target > 0)))
            {
                output = -fabs(output);
            }
            */
            output = std::clamp(output,-127.0,127.0);
            SetWallMech(output);

            //controller.print(2,2,"%3f",error);
        }
        pros::delay(30);
    }
}