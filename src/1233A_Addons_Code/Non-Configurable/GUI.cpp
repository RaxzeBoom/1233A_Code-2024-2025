#include "main.h"
bool Toggle_GUI = false;

void Drive_Train_Heat_Drawer(int Drive_Train_Heat)
{
    if(Drive_Train_Heat < 35)
    {
        pros::screen::set_pen(pros::Color::green);
    } else if(Drive_Train_Heat < 60)
    {
        pros::screen::set_pen(pros::Color::yellow);
    } else if (Drive_Train_Heat < 70)
    {
        pros::screen::set_pen(pros::Color::orange_red);
    } else
    {
        pros::screen::set_pen(pros::Color::red);
    }
        pros::screen::fill_rect(40,20,140,200);
        pros::screen::set_pen(pros::Color::black);
        pros::screen::draw_rect(40,20,140,200);
        pros::screen::set_pen(pros::Color::green);
        pros::screen::print(pros::E_TEXT_SMALL,40,210,"Drive Train %3d", Drive_Train_Heat);
}
void autoInfoDrawer()
{
    pros::screen::print(pros::E_TEXT_SMALL,200,20,"X = %3d", Odom.position.x);
    pros::screen::print(pros::E_TEXT_SMALL,200,40,"Y = %3d", Odom.position.y);
    pros::screen::print(pros::E_TEXT_SMALL,200,60,"Heading = %3f", Odom.Heading);
    pros::screen::print(pros::E_TEXT_SMALL,200,80,"Time = %3d", pros::micros());
    //pros::screen::print(pros::E_TEXT_SMALL,200,100,"Sub Time =  %3d", pros::micros() - RamseteController.startTime);
    //pros::screen::print(pros::E_TEXT_SMALL,200,120,"Index %3d", RamseteController.index);
}
void Start_GUI()
{
    pros::screen::set_pen(pros::Color::grey );
    pros::screen::fill_rect(0,0,480,240);
    while(Toggle_GUI)
    {
        int Drive_Train_Heat = (drivetrain.Get_Temp());
        Drive_Train_Heat_Drawer(Drive_Train_Heat);
        autoInfoDrawer();
        pros::delay(40);
        Odom.Update();
    }
}
