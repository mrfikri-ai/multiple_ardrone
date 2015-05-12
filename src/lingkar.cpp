/*  Program for takeoff with two ardrones
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

std_msgs::Empty t, l;
geometry_msgs::Twist h;
geometry_msgs::Twist msg1,msg2;

int main(int argc, char** argv)
{
  ROS_INFO("Terbang melingkar");
  ros::init(argc, argv, "ARDrone_test");
  ros::NodeHandle node_handle;
  ros::Rate r(10);
  
  ros::Publisher takeoff1, takeoff2;
  ros::Publisher a1, a2;
  ros::Publisher land1, land2;
  ros::Publisher reset1, reset2;
  ros::Publisher lingkar1, lingkar2;
  
  float takeoff_time = 3.0;
  float lingkar_time = 10.0;
  float land_time = 3.0;
  float reset_time = 3.0;
  
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
  
  reset1 = node_handle.advertise<std_msgs::Empty>("/ardrone1/ardrone/reset", 1);
  reset2 = node_handle.advertise<std_msgs::Empty>("/ardrone2/ardrone/reset", 1);
  
  lingkar1 = node_handle.advertise<geometry_msgs::Twist>("/ardrone1/ardrone/cmd_vel", 1);
  lingkar2 = node_handle.advertise<geometry_msgs::Twist>("/ardrone2/ardrone/cmd_vel", 1);
  
  double start_time=(double)ros::Time::now().toSec();
  while(ros::ok())
  {
    while((double)ros::Time::now().toSec() < start_time+takeoff_time)
    {
      takeoff1.publish(t);
      takeoff2.publish(t);
      a1.publish(h);
      a2.publish(h);
      ROS_INFO("takeoff");
      ros::spinOnce();
      r.sleep();
    } // while takeoff
    
    while  ((double)ros::Time::now().toSec()> start_time+takeoff_time+lingkar_time)
    {
		
			a1.publish(h); //dronenya hovers
			a2.publish(h); //dronenya hovers (harusnya)
			land1.publish(l); //dronenya landing
			land2.publish(l); //dronenya landing
			ROS_INFO("Landing");
			
			if ((double)ros::Time::now().toSec()> takeoff_time+start_time+lingkar_time+land_time+reset_time)
			{
				ROS_INFO("Nodenya mati");
				//pub_empty_reset.publish(emp_msg); //kills the drone		
				exit(0); 	
			}//kill node
			ros::spinOnce();
			r.sleep();
    }
    while ( (double)ros::Time::now().toSec()> start_time+takeoff_time &&(double)ros::Time::now().toSec()< start_time+takeoff_time+fly_time)
    {
      if((double)ros::Time::now().toSec()< (start_time+takeoff_time+lingkar_time)/2)
      {
        a1.publish(msg1);
        a2.publish(msg1);
        ROS_INFO("Terbang lingkar +");
      }
      
      if((double)ros::Time::now().toSec()> (start_time+takeoff_time+fly_time)/2)
      {
        a1.publish(msg2);
        a2.publish(msg2);
        ROS_INFO("Terbang lingkar -");
			} // terbang sesuai twist yang diinginkan
			
			ros::spinOnce();
			r.sleep();
    }
    ros::spinOnce();
    r.sleep();
    
  } //ros::ok
  
} //main
