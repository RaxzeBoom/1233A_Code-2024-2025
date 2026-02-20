#include "main.h"
DrivePID::DrivePID(Drivetrain* dTrain_, Odometry* Odom_)
: dTrain(dTrain_), Odom(Odom_)
{}
    double DrivePID::ShortestAngle(double angle)
    {
        return fmod(angle+180,360)-180;
    }
    void DrivePID::driveDistance(double inches, double maxSpeed, PIDVars variable, double Ka) {
        dTrain->Change_Brake_Type(Drivetrain::BRAKE);
        //dTrain->Reset_Motor_Position();
        Odom->LeftTracker.reset_position();
        Odom->RightTracker.reset_position();
        //Gets Time for Timeout
        int startTime = pros::millis();
    
        // Constants and initial calculations
        //const double target = inches *  dTrain->StraightTPI/24;
        const double target = inches *  Odom->RightTPI;
        const double Max = 127; //Max speed for motors
    
        // PID constants, adjust or utilize as passed from the structure
        double kP = variable.Kp;
        double kI = variable.Ki, kD = variable.Kd;
    
        // PI constants for heading correction
        double kP_heading = Ka;
    
        // Initialize encoder readings and PID variables
        double lAvgTicks = 0, rAvgTicks = 0, avgTicks = 0;
        double error = 0, prevError = 0, accumulativeError = 0;
        double headingError = 0, accheadingrror = 0;
        while (fabs(avgTicks) < fabs(target + ((target > 0) ? -5 : 5))) {
            //controller.print(2,2,"%3f",avgTicks);
            //controller.print(2,2,"%3f",Get_Heading());
            // Calculate PID output
            double currentPower = error * kP + accumulativeError * kI + (error - prevError) * kD;
            currentPower = std::clamp(currentPower,-maxSpeed,maxSpeed);// Constrain power within max
            currentPower = currentPower;
            // Calculate heading error and correction
            headingError = fmod(((Target_Heading-ShortestAngle(dTrain->Get_Heading()))+180.0), 360.0)-180.0;
    
            // Simple proportional correction for heading
            double headingCorrection = headingError * kP_heading ;
    
            // Apply heading correction to motor powers
            double lPower = currentPower + headingCorrection;
            double rPower = currentPower - headingCorrection;
    
            // Constrain Power to highest and lowest power of motors
            lPower = std::clamp(lPower,-Max,Max);
            rPower = std::clamp(rPower,-Max,Max);
    
            // Apply direction and set motor powers
            dTrain->Set_Drivetrain(lPower, rPower);
    
            // Update encoders and error for next iteration
            //lAvgTicks = dTrain->Get_Position('l');
            //rAvgTicks = dTrain->Get_Position('r');
            lAvgTicks = Odom->LeftTracker.get_position();
            rAvgTicks = Odom->RightTracker.get_position();
            avgTicks = (lAvgTicks + rAvgTicks) / 2;
            prevError = error;
            error = target - avgTicks; // Adjust for direction
            controller.print(2,2,"%3f",drivetrain.Get_Heading());
            // Reset accumulative error under specific conditions
            if(fabs(error) < 0.5 || fabs(error) > 150) accumulativeError = 0;
            else accumulativeError += error;
            if(fabs(headingError) < 0.2 || fabs(headingError) > 20) accheadingrror = 0;
            else accheadingrror += headingError;
            if((pros::millis() - startTime) > timeOutLenght)
            {
                return;
            }
            pros::delay(10); // Delay to save resources
        }
        Odom->LeftTracker.reset_position();
        Odom->RightTracker.reset_position();
        dTrain->Set_Drivetrain(0,0);
        pros::delay(100);
        //dTrain->Reset_Motor_Position(); // Reset motors encoders at the end
        
        }
void DrivePID::Turn(double Target, double MaxSpeed, PIDVars Vars, double ExitError , double speedTol)
{   
    while(Target < 0)
    {
        Target = Target + 360;
    }
    dTrain->Change_Brake_Type(Drivetrain::BRAKE);
    Target_Heading = Target;
    //double ExitError = 0.1; //Variable to easily change PID exit Conditions
    double IntergalStart = 15; // Variable to easily change when Intergal should start gaining

    //Pos = right Pos error = left forward right backwards
    //K = error * kP + totalerror * kI + (PrevError - Error * kD)
    double Error, TotalError, PrevError, DeltaError;
    while (true)
    {

        Error = ShortestAngle(Target - ShortestAngle(dTrain->Get_Heading())); // Finds the shortest angle towards target
        DeltaError = (PrevError - Error);

        double K = Error * Vars.Kp + TotalError * Vars.Ki + DeltaError * Vars.Kd; // Main PID loop 
        //controller.print(2,2,"%3f           ",Error);
        K = std::clamp(K,-MaxSpeed,MaxSpeed); // Makes sure K isn't outside the range of Max Speed

        double LSpeed = K; //Sets the left side to postive because clockwise is postive degress and the left side forwards makes the robot turn clockwise
        double RSpeed =-K;

        if(fabs(Error) > IntergalStart)
        {
            TotalError = 0; //Sets the Total error to 0 if it too far away from it target preventing large I gains when turning
        }
        if(fabs(Error) < .5)// Not really neccesay due to loop closing at 1, but is here for future use
        {
            TotalError = 0; //Resets Total error when it gets close to its target to prevent over shoot.
        }
        double currentSpeed = fabs((Odom->LeftTracker.get_velocity() + Odom->RightTracker.get_velocity()) / 2);
        if(fabs(Error) < ExitError && fabs(currentSpeed) < speedTol)
        {
            dTrain->Set_Drivetrain(0,0);
            return; // Exits the loop when close to target
        }
        controller.print(2,2,"%3f",drivetrain.Get_Heading());
        dTrain->Set_Drivetrain_Vel(LSpeed,RSpeed); //Sets the drive motor to the PID output

        TotalError = TotalError + Error; 
        PrevError = Error;

        
        pros::delay(10); //delay in loop to prevent resorce hogging.
    }
}
void DrivePID::Swing(double Target, double LeftSpeed, double RightSpeed, PIDVars Vars, double ExitError , double speedTol)
{   
    while(Target < 0)
    {
        Target = Target + 360;
    }
    dTrain->Change_Brake_Type(Drivetrain::BRAKE);
    Target_Heading = Target;
    //double ExitError = 0.1; //Variable to easily change PID exit Conditions
    double IntergalStart = 15; // Variable to easily change when Intergal should start gaining

    //Pos = right Pos error = left forward right backwards
    //K = error * kP + totalerror * kI + (PrevError - Error * kD)
    double Error, TotalError, PrevError, DeltaError;
    while (true)
    {

        Error = ShortestAngle(Target - ShortestAngle(dTrain->Get_Heading())); // Finds the shortest angle towards target
        DeltaError = (PrevError - Error);

        double K = Error * Vars.Kp + TotalError * Vars.Ki + DeltaError * Vars.Kd; // Main PID loop 
        //controller.print(2,2,"%3f           ",Error);
        double LeftK = std::clamp(K,-LeftSpeed,LeftSpeed); // Makes sure K isn't outside the range of Max Speed
        double RightK = std::clamp(K,-RightSpeed,RightSpeed);

        double LSpeed = LeftK; //Sets the left side to postive because clockwise is postive degress and the left side forwards makes the robot turn clockwise
        double RSpeed =-RightK;

        if(fabs(Error) > IntergalStart)
        {
            TotalError = 0; //Sets the Total error to 0 if it too far away from it target preventing large I gains when turning
        }
        if(fabs(Error) < .5)// Not really neccesay due to loop closing at 1, but is here for future use
        {
            TotalError = 0; //Resets Total error when it gets close to its target to prevent over shoot.
        }
        double currentSpeed = fabs((Odom->LeftTracker.get_velocity() + Odom->RightTracker.get_velocity()) / 2);
        if(fabs(Error) < ExitError && fabs(currentSpeed) < speedTol)
        {
            dTrain->Set_Drivetrain(0,0);
            return; // Exits the loop when close to target
        }
        controller.print(2,2,"%3f",drivetrain.Get_Heading());
        dTrain->Set_Drivetrain_Vel(LSpeed,RSpeed); //Sets the drive motor to the PID output

        TotalError = TotalError + Error; 
        PrevError = Error;

        
        pros::delay(10); //delay in loop to prevent resorce hogging.
    }
}