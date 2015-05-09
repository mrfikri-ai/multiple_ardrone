/* This copyright programming script is belong to
 * Muhamad Rausyan Fikri (Author)
 * Electronics and Instrumentation 2011
 * Department of Computer Science and Electronics
 * Universitas Gadjah Mada
 * Credit goes to all contributor from ROS tutorial, github, answer.ros.org etc.
 *
 * The purpose of this script is for final project assignment
 * Allowed to be modified and used widely for better program
 * Goal of this script to drive AR.Drone using controller or autonomously flying
 * For purpose of Multi-agent systems robot 2015
 * This program version 1.1.2
*/

#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <cstdlib>
#include <ardrone_autonomy/Navdata.h>
#include <geometry_msgs/Twist.h>
#include <iostream>

using namespace std;

geometry_msgs::Twist msg_cmd;
geometry_msgs::Twist hover;
geometry_msgs::Twist msg_neg;
geometry_msgs::Twist up;
geometry_msgs::Twist maju;
geometry_msgs::Twist neg_maju;
std_msgs::Empty emp_msg;	
ardrone_autonomy::Navdata msg_in;

int drone_state;


void nav_callback(const ardrone_autonomy::Navdata& msg_in)
{
	//Take in state of ardrone	
	drone_state=msg_in.state;	
}


int main(int argc, char** argv)
{

	ROS_INFO("AR.Drone Terbang");
	ros::init(argc, argv,"ARDrone_test");
    	ros::NodeHandle node;
    	ros::Rate loop_rate(50);
	ros::Publisher takeoff1; 
	ros::Publisher takeoff2; 
	ros::Publisher land1;
	ros::Publisher land2;
	ros::Publisher twist1;
	ros::Publisher twist2;
	ros::Publisher reset1;
	ros::Publisher reset2;
	ros::Publisher msg;
	ros::Subscriber nav_sub1;
	ros::Subscriber nav_sub2;

	float takeoff_time = 5.0;
	float land_time = 5.0;
	float fly_time = 50.0;
	float reset_time = 3.0;
	
//AR.Dronenya Hover	sama kayak altitude hold gitu
	hover.linear.x=0.0; 
	hover.linear.y=0.0;
	hover.linear.z=0.0;
	hover.angular.x=0.0; 
	hover.angular.y=0.0;
	hover.angular.z=0.0; 

//AR Dronenya naik
	up.linear.x=0.0; 
	up.linear.y=0.0;
	up.linear.z=0.25;
	up.angular.x=0.0; 
	up.angular.y=0.0;
	up.angular.z=0.0;

//AR.Dronenya ke kanan	
	msg_cmd.linear.x=0.0; 
	msg_cmd.linear.y=0.25;
	msg_cmd.linear.z=0.0;
	msg_cmd.angular.x=0.0; 
	msg_cmd.angular.y=0.0;
	msg_cmd.angular.z=0.0;
	
//AR.Dronenya negatifnya ke kanan
	msg_neg.linear.x = -msg_cmd.linear.x;
	msg_neg.linear.y = -msg_cmd.linear.y;
	msg_neg.linear.z = -msg_cmd.linear.z;
	msg_neg.angular.x = -msg_cmd.angular.x;
	msg_neg.angular.x = -msg_cmd.angular.y;
	msg_neg.angular.x = -msg_cmd.angular.z;
/*
//AR.Dronenya maju
	maju.linear.x = 0.25;
	maju.linear.y = 0.0;
	maju.linear.z = 0.0;
	maju.angular.x = 0.0;
	maju.angular.y = 0.0;
	maju.angular.z = 0.0;
*/
	
/*	
//AR.Dronenya mundur
	neg_maju.linear.x = -maju.linear.x;
	neg_maju.linear.y = -maju.linear.y;
	neg_maju.linear.z = -maju.linear.z;
	neg_maju.angular.x = -maju.angular.x;
	neg_maju.angular.y = -maju.angular.y;
	neg_maju.angular.z = -maju.angular.z;
*/	
//AR.Dronenya membentuk lingkaran	
//AR.Dronenya membentuk pola delapan	

//Navigasi buat AR Drone
	takeoff1 = node.advertise<std_msgs::Empty>("/ardrone1/ardrone/takeoff", 1); /* Message queue length is just 1 */
	takeoff2 = node.advertise<std_msgs::Empty>("/ardrone2/ardrone/takeoff", 1); /* sama kayak keterangan di atas  */
 	
 	land1 = node.advertise<std_msgs::Empty>("/ardrone1/ardrone/land", 1); /* Message queue length is just 1 */
	land2 = node.advertise<std_msgs::Empty>("/ardrone2/ardrone/land", 1); /* Message queue length is just 1 */
	
	nav_sub1 = node.subscribe("/ardrone1/ardrone/navdata", 1, nav_callback);
	nav_sub2 = node.subscribe("/ardrone2/ardrone/navdata", 1, nav_callback);
	
	reset1 = node.advertise<std_msgs::Empty>("/ardrone1/ardrone/reset", 1); /* Message queue length is just 1 */
	reset2 = node.advertise<std_msgs::Empty>("/ardrone2/ardrone/reset", 1); /* Message queue length is just 1 */

	twist1	= node.advertise<geometry_msgs::Twist>("/ardrone1/ardrone/cmd_vel",1); /* Message queue length is just 1 */
	twist2	= node.advertise<geometry_msgs::Twist>("/ardrone2/ardrone/cmd_vel",1); /* Message queue length is just 1 */

 	double start_time=(double)ros::Time::now().toSec();
 	while (ros::ok()) 
 	{
		while ((double)ros::Time::now().toSec()< start_time+takeoff_time) //takeoff
		{ 
			takeoff1.publish(emp_msg); //launches the drone 1
			takeoff2.publish(emp_msg); //launches the drone 2
			msg.publish(hover); //drone is hovering
			ROS_INFO("Taking off");
			ros::spinOnce();
			loop_rate.sleep();
		}//while untuk takeoff

		while  ((double)ros::Time::now().toSec()> start_time+takeoff_time+fly_time)
		{
			msg.publish(hover); //drone is flat
			land1.publish(emp_msg); //lands the drone 1
			land2.publish(emp_msg); //lands the drone 2
			ROS_INFO("Landing");
			
			if ((double)ros::Time::now().toSec()> takeoff_time+start_time+fly_time+land_time+reset_time)
			{
				ROS_INFO("Closing Node");
				//reset1.publish(emp_msg); //kills the ar drone 1
				//reset2.publish(emp_msg); //kills the ar drone 2		
				exit(0); 	
			}//kill node
			
			ros::spinOnce();
			loop_rate.sleep();			
		}//while landing

		while ( (double)ros::Time::now().toSec()> start_time+takeoff_time &&
				 (double)ros::Time::now().toSec()< start_time+takeoff_time+fly_time)
		{	
			if((double)ros::Time::now().toSec()< start_time+takeoff_time+fly_time/2)
			{
				twist1.publish(msg_cmd);
				twist2.publish(msg_cmd);
				ROS_INFO("Terbang pada sumbu positif");
				
			}//terbang berdasarkan arah yang diinginkan
			
			if((double)ros::Time::now().toSec()> start_time+takeoff_time+fly_time/2)
			{
				twist1.publish(msg_neg);
				twist2.publish(msg_neg);
				ROS_INFO("Terbang sumbu negatif");

			}//terbang berdasarkan arah yang diinginkan
			
		ros::spinOnce();
		loop_rate.sleep();
		}

	ros::spinOnce();
	loop_rate.sleep();

}//ros::ok

}//main
