/*  Program multi agent dengan quadrotor AR.Drone
 *  dengan menggunakan kendali dari keyboard.
 *  Penulis :
 *  Muhamad Rausyan Fikri - Elins UGM 2011 
 *
 *  Elins research group
 *  keyex.cpp
 *  credit goes to parcon arl_ardrone_examples atas tutorialnya
 */

#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

	geometry_msgs::Twist lurus;
	geometry_msgs::Twist mundur;
	geometry_msgs::Twist lingkar;
	geometry_msgs::Twist lingkar_neg;
	geometry_msgs::Twist hover;
	geometry_msgs::Twist naik;
	geometry_msgs::Twist turun;
	geometry_msgs::Twist kiri;
	geometry_msgs::Twist kanan;
	geometry_msgs::Twist rotasi;
	geometry_msgs::Twist yaw;
	std_msgs::Empty msg;
	
int main(int argc, char** argv)
{

    ROS_INFO("ARdrone Test Back and Forth Starting");
    ros::init(argc, argv,"ARDrone_test");
    ros::NodeHandle node;
    ros::Rate loop_rate(50);

	ros::Publisher pub_empty_land1;
	ros::Publisher pub_empty_land2;
	ros::Publisher pub_twist1;
	ros::Publisher pub_twist2;
	ros::Publisher pub_empty_takeoff1;
	ros::Publisher pub_empty_takeoff2;
	ros::Publisher pub_empty_reset1;
	ros::Publisher pub_empty_reset2;
	double start_time;

//command message
			float takeoff_time=5.0;
			float fly_time=5.0;
			float land_time=3.0;
			float kill_time =2.0;	

//hover message
			hover.linear.x=0.0; 
			hover.linear.y=0.0;
			hover.linear.z=0.0;
			hover.angular.x=0.0; 
			hover.angular.y=0.0;
			hover.angular.z=0.0;  
			
//rotasi kanan 180 derajat
			rotasi.linear.x = 0.0;
			rotasi.linear.y = 0.0;
			rotasi.linear.z = 0.0;
			rotasi.angular.x = 0.0;
			rotasi.angular.y = 0.0;
			rotasi.angular.z = 1.0;

//rotasi kiri 180 derajat
			yaw.linear.x = -rotasi.linear.x;
			yaw.linear.y = -rotasi.linear.y;
			yaw.linear.z = -rotasi.linear.z;
			yaw.angular.x = -rotasi.angular.x;
			yaw.angular.y = -rotasi.angular.y;
			yaw.angular.z = -rotasi.angular.z;
			
//up message
			naik.linear.x=0.0; 
			naik.linear.y=0.0;
			naik.linear.z=0.1;
			naik.angular.x=0.0; 
			naik.angular.y=0.0;
			naik.angular.z=0.0;

//turun
			turun.linear.x = -naik.linear.x;
			turun.linear.y = -naik.linear.y;
			turun.linear.z = -naik.linear.z;
			turun.angular.x = -naik.angular.x;
			turun.angular.y = -naik.angular.y;
			turun.angular.z = -naik.angular.z;	

//kiri 
			kiri.linear.x = 0.0;
			kiri.linear.y = 0.1;
			kiri.linear.z = 0.0;
			kiri.angular.x = 0.0;
			kiri.angular.y = 0.0;
			kiri.angular.z = 0.0;
			
//kanan
			kanan.linear.x = -kiri.linear.x;
			kanan.linear.y = -kiri.linear.y;
			kanan.linear.z = -kiri.linear.z;
			kanan.angular.x = -kiri.angular.x;
			kanan.angular.y = -kiri.angular.y;
			kanan.angular.z = -kiri.angular.z;
			
//gerak melingkar cw			
			lingkar.linear.x=0.1; 
			lingkar.linear.y=0.0;
			lingkar.linear.z=0.0;
			lingkar.angular.x=0.0; 
			lingkar.angular.y=0.0;
			lingkar.angular.z=1.0;

//gerak melingkar ccw
			lingkar_neg.linear.x=-lingkar.linear.x; 
			lingkar_neg.linear.y=-lingkar.linear.y;
			lingkar_neg.linear.z=-lingkar.linear.z;
			lingkar_neg.angular.x=-lingkar.angular.x; 
			lingkar_neg.angular.y=-lingkar.angular.y;
			lingkar_neg.angular.z=-lingkar.angular.z;

// gerak lurus
			lurus.linear.x=0.1; 
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
	
	pub_twist1 = node.advertise<geometry_msgs::Twist>("/ardrone1/cmd_vel", 1); /* Message queue length is just 1 */
	pub_twist2 = node.advertise<geometry_msgs::Twist>("/ardrone2/cmd_vel", 1); /* Message queue length is just 1 */
	pub_empty_takeoff1 = node.advertise<std_msgs::Empty>("/ardrone1/ardrone/takeoff", 1); /* Message queue length is just 1 */
	pub_empty_takeoff2 = node.advertise<std_msgs::Empty>("/ardrone2/ardrone/takeoff", 1); /* Message queue length is just 1 */
	pub_empty_land1 = node.advertise<std_msgs::Empty>("/ardrone1/ardrone/land", 1); /* Message queue length is just 1 */
	pub_empty_land2 = node.advertise<std_msgs::Empty>("/ardrone2/ardrone/land", 1); /* Message queue length is just 1 */
	pub_empty_reset1 = node.advertise<std_msgs::Empty>("/ardrone1/ardrone/reset", 1); /* Message queue length is just 1 */
	pub_empty_reset2 = node.advertise<std_msgs::Empty>("/ardrone2/ardrone/reset", 1); /* Message queue length is just 1 */

	start_time =(double)ros::Time::now().toSec();	
	ROS_INFO("AR Drone loop dimulai, biasanya loop forever");

while (ros::ok()) 
{
	cout <<" simple keyboard controller yang digunakan untuk mengendalikan dua quadrotor \n"
		 <<" inilah perintah yang digunakan untuk setiap stepnya \n"
		 <<" =========================================================================== \n"
		 <<" t/l = takeoff / landing \n"
		 <<" r   = reset \n"
		 <<" a/d = kiri / kanan \n"
		 <<" w/s = maju / mundur \n"
		 <<" q/e = yawing kiri / kanan \n"
		 <<" i/k = naik / turun \n"
		 <<" o/p = lingkar cw / ccw \n"	 
		 <<" Ctrl + C untuk menonaktifkan program \n";
		 
	char m = getchar();	
		
		if(m == 't')		
		{
			pub_empty_takeoff1.publish(msg); //launches the drone
			pub_empty_takeoff2.publish(msg); //launches the drone
			pub_twist1.publish(hover); //drone is flat
			pub_twist2.publish(hover); //drone is flat	
			ROS_INFO("Taking off");
			ros::spinOnce();
			loop_rate.sleep();
			m=' ';	
		}

		if(m == 'l')
		{	
			pub_twist1.publish(hover); //drone is flat
			pub_twist2.publish(hover); //drone is flat
			pub_empty_land1.publish(msg); //lands the drone
			pub_empty_land2.publish(msg); //lands the drone
			ROS_INFO("Landing");
			exit(0);
			m=' ';
		}	
		
		if(m == 'r')
		{				
			ROS_INFO("Closing Node");
			//pub_empty_reset1.publish(msg); //kills the drone
			//pub_empty_reset2.publish(msg); //kills the drone		
			exit(0); 
			ros::spinOnce();
			loop_rate.sleep();			
			m=' ';
		}	
		
		if(m == 'a')
		{
			ROS_INFO("Kiri");
			kiri.linear.y += 1.0;
			pub_twist1.publish(kiri);
			pub_twist2.publish(kiri);
			m = ' ';
		}
		
		if(m == 'd')
		{
			ROS_INFO("kanan");
			kanan.linear.y -= 1.0;
			pub_twist1.publish(kanan);
			pub_twist2.publish(kanan);
			m = ' ';
		}
		
		if(m == 'w' )
		{
			ROS_INFO("maju");
			lurus.linear.x += 1;
			pub_twist1.publish(lurus);
			pub_twist2.publish(lurus);
			m = ' ';
		}
		
		if(m == 's' )
		{
			ROS_INFO("mundur");
			mundur.linear.x -= 1.0;
			pub_twist1.publish(mundur);
			pub_twist2.publish(mundur);
			m = ' ';
		}
		
		if(m == 'q' )
		{
			ROS_INFO("yawing ke kanan");
			rotasi.angular.z += 1.0;
			pub_twist1.publish(rotasi);
			pub_twist2.publish(rotasi);
			m = ' ';
		}
		
		if(m == 'e' )
		{
			ROS_INFO("yawing ke kiri");
			yaw.angular.z -= 1.0;
			pub_twist1.publish(yaw);
			pub_twist2.publish(yaw);
			m = ' ';
		}
		
		if(m == 'i' )
		{
			ROS_INFO("naik");
			naik.linear.z -= 1.0;
			pub_twist1.publish(naik);
			pub_twist2.publish(naik);
			m = ' ';
		}
		
		if(m == 'k' )
		{
			ROS_INFO("turun");
			turun.linear.z -= 1.0;
			pub_twist1.publish(turun);
			pub_twist2.publish(turun);
			m = ' ';
		}
		
		if(m == 'o')
		{
			ROS_INFO("lingkar cw");
			lingkar.linear.x += 1.0;
			lingkar.angular.z += 1.0;
			pub_twist1.publish(lingkar);
			pub_twist2.publish(lingkar);
			m = ' ';
		}
		
		if(m == 'p' )
		{
			ROS_INFO("lingkar ccw");
			lingkar_neg.linear.x -= 1.0;
			lingkar_neg.angular.z -= 1.0;
			pub_twist1.publish(lingkar_neg);
			pub_twist2.publish(lingkar_neg);
			m = ' ';
		}
		
		if(m!='a' || m!='w' || m!='s' || m!='d' || m!='i' || m!='k' || m!='o' || m!='p' || m!='t' || m!='l' || m!='r' )
		{
			ROS_INFO("perintah tidak ditemukan");
			m = ' ';
		}
		
	printf(" \n");	
	ros::spinOnce();
	loop_rate.sleep();

}//ros::ok

}//main
