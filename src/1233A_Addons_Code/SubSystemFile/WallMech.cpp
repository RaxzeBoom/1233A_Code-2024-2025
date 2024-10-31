#include "main.h"
extern int Driver_WallMech_Speed;
extern double WallMechPidVar[3];
extern double DriverWallMechAngle;
double WallMech_Target = 0;
bool WallMechPid = true;
void SetWallMech(int power)
{
    WallMech.move(power);
}
void StopWallMech()
{
    WallMech.move(0);
}
void Driver_WallMech() {
    int WallMechpower = 0;
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R1)) {
        WallMechpower = Driver_WallMech_Speed;
        WallMechPid = false;
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) {
        WallMechpower = Driver_WallMech_Speed*-1;
        WallMechPid = false;
    }
    if(!WallMechPid == true)
    {
    SetWallMech(WallMechpower);
    }
}
void Driver_WmPID(){
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_X) || controller.get_digital(pros::E_CONTROLLER_DIGITAL_B))
    {
        WallMech_Target = DriverWallMechAngle;
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
            double error = -(fmod((WallMech_Target-(WallMechRotation.get_angle()/100) + 540.0), 360.0)-180.0);
            tot_error += error;

            double output = error * WallMechPidVar[0] + tot_error * WallMechPidVar[1] - prev_error * WallMechPidVar[2];
            if(WallMechRotation.get_angle()/100 > 60 & WallMechRotation.get_angle()/100 < 240 )
            {
                output = fabs(output);
            }
            output = std::clamp(output,-100.0,100.0);
            SetWallMech(-output);

            controller.print(2,2,"%3f",error);
            prev_error = error;
        }
        pros::delay(30);
    }
}