#include "main.h"
MotorController::MotorController(std::vector<pros::Motor*> Motors_, std::vector<ControllerAssigner> Controls_)
: Motors(Motors_) , Controls(Controls_)
{
    for (pros::Motor* Motor : Motors)
    {
        ControllerCache.emplace_back(std::array<int,2> {0,0});
    }
}

void MotorController::SpinMotor(int Motor, double Speed)
{
    Speed = std::clamp(Speed,-126.0,126.0);
    if(Motor < 0)
    {
        Motor = std::abs(Motor);
        Speed = -Speed;
    }
    if (Speed == 0)
    {
        Motors[Motor]->brake();
    } else
    {
        Motors[Motor]->move(Speed);
    }
    
}
void MotorController::SpinMotor(std::vector<int> Motors_, std::vector<double> Speeds)
{
    int i = 0;
    for (int Motor : Motors_)
    {
        Speeds[i] = std::clamp(Speeds[i],-126.0,126.0);
        if(Motor < 0)
        {
            Motor = std::abs(Motor);
            Speeds[i] = -Speeds[i];
        }
        if (Speeds[i] == 0)
        {
            Motors[Motor]->brake();
        } else
        {
            Motors[Motor]->move(Speeds[i]);
        }
        i++;
    }

}
void MotorController::StopMotor(int Motor)
{
    Motors[Motor]->brake();
}
void MotorController::StopMotor(std::vector<int> Motors_)
{
    for (int Motor : Motors_)
    {
        Motors[Motor]->brake();
    }   
}
void MotorController::StopAllMotors()
{
    for (size_t i = 0; i < Motors.capacity(); i++)
    {
        Motors[i]->brake();
    }
    
}
void MotorController::MainControl()
{
    for (size_t i = 0; i < ControllerCache.capacity(); i++)
    {
        ControllerCache[i][0] = 0;
    }
    
    for (ControllerAssigner Control : Controls)
    {
        if(controller.get_digital(Control.Button))
        {
            int i = 0;
            for(int Motor : Control.ControledMotors)
            {
                ControllerCache[Motor][0] = 1;
                ControllerCache[Motor][1] = Control.Speeds[i];
                i++;
            }
        }
    }
    int i = 0;
    for (std::array<int, 2> Motor : ControllerCache)
    {
        if(Motor[0] == 1)
        {
            SpinMotor(i, Motor[1]);
        } else
        {
            SpinMotor(i, 1);
        }
        i++;
    }
}
void MotorController::Unstuck(int Motor, double PCT, double Time, std::vector<int> AffectedMotors, std::vector<double> Powers)
{
    if (Motors[Motor]->get_efficiency() < PCT)
    {
        int i=0;
        for (int Motor_ : AffectedMotors)
        {
            SpinMotor(Motor_,Powers[i]);
            i++;
        }
        pros::delay(Time);
        StopMotor(AffectedMotors);
    }
    
}


