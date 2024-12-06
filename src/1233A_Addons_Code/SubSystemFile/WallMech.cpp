#include "main.h"
extern int Driver_WallMech_Speed;
extern double WallMechPidVar[3];
extern double DriverWallMechAngle;
extern double DriverWallMechAngleEnd;
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
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_A))
    {
        WallMech_Target = DriverWallMechAngleEnd;
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

            double output = error * WallMechPidVar[0];
            double pos = WallMechRotation.get_angle()/100;
            if((pos < 210 & pos > 90) & !(WallMech_Target < 220 & WallMech_Target > 90))
            {
                output = fabs(output);
            }
            if(((pos < 360 & pos > 300) || (pos < 80 & pos > 0)) & !((WallMech_Target < 360 & WallMech_Target > 300) || (WallMech_Target < 80 & WallMech_Target > 0)))
            {
                output = -fabs(output);
            }
            output = std::clamp(output,-100.0,100.0);
            SetWallMech(-output);

            controller.print(2,2,"%3f",error);
        }
        pros::delay(30);
    }
}