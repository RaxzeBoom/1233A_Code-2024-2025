#include "main.h"
extern int Driver_TopRoller_Speed;

void SetTopRoller(int power)
{
    TopRoller.move(power);
}
void StopTopRoller()
{
    TopRoller.brake();
}
void Driver_TopRoller() {
    int TopRollerpower = 0;
    if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
        TopRollerpower = Driver_TopRoller_Speed;
    }
    else if(controller.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
        TopRollerpower = Driver_TopRoller_Speed*-1;
    }
    SetTopRoller(TopRollerpower);
}