/*  Program for takeoff between two ardrones
 *  Muhamad Rausyan Fikri - UGM 
 *
 *  Elins research group
 *  lurus.cpp
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
	std_msgs::Empty emp_msg;
	
int main(int argc, char** argv)
{

    ROS_INFO("ARdrone Test Back and Forth Starting");
    ros::init(argc, argv,"ARDrone_test");
    ros::NodeHandle node;
    ros::Rate loop_rate(20);

	ros::Publisher pub_empty_land1;
	ros::Publisher pub_empty_land2;
	ros::Publisher pub_twist1;
	ros::Publisher pub_twist2;
	ros::Publisher pub_empty_takeoff1;
	ros::Publisher pub_empty_takeoff2;
	ros::Publisher pub_empty_reset1;
	ros::Publisher pub_empty_reset2;
	double start_time;

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
			float fly_time=20.0;
			float land_time=3.0;
			float kill_time =2.0;	
			
//gerak melingkar cw			
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
	
  pub_twist1 = node.advertise<geometry_msgs::Twist>("/ardrone1/ardrone/cmd_vel", 1); /* Message queue length is just 1 */
	pub_twist2 = node.advertise<geometry_msgs::Twist>("/ardrone2/ardrone/cmd_vel", 1); /* Message queue length is just 1 */
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
		while ((double)ros::Time::now().toSec()< start_time+takeoff_time)
		{
		  for(lurus.linear.x = 0; lurus.linear.x <= 40.0; lurus.linear.x += 2.0)
		  {
  		  pub_twist1.publish(lurus);
				pub_twist2.publish(lurus);
				ROS_INFO("terbang lurus");
		  }
		  
		}//fly according to desired twist
						
		ros::spinOnce();
		loop_rate.sleep();
}//ros::ok

}//main
