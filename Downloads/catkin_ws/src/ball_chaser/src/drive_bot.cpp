#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "ball_chaser/DriveToTarget.h"

// ROS::Publisher motor commands;
ros::Publisher motor_command_publisher;

bool handle_drive_request(ball_chaser::DriveToTarget::Request& req, ball_chaser::DriveToTarget::Response& res){
    
    geometry_msgs::Twist motor_command;

    motor_command.linear.x = req.linear_x;
    motor_command.angular.z = req.angular_z;

    motor_command_publisher.publish(motor_command);

    res.msg_feedback = "Linear velcoty in x direction set to: " + std::to_string(motor_command.linear.x) + "Angular velocity along z-axis set to: "+ std::to_string(motor_command.angular.z); 
}




int main(int argc, char** argv){

    // Initialize a ROS node
    ros::init(argc, argv, "drive_bot");

    // Create a ROS NodeHandle object
    ros::NodeHandle n;

    // Inform ROS master that we will be publishing a message of type geometry_msgs::Twist on the robot actuation topic with a publishing queue size of 10
    motor_command_publisher = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

    ros::ServiceServer sirvice = n.advertiseService("/ball_chaser/command_robot", handle_drive_request);
    // TODO: Define a drive /ball_chaser/command_robot service with a handle_drive_request callback function
    
    // TODO: Handle ROS communication events
    ros::spin();

    return 0;
}
