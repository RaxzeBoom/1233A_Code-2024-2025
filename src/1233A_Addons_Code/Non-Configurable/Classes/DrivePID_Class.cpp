#include "main.h"
DrivePID::DrivePID(Drivetrain* dTrain_)
{
    dTrain = dTrain_;
}
DrivePID::Straight_PID_Var::Straight_PID_Var() {}
DrivePID::Straight_PID_Var::Straight_PID_Var(double kP_, double kI_, double kD_, double kA_, double kAI_)
    {
        kP = kP_;
        kI = kI_;
        kD = kD_;
        kA = kA_;
        kAI = kAI_;
    };
    DrivePID::Turn_PID_Var::Turn_PID_Var() {}
    DrivePID::Turn_PID_Var::Turn_PID_Var(double kP_, double kI_, double kD_, bool Passive_Power_)
    {
        kP = kP_;
        kI = kI_;
        kD = kD_;
        Passive_Power = Passive_Power_;
    };
    DrivePID::Swing_PID_Var::Swing_PID_Var() {}
    DrivePID::Swing_PID_Var::Swing_PID_Var(double kP_, double kI_, double kD_)
    {
        kP = kP_;
        kI = kI_;
        kD = kD_;
    };
    void DrivePID::driveDistance(double inches, double maxSpeed, Straight_PID_Var variable) {
        dTrain->Change_Brake_Type(Drivetrain::BRAKE);
        dTrain->Reset_Motor_Position();
        //Gets Time for Timeout
        int startTime = pros::millis();
    
        // Constants and initial calculations
        const double target = inches *  dTrain->StraightTPI/24;
        const double Max = 127; //Max speed for motors
    
        // PID constants, adjust or utilize as passed from the structure
        double kP = variable.kP * (inches <= 14 ? 2 : 1);
        double kI = variable.kI, kD = variable.kD;
    
        // PI constants for heading correction
        double kP_heading = variable.kA;
        double kI_heading = variable.kAI;
    
        // Initialize encoder readings and PID variables
        double lAvgTicks = 0, rAvgTicks = 0, avgTicks = 0;
        double error = 0, prevError = 0, accumulativeError = 0;
        double headingError = 0, accheadingrror = 0;
        while (fabs(avgTicks) < fabs(target + ((target > 0) ? -5 : 5))) {
            controller.print(2,2,"%3f",avgTicks);
            //controller.print(2,2,"%3f",Get_Heading());
            // Calculate PID output
            double currentPower = error * kP + accumulativeError * kI + (error - prevError) * kD;
            currentPower = std::clamp(currentPower,-maxSpeed,maxSpeed);// Constrain power within max
            
            // Calculate heading error and correction
            headingError = fmod((Target_Heading-dTrain->Get_Heading()+540.0), 360.0)-180.0;
    
            // Simple proportional correction for heading
            double headingCorrection = headingError * kP_heading + accheadingrror * kI_heading;
    
            // Apply heading correction to motor powers
            double lPower = currentPower + headingCorrection;
            double rPower = currentPower - headingCorrection;
    
            // Constrain Power to highest and lowest power of motors
            lPower = std::clamp(lPower,-Max,Max);
            rPower = std::clamp(rPower,-Max,Max);
    
            // Apply direction and set motor powers
            dTrain->Set_Drivetrain(lPower, rPower);
    
            // Update encoders and error for next iteration
            lAvgTicks = dTrain->Get_Position('l');
            rAvgTicks = dTrain->Get_Position('r');
            avgTicks = (lAvgTicks + rAvgTicks) / 2;
            prevError = error;
            error = target - avgTicks; // Adjust for direction
    
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
        pros::delay(100);
        dTrain->Reset_Motor_Position(); // Reset motors encoders at the end
        }
        void DrivePID::driveDistance_Vel(double inches, double maxSpeed, Straight_PID_Var variable) {
        dTrain->Change_Brake_Type(Drivetrain::BRAKE);
        dTrain->Reset_Motor_Position();
    
        // Constants and initial calculations
        const double target = inches *  dTrain->StraightTPI/24;
        //(((inches / (Wheel_Diameter * M_PI)) * 360 )/ Gear_Ratio)/ 1.1;
        const double Max = 100; //Max speed for motors
    
        // PID constants, adjust or utilize as passed from the structure
        double kP = variable.kP * (inches < 12 ? 2 : 1);
        double kI = variable.kI, kD = variable.kD;
    
        // P constants for heading correction
        double kP_heading = variable.kA;
        double kI_heading = variable.kAI;
    
        // Initialize encoder readings and PID variables
        double lAvgTicks = 0, rAvgTicks = 0, avgTicks = 0;
        double error = 0, prevError = 0, accumulativeError = 0;
        double headingError = 0, accheadingrror = 0;
        while (fabs(avgTicks) < fabs(target)) {
            controller.print(2,2,"%3f",avgTicks);
            // Calculate PID output
            double currentPower = error * kP + accumulativeError * kI + (error - prevError) * kD;
            currentPower = std::clamp(currentPower,-maxSpeed,maxSpeed);// Constrain power within max
            
            // Calculate heading error and correction
            headingError = fmod((Target_Heading-dTrain->Get_Heading()+540.0), 360.0)-180.0;
    
            // Simple proportional correction for heading
            double headingCorrection = headingError * kP_heading + accheadingrror * kI_heading;
    
            // Apply heading correction to motor powers
            double lPower = currentPower + headingCorrection;
            double rPower = currentPower - headingCorrection;
    
            // Constrain Power to highest and lowest power of motors
            lPower = std::clamp(lPower,-Max,Max);
            rPower = std::clamp(rPower,-Max,Max);
    
            // Apply direction and set motor powers
            dTrain->Set_Drivetrain_Vel(lPower, rPower);
    
            // Update encoders and error for next iteration
            lAvgTicks = dTrain->Get_Position('l');
            rAvgTicks = dTrain->Get_Position('r');
            avgTicks = (lAvgTicks + rAvgTicks) / 2;
            prevError = error;
            error = target - avgTicks; // Adjust for direction
    
            // Reset accumulative error under specific conditions
            if(fabs(error) < 0.5 || fabs(error) > 150) accumulativeError = 0;
            else accumulativeError += error;
            if(fabs(headingError) < 0.2 || fabs(headingError) > 20) accheadingrror = 0;
            else accheadingrror += headingError;
            pros::delay(10); // Delay to save resources
        }
        pros::delay(100);
        dTrain->Reset_Motor_Position(); // Reset motors encoders at the end
        }
        void DrivePID::Turn(double angle, double maxTurnSpeed, Turn_PID_Var variable) {
        dTrain->Reset_Motor_Position();
        dTrain->Change_Brake_Type(Drivetrain::BRAKE);
        Target_Heading = angle;
    
        // Calculate the shortest path to the target angle
        double currentAngle = dTrain->Get_Heading();
        double shortestAngle = fmod((angle - currentAngle + 540.0), 360.0) - 180.0;
        double prevShortestAngle = shortestAngle;
        double totalAccumulatedAngleError = 0.0;
    
        // PID Coefficients
        const double kP = variable.kP;
        const double kI = variable.kI;
        const double kD = variable.kD;
    
        while (true) {
            // Calculate target speed based on PID formula
            double targetSpeed = fabs(shortestAngle) * kP + totalAccumulatedAngleError * kI + (fabs(shortestAngle) - fabs(prevShortestAngle)) * kD;
    
            // Apply passive power if needed
            if (variable.Passive_Power) {
                targetSpeed = (targetSpeed > 0) ? targetSpeed + 14 : targetSpeed - 14;
            }
            targetSpeed = std::clamp(targetSpeed,-maxTurnSpeed,maxTurnSpeed);
            // Adjust drivetrain speed based on the sign of the angle
            dTrain->Set_Drivetrain((shortestAngle < 0) ? -targetSpeed : targetSpeed, (shortestAngle < 0) ? targetSpeed : -targetSpeed);
    
            // Update for next iteration
            prevShortestAngle = shortestAngle;
            currentAngle = dTrain->Get_Heading();
            shortestAngle = fmod((angle - currentAngle + 540.0), 360.0) - 180.0;
            totalAccumulatedAngleError += fabs(shortestAngle);
    
            // Reset total accumulated angle error if too far or it overshoots to prevent integral windup
            if (fabs(shortestAngle) < 0.1 || fabs(shortestAngle) > 15) {
                totalAccumulatedAngleError = 0;
            }
    
            // Exit condition: angle is within tolerance and drivetrain speed is sufficiently low
            double currentSpeed = fabs((dTrain->Get_RPM('l') + dTrain->Get_RPM('r')) / 2);
            controller.print(2,2,"%3f",dTrain->Get_Heading());
            controller.print(1,2,"%3f",currentSpeed);
            if (fabs(shortestAngle) < 2.5 & currentSpeed < 5) {
                dTrain->Reset_Motor_Position();
                pros::delay(50);
                return;
            }
    
            // Save resources
            pros::delay(10);
        }
    }
    void DrivePID::Turn(double angle, double maxTurnSpeed, Turn_PID_Var variable , double headingTol , double speedTol) {
        dTrain->Reset_Motor_Position();
        dTrain->Change_Brake_Type(Drivetrain::BRAKE);
        Target_Heading = angle;
    
        // Calculate the shortest path to the target angle
        double currentAngle = dTrain->Get_Heading();
        double shortestAngle = fmod((angle - currentAngle + 540.0), 360.0) - 180.0;
        double prevShortestAngle = shortestAngle;
        double totalAccumulatedAngleError = 0.0;
    
        // PID Coefficients
        const double kP = variable.kP;
        const double kI = variable.kI;
        const double kD = variable.kD;
    
        while (true) {
            // Calculate target speed based on PID formula
            double targetSpeed = fabs(shortestAngle) * kP + totalAccumulatedAngleError * kI + (fabs(shortestAngle) - fabs(prevShortestAngle)) * kD;
    
            // Apply passive power if needed
            if (variable.Passive_Power) {
                targetSpeed = (targetSpeed > 0) ? targetSpeed + 14 : targetSpeed - 14;
            }
            targetSpeed = std::clamp(targetSpeed,-maxTurnSpeed,maxTurnSpeed);
            // Adjust drivetrain speed based on the sign of the angle
            dTrain->Set_Drivetrain((shortestAngle < 0) ? -targetSpeed : targetSpeed, (shortestAngle < 0) ? targetSpeed : -targetSpeed);
    
            // Update for next iteration
            prevShortestAngle = shortestAngle;
            currentAngle = dTrain->Get_Heading();
            shortestAngle = fmod((angle - currentAngle + 540.0), 360.0) - 180.0;
            totalAccumulatedAngleError += fabs(shortestAngle);
    
            // Reset total accumulated angle error if too far or it overshoots to prevent integral windup
            if (fabs(shortestAngle) < 0.1 || fabs(shortestAngle) > 15) {
                totalAccumulatedAngleError = 0;
            }
    
            // Exit condition: angle is within tolerance and drivetrain speed is sufficiently low
            double currentSpeed = fabs((dTrain->Get_RPM('l') + dTrain->Get_RPM('r')) / 2);
            controller.print(2,2,"%3f",dTrain->Get_Heading());
            controller.print(1,2,"%3f",currentSpeed);
            if (fabs(shortestAngle) < headingTol & currentSpeed < speedTol) {
                dTrain->Reset_Motor_Position();
                pros::delay(50);
                return;
            }
    
            // Save resources
            pros::delay(10);
        }
    }
        void DrivePID::Swing(double angle, double maxTurnSpeed, char side, Swing_PID_Var variable) {
            dTrain->Reset_Motor_Position();
            dTrain->Change_Brake_Type(Drivetrain::BRAKE);
            Target_Heading = angle;
    
            // Calculate the shortest path to the target angle
            double currentAngle = dTrain->Get_Heading();
            double shortestAngle = fmod((angle - currentAngle + 540.0), 360.0) - 180.0;
            double prevShortestAngle = shortestAngle;
            double totalAccumulatedAngleError = 0.0;
    
            // PID Coefficients
            const double kP = variable.kP;
            const double kI = variable.kI;
            const double kD = variable.kD;
    
            while (true) {
                // Calculate target speed based on PID formula
                double targetSpeed = fabs(shortestAngle) * kP + totalAccumulatedAngleError * kI + (fabs(shortestAngle) - fabs(prevShortestAngle)) * kD;
    
                // Adjust drivetrain speed based on the sign of the angle
                if(side == 'l'){
                    dTrain->Set_Drivetrain_Vel((shortestAngle < 0) ? -targetSpeed : targetSpeed,0); 
                }else{
                    dTrain->Set_Drivetrain_Vel(0, (shortestAngle < 0) ? targetSpeed : -targetSpeed);
                }
                
    
                // Update for next iteration
                prevShortestAngle = shortestAngle;
                currentAngle = dTrain->Get_Heading();
                shortestAngle = fmod((angle - currentAngle + 540.0), 360.0) - 180.0;
                totalAccumulatedAngleError += fabs(shortestAngle);
    
                // Reset total accumulated angle error if too far or it overshoots to prevent integral windup
                if (fabs(shortestAngle) < 0.5 || fabs(shortestAngle) > 15) {
                    totalAccumulatedAngleError = 0;
                }
    
                // Exit condition: angle is within tolerance and drivetrain speed is sufficiently low
                double currentSpeed = fabs((dTrain->Get_RPM('l') + dTrain->Get_RPM('r')) / 2);
                controller.print(2,2,"%3f",dTrain->Get_Heading());
                controller.print(1,2,"%3f",currentSpeed);
                if (fabs(shortestAngle) < 1.2 & currentSpeed < 2) {
                    dTrain->Reset_Motor_Position();
                    pros::delay(50);
                    return;
                }
    
                // Save resources
                pros::delay(10);
            }
        }