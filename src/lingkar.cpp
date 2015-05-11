/*  Program for takeoff between two ardrones
 *  Muhamad Rausyan Fikri - UGM 
 *
 *  Elins research group
 *  lingkar.cpp
 */

#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <iostream>
#include <cstdlib>

using namespace std;

std_msgs::Empty t, l, h;
geometry_msgs::Twist msg1,msg2;

int main(int argc, char** argv)
{
  ROS_INFO("Terbang melingkar");
  ros::init(argc, argv, "ARDrone_test")
  ros::NodeHandle node_handle;
  ros::Rate r(10);
  
  ros::Publisher takeoff1, takeoff2, a;
  ros::Publisher land1, land2;
  ros::Publisher lingkar1, lingkar2;
  
  float takeoff_time = 3.0;
  float lingkar_time = 10.0;
  float land_time = 3.0;
  
  //state buat hovering
  h.linear.x = 0.0;
  h.linear.y = 0.0;
  h.linear.z = 0.0;
  h.angular.x = 0.0;
  h.angular.y = 0.0;
  h.angular.z = 0.0;
  
  /* definisi gerakan melingkar
   * untuk menggerakan secara melingkar angular.z berfungsi untuk membuat gerakan cmd_vel 
   * seolah-olah melingkar, tidak bergerak ke atas
   * referensi gerakan dari cmd_vel dan ardrone_autonomy
  */
  msg1.linear.x = 0.25;
  msg1.linear.y = 0.0;
  msg1.linear.z = 0.0;
  msg1.angular.x = 0.0;
  msg1.angular.y = 0.0;
  msg1.angular.z = 0.25;
  
  /* berikut ini untuk bergerak melingkar reverse atau counter clockwise
  */
  msg2.linear.x = -msg1.linear.x;
  msg2.linear.y = -msg1.linear.y;
  msg2.linear.z = -msg1.linear.z;
  msg2.angular.x = -msg1.angular.x;
  msg2.angular.y = -msg1.angular.y;
  msg2.angular.z = -msg1.angular.z;
  
  //Empty message buat takeoff dan landing 
  takeoff1 = node_handle.advertise<std_msgs::Empty>("/ardrone1/ardrone/takeoff", 1);
  takeoff2 = node_handle.advertise<std_msgs::Empty>("/ardrone2/ardrone/takeoff", 1);
  
  land1 = node_handle.advertise<std_msgs::Empty>("/ardrone1/ardrone/land", 1);
  land2 = node_handle.advertise<std_msgs::Empty>("/ardrone2/ardrone/land", 1);
  
  lingkar1 = node_handle.advertise<geometry_msgs::Twist>("/ardrone1/ardrone/cmd_vel", 1);
  lingkar2 = node_handle.advertise<geometry_msgs::Twist>("/ardrone2/ardrone/cmd_vel", 1);
  
  double start_time=(double)ros::Time::now().toSec();
  while(ros::ok())
  {
    while((double)ros::Time::now().toSec() < start_time+takeoff_time)
    {
      takeoff1.publish(t);
      takeoff2.publish(t);
      a.publish(h);
      ROS_INFO("takeoff");
      ros::spinOnce();
      r.sleep();
    } // while takeoff
    
    while((double)ros::Time::now().toSec)
  }
}
