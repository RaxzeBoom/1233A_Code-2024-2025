#include "main.h"
class MotorController
{
private:
    /* data */
public:
    struct ControllerAssigner
    {
        pros::controller_digital_e_t Button;
        std::vector<int> ControledMotors;
        std::vector<int> Speeds;
        ControllerAssigner(pros::controller_digital_e_t Button_, std::vector<int> ControledMotors_, std::vector<int> Speeds_)
        :Button(Button_), ControledMotors(ControledMotors_), Speeds(Speeds_)
        {}
    };
    std::vector<pros::Motor*> Motors;
    std::vector<ControllerAssigner> Controls;
    std::vector<std::array<int, 2>> ControllerCache;
    MotorController(std::vector<pros::Motor*> Motors_, std::vector<ControllerAssigner> Controls_);
    void SpinMotor(int Motor, double Speed);
    void StopMotor(int Motor);
    void StopMotor(std::vector<int> Motors_);
    void SpinMotor(std::vector<int> Motors, std::vector<double> Speeds);
    void StopAllMotors();
    void MainControl();
    void Unstuck(int Motor, double PCT, double Time, std::vector<int> AffectedMotors,std::vector<double> Powers);
};


