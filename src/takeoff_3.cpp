/*  Program for takeoff with three ardrones
 *  Muhamad Rausyan Fikri - UGM 
 *
 *  Elins research group
 *  takeoff.cpp
 */

#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist hover;
std_msgs::Empty takeoff;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Multiple_ARDrone_Test");
  ros::NodeHandle node_handle;
  ros::Rate rate(50);
  ros::Publisher a,b,c;
  ros::Publisher twist1, twist2, twist3;
  
  //based on rqt when controlling 2 ardrones, the topics have a name for each ardrone
  //it depends on how many ardrone ip that connected with your access point and ROS
  a = node_handle.advertise<std_msgs::Empty>("/ardrone1/ardrone/takeoff", 1);
  b = node_handle.advertise<std_msgs::Empty>("/ardrone2/ardrone/takeoff", 1);
  c = node_handle.advertise<std_msgs::Empty>("/ardrone3/ardrone/takeoff", 1);
  
  float takeoff_time = 5.0;
  // float fly_time = 5.0;
  twist1 = node_handle.advertise<geometry_msgs::Twist>("/ardrone1/ardrone/cmd_vel", 1);
  twist2 = node_handle.advertise<geometry_msgs::Twist>("/ardrone2/ardrone/cmd_vel", 1);
  twist3 = node_handle.advertise<geometry_msgs::Twist>("/ardrone3/ardrone/cmd_vel", 1);
  
  hover.linear.x = 0.0;
  hover.linear.y = 0.0;
  hover.linear.z = 0.0;
  hover.angular.x = 0.0;
  hover.angular.y = 0.0;
  hover.angular.z = 0.0;
  
  //declaration for max altitude after ardrone is taking-off
  //uint32_t vz = 250; //kecepatan sumbu z = 250mm/s
  
  //uint32_t max_altd = 1500; //declaration of max altitude
  //uint32_t min_altd = 50; //declaration of min altitude
   a.publish(takeoff);
   b.publish(takeoff);   
   c.publish(takeoff);
   
  while(ros::ok())
  {
    double time = (double)ros::Time::now().toSec();
    while ((double)ros::Time::now().toSec() < time + takeoff_time)
    {
      a.publish(takeoff);
      b.publish(takeoff);   
      c.publish(takeoff);
      
      twist1.publish(hover);
      twist2.publish(hover);
      twist3.publish(hover);
      ROS_INFO("AR.Drone Hover");
      ros::spinOnce();
      rate.sleep();
    }
    ROS_INFO("AR.Drone Takeoff");
    exit(0);
  }// while 
  
}// main
