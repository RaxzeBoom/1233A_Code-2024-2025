#include "main.h"
    Odometry::Odometry(Drivetrain* dTrain_ , double HorizOffset_ , double LeftOffset_, double RightOffset_, int LeftPort, int RightPort, int HorizPort, double LeftTPI_, double RightTPI_, double  HorizTPI_){

        pros::v5::Rotation leftsensor(LeftPort);
        LeftTracker = &leftsensor;
        pros::v5::Rotation rightsensor(RightPort);
        RightTracker = &rightsensor;
        pros::v5::Rotation Horizsensor(HorizPort);
        HorizTracker = &Horizsensor;

        dTrain = dTrain_;
        HorizOffset = HorizOffset_;
        LeftOffset = LeftOffset_;
        RightOffset = RightOffset_;
        LeftTPI = LeftTPI_;
        RightTPI = RightTPI_;
        HorizTPI = HorizTPI_;
    }
    void Odometry::Update()
    {   
        Updating == true;
        // Defining variables
        double PrevHoriz, PrevLeft, PrevRight, PrevAngle;
        double HorizPos, LeftPos, RightPos, Angle;
        double DeltaHoriz, DeltaLeft, DeltaRight, DeltaAngle;
        while (Updating == true)
        {
            //Sets new positions
            LeftPos = LeftTracker->get_position() / LeftTPI;
            RightPos = RightTracker->get_position() / RightTPI;
            HorizPos = HorizTracker->get_position() / HorizTPI;

            // Calculates change in position of tracking wheels
            DeltaHoriz = (HorizPos - PrevHoriz);
            DeltaLeft = (LeftPos - PrevLeft) / LeftTPI;
            DeltaRight = (RightPos - PrevRight) / RightTPI;

            // Calculates change in Angle and global angle
            Angle = (LeftPos-RightPos)/(LeftOffset+RightOffset);
            DeltaAngle = (Angle - PrevAngle);


            // Calculates Local change each itteration
            double LocalX = 0;
            double LocalY = 0;
            
            if (DeltaAngle != 0) {
                double i = sin(DeltaAngle / 2.0) * 2.0; //Chord Lenght Equation without R
                LocalX = (DeltaHoriz / DeltaAngle + HorizOffset) * i; // Calculates R of arc of travel(From the Horizontal wheel Prespective) then find the Chord Lenght
                LocalY = (DeltaRight / DeltaAngle + RightOffset) * i; // Calculates R of arc of travel then find the Chord Lenght
            } else {
                LocalX = DeltaHoriz; //Angle didn't change so movement is the same as local
                LocalY = DeltaRight;
            }
            // Calculated global position
            double AngleAVG = PrevAngle + DeltaAngle / 2.0; // Calculates the average angle throught the arc or angle of the chord line
            
            // Convernts to Coords into Polor Cords
            double r = sqrt(pow(LocalX,2) + pow(LocalY,2)); // Find the radius of the Local Polor Coord with Distance Formule 
            double LocalAngle = atan2(LocalY,LocalX); // Find the angle of the local Polor Coord
            double GlobalAngle = LocalAngle + AngleAVG; 

            position.x += r * cos(GlobalAngle);
            position.y += r * sin(GlobalAngle);
            Heading = Angle;
            // Store previous positions
            PrevHoriz = HorizPos;
            PrevLeft = LeftPos;
            PrevRight = RightPos;
            PrevAngle = Angle;
            pros::delay(10);
        }
    }




