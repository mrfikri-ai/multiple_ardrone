/*  Program for takeoff between two ardrones
 *  Muhamad Rausyan Fikri - UGM 
 *
 *  Elins research group
 *  eight-pattern-movement.cpp
 */

#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>

geometry_msgs::Twist lurus;
geometry_msgs::Twist mundur;
geometry_msgs::Twist lingkar;
geometry_msgs::Twist lingkar_neg;
geometry_msgs::Twist hover;
geometry_msgs::Twist naik;

std_msgs::Empty fn;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "Multiple_ARDrone_test");
  ros::NodeHandle node_handle;
  ros::Rate rate(50);
  
  //untuk inisialisasi takeoff landing dua ardrone
  ros::Publisher takeoff1, takeoff2, land1, land2, reset1, reset2;
  
  //untuk inisialisasi terbang selain takeoff dan landing untuk dua ardrone
  ros::Publisher twist1, twist2;
  
  //hover message
			hover.linear.x=0.0; 
			hover.linear.y=0.0;
			hover.linear.z=0.0;
			hover.angular.x=0.0; 
			hover.angular.y=0.0;
			hover.angular.z=0.0;  
//up message
			naik.linear.x=0.0; 
			naik.linear.y=0.0;
			naik.linear.z=0.5;
			naik.angular.x=0.0; 
			naik.angular.y=0.0;
			naik.angular.z=0.0;
//command message
			float takeoff_time=5.0;
			float fly_time=7.0;
			float land_time=3.0;
			float kill_time =2.0;	
			
//gerak melingkar cw			
			float radius = 5.0;
			lingkar.linear.x=2.0; 
			lingkar.linear.y=0.0;
			lingkar.linear.z=0.0;
			lingkar.angular.x=0.0; 
			lingkar.angular.y=0.0;
			lingkar.angular.z=2.0;

//gerak melingkar ccw
			lingkar_neg.linear.x=-lingkar.linear.x; 
			lingkar_neg.linear.y=-lingkar.linear.y;
			lingkar_neg.linear.z=-lingkar.linear.z;
			lingkar_neg.angular.x=-lingkar.angular.x; 
			lingkar_neg.angular.y=-lingkar.angular.y;
			lingkar_neg.angular.z=-lingkar.angular.z;
// gerak lurus
			lurus.linear.x=2.0; 
			lurus.linear.y=0.0;
			lurus.linear.z=0.0;
			lurus.angular.x=0.0; 
			lurus.angular.y=0.0;
			lurus.angular.z=0.0;

//gerak mundur
			mundur.linear.x=-lurus.linear.x; 
			mundur.linear.y=-lurus.linear.y;
			mundur.linear.z=-lurus.linear.z;
			mundur.angular.x=-lurus.angular.x; 
			mundur.angular.y=-lurus.angular.y;
			mundur.angular.z=-lurus.angular.z;
  
  
  takeoff1 = node_handle.advertise<std_msgs::Empty>("ardrone1/ardrone/takeoff", 1);
  takeoff2 = node_handle.advertise<std_msgs::Empty>("ardrone2/ardrone/takeoff", 1);
  land1 = node_handle.advertise<std_msgs::Empty>("ardrone1/ardrone/land", 1);
  land2 = node_handle.advertise<std_msgs::Empty>("ardrone2/ardrone/land", 1);
  twist1 = node_handle.advertise<geometry_msgs::Twist>("ardrone1/ardrone/cmd_vel", 1);
  twist2 = node_handle.advertise<geometry_msgs::Twist>("ardrone2/ardrone/cmd_vel", 1);
  reset1 = node_handle.advertise<std_msgs::Empty>("ardrone1/ardrone/reset", 1);
  reset2 = node_handle.advertise<std_msgs::Empty>("ardrone2/ardrone/reset", 1);
  
  double start_time = (double)ros::Time::now().toSec();
  ROS_INFO("Begin");
  
  while(ros::ok())
  {
    
  }// end of while ros::ok

  
}//end of int main
  
  
  
  
  
  
