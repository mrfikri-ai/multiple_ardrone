/*  Program for takeoff between two ardrones
 *  Muhamad Rausyan Fikri - UGM 
 *
 *  Elins research group
 */

#include <ros/ros.h>
#include <std_msgs/Empty.h>

std_msgs::Empty takeoff;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Multiple_ARDrone_Test");
  ros::NodeHandle node_handle;
  ros::Rate rate(50);
  
  ros::Publisher a,b;
  
  //based on rqt when controlling 2 ardrones, the topics have a name for each ardrone
  //it depends on how many ardrone ip that connected with your access point and ROS
  a = node_handle.advertise<std_msgs::Empty>("/ardrone1/ardrone/takeoff", 1);
  b = node_handle.advertise<std_msgs::Empty>("/ardrone2/ardrone/takeoff", 1);
  float takeoff_time = 5.0;
  
  //declaration for max altitude after ardrone is taking-off
  uint32_t vz = 250; //kecepatan sumbu z = 250mm/s
  
  uint32_t max_altd = 1500; //declaration of max altitude
  uint32_t min_altd = 50; //declaration of min altitude
  
  while(ros::ok())
  {
    double time = (double)ros::Time::now().toSec();
    while ((double)ros::Time::now().toSec() < time + takeoff_time)
    {
      a.publish(takeoff);
      b.publish(takeoff);
      ros::spinOnce();
      rate.sleep();
    }
    
    ROS_INFO("AR.Drone Takeoff");
    exit(0);
  }// while 
  
}// main
