#include "main.h"
    Odometry::Odometry(Drivetrain* dTrain_ , double verticalOffset_ , double middleDist_, int horizontalPort, int verticalPort, double tpi_, double  middleTPI_){
        if(horizontalPort > 0)
        {
            pros::v5::Rotation sensor(horizontalPort);
            horizontalSensor = &sensor;
        } else
        {
            horizontalSensor = NULL;
        }
        if(verticalPort > 0)
        {
            pros::v5::Rotation sensor_(verticalPort);
            verticalSensor = &sensor_;
        } else
        {
            verticalSensor = NULL;
        }
        
        verticalOffset = verticalOffset_;
        dTrain = dTrain_;
        tpi = tpi_;
        middleTpi = middleTPI_;
    }
    void Odometry::Update()
    {   
        Updating == true;
        // Defining variables
        double prev_vectical, prev_middle, prev_heading;
        double vertical_pos, middle_pos, heading;
        double delta_vertical, delta_middle, delta_angle;
        while (Updating == true)
        {
            //Sets new positions
            
            if(horizontalSensor != NULL){
                middle_pos = horizontalSensor->get_position();
            } else{
                middle_pos = 0;
            }
            if(verticalSensor != NULL){
                vertical_pos = verticalSensor->get_position();
            } else{
                vertical_pos = dTrain->Get_Position('r');
            }
            heading = dTrain->Get_Heading() * M_PI / 180;

            // Calculates change in position of tracking wheels
            delta_vertical = (vertical_pos - prev_vectical) / tpi;
            delta_middle = (middle_pos - prev_middle) / middleTpi;
            delta_angle = (heading - prev_heading);

            // Calculates Local change each itteration
            double local_x = 0;
            double local_y = 0;
            
            if (delta_angle) {
                double i = sin(delta_angle / 2.0) * 2.0;
                local_x = (delta_vertical / delta_angle - verticalOffset) * i;
                local_y = (delta_middle / delta_angle + middleDist) * i;
            } else {
                local_x = delta_vertical;
                local_y = delta_middle;
            }
            // Calculated global position
            double p = heading - delta_angle / 2.0;

            position.x += cos(p) * local_x - sin(p) * local_y;
            position.y += cos(p) * local_y + sin(p) *local_x;

            // Store previous positions
            prev_vectical = vertical_pos;
            prev_middle = middle_pos;
            prev_heading = heading;
            pros::delay(10);
        }
    }






