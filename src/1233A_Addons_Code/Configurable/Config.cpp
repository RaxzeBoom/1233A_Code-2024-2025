#include "main.h"
//Intake Config
//Intake Speeds
int DriverIntakeInSpeed[3] = {127,127,127};  //Front Middle Hood
int DriverIntakeOutSpeed[3] = {127,127,127};
int DriverScoreMidSpeed[3] = {127,60,60};
int DriverScoreHighSpeed[3] = {127,127,127};
int Driver_FrontRoller_Speed = 127;
int Driver_HoodRoller_Speed =127;
int Driver_MiddleRoller_Speed = 127;
//Intake Buttons
pros::controller_digital_e_t IntakeInButton = pros::E_CONTROLLER_DIGITAL_L1;
pros::controller_digital_e_t IntakeOutButton = pros::E_CONTROLLER_DIGITAL_L2;
pros::controller_digital_e_t ScoreMidButton = pros::E_CONTROLLER_DIGITAL_R2;
pros::controller_digital_e_t ScoreHighButton = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t FrontRollerFwdButton = pros::E_CONTROLLER_DIGITAL_L2;
pros::controller_digital_e_t FrontRollerRevButton = pros::E_CONTROLLER_DIGITAL_L1;
pros::controller_digital_e_t MiddleRollerFwdButton = pros::E_CONTROLLER_DIGITAL_R1;
pros::controller_digital_e_t MiddleRollerRevButton = pros::E_CONTROLLER_DIGITAL_R2;
pros::controller_digital_e_t HoodRollerFwdButton = pros::E_CONTROLLER_DIGITAL_UP;
pros::controller_digital_e_t HoodRollerRevButton = pros::E_CONTROLLER_DIGITAL_DOWN;
pros::controller_digital_e_t ModeSwitchButton = pros::E_CONTROLLER_DIGITAL_LEFT;

