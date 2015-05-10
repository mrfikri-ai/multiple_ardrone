/*  Program for takeoff between two ardrones
 *  Muhamad Rausyan Fikri - UGM 
 *
 *  Elins research group
 */
 
#include <ros/ros.h>
#include <std_msgs/Empty.h>

std_msgs::Empty landing;

int main(int argc, char** argv)
{
 
 ros::init (argc, argv, "Multiple_ARDrone_Test");
 ros::NodeHandle node_handle;
 ros::Rate rate(50);
 
 ros::Publisher a,b;
 a = node_handle.advertise<std_msgs::Empty>("/ardrone1/ardrone/land", 1); commence to make ardrone 1 land
 b = node_handle.advertise<std_msgs::Empty>("/ardrone2/ardrone/land", 1);
 
 float land_time = 5.0;
 
 while(ros::ok())
 {
  
  //using ros::Time::now() as timer when ardrone takeoff and landing as well
  double time = (double)ros::Time::now().toSec();
  while((double)ros::Time::now().toSec() < time + land_time)
  {
   
   a.publish(landing);
   b.publish(landing);
   ros::spinOnce();
   rate.sleep();
   
  } // landing while
  
  ROS_INFO("AR.Drone 1 and 2 landing");
  exit(0);
  
 } // while loop
 
} //main program
