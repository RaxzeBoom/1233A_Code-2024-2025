#include "main.h"
//Intake Config
//Intake Speeds
int DriverIntakeInSpeed[3] = {127,127,127};  //Front Tank Top
int DriverIntakeOutSpeed[3] = {127,127,127};
int DriverScoremidSpeed[3] = {127,60,60};
int DriverScoreHighSpeed[3] = {127,127,127};
int Driver_FrontRoller_Speed = 127;
int Driver_TopRoller_Speed =127;
int Driver_TankRoller_Speed = 127;
//Intake Buttons
pros::controller_digital_e_t IntakeInButton = pros::E_CONTROLLER_DIGITAL_L1;
pros::controller_digital_e_t IntakeOutButton = pros::E_CONTROLLER_DIGITAL_L2;
pros::controller_digital_e_t ScoremidButton = pros::E_CONTROLLER_DIGITAL_R2;
pros::controller_digital_e_t ScoreHighButton = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t FrontRollerFwdButton = pros::E_CONTROLLER_DIGITAL_L2;
pros::controller_digital_e_t FrontRollerRevButton = pros::E_CONTROLLER_DIGITAL_L1;
pros::controller_digital_e_t TankRollerFwdButton = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t TankRollerRevButton = pros::E_CONTROLLER_DIGITAL_R2;
pros::controller_digital_e_t TopRollerFwdButton = pros::E_CONTROLLER_DIGITAL_UP;
pros::controller_digital_e_t TopRollerRevButton = pros::E_CONTROLLER_DIGITAL_DOWN;
pros::controller_digital_e_t ModeSwitchButton = pros::E_CONTROLLER_DIGITAL_LEFT;

