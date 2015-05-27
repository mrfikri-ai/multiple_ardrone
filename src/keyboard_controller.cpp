#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Empty.h>
#include <ardrone_autonomy/Navdata.h>
#include <std_msgs/String.h>

// #include <A

#include <sstream>

std_msgs::Empty msg;
geometry_msgs::Twist maju,mundur,hover,lingkar, naik, turun, kiri, kanan;

char message[];

int main(int argc, char **argv)
{
  ros::init(argv, argc, "Navdata feedback");
  ros::NodeHandle n;
  
  ros::Publisher takeoff1 = n.advertise<std_msgs::Empty>("/ardrone1/ardrone/takeoff", 1);
  ros::Publisher takeoff2 = n.advertise<std_msgs::Empty>("/ardrone2/ardrone/takeoff", 1);
  ros::Publisher land1 = n.advertise<std_msgs::Empty>("/ardrone1/ardrone/land", 1);
  ros::Publisher land2 = n.advertise<std_msgs::Empty>("/ardrone2/ardrone/land", 1);
  ros::Publisher twist1 = n.advertise<geometry_msgs::Twist>("/ardrone1/cmd_vel", 1);
  ros::Publisher twist2 = n.advertise<geometry_msgs::Twist>("/ardrone2/cmd_vel", 1);
  
  ros::Rate r(50);

//hover parameter
hover.linear.x = 0;
hover.linear.y = 0;
hover.linear.z = 0;
hover.angular.x = 0;
hover.angular.y = 0;  
hover.angular.z = 0;  

//parameter untuk maju
maju.linear.x = 0.25;
maju.linear.y = 0;
maju.linear.z = 0;
maju.angular.x = 0;
maju.angular.y = 0;  
maju.angular.z = 0;

//parameter untuk mundur
mundur.linear.x = -0.25;
mundur.linear.y = 0;
mundur.linear.z = 0;
mundur.angular.x = 0;
mundur.angular.y = 0;  
mundur.angular.z = 0;

//parameter untuk ke atas
naik.linear.x = 0;
naik.linear.y = 0;
naik.linear.z = 0.25;
naik.angular.x = 0;
naik.angular.y = 0;  
naik.angular.z = 0;

//parameter untuk turun
turun.linear.x = 0;
turun.linear.y = 0;
turun.linear.z = -0.25;
turun.angular.x = 0;
turun.angular.y = 0;  
turun.angular.z = 0;

//parameter untuk ke kiri
kiri.linear.x = 0;
kiri.linear.y = 0.25;
kiri.linear.z = 0;
kiri.angular.x = 0;
kiri.angular.y = 0;  
kiri.angular.z = 0;

//parameter untuk ke kanan
kanan.linear.x = 0;
kanan.linear.y = -0.25;
kanan.linear.z = 0;
kanan.angular.x = 0;
kanan.angular.y = 0;  
kanan.angular.z = 0;

while(ros::ok())
{
	  if(message[0] != " " && message[0] != "a" && message[0] != "s" && message[0] != "w" && message[0] != "d" && message[0] != "z" 
		&& message[0] != "x" && message[0] != "c")
	  {
    
	    continue;
	  }
  
	  if(message[0] ==' ')
	  {
	    takeoff1.publish(msg);
	    takeoff2.publish(msg);
	    twist1.publish(hover);
            twist2.publish(hover);
	    ROS_INFO("takeoff nih");     	
	  }

	  else if(message[0] =='a')
	  {
	   twist1.publish(kiri); //untuk menggerakkan ke kiri dengan kecepatan 0.03 m/s
	   twist2.publish(kiri);
	   ROS_INFO("ke kiri");
	  }

	  else if(message[0] =='s')
	  {
	   twist1.publish(mundur);
	   twist2.publish(mundur);
	   ROS_INFO("mundur");
	  }
	
	 else if(message[0] =='w')
	  {
	   twist1.publish(maju);
	   twist2.publish(maju);
	   ROS_INFO("maju");
	 }

	else if(message[0] =='d')
	  {
	   twist1.publish(kanan);
	   twist2.publish(kanan);
	   ROS_INFO("ke kanan");
	  }

	else if(message[0] =='z')
	  {
	   twist1.publish(naik);
	   twist2.publish(naik);
	   ROS_INFO("naik");
	  }

	else if(message[0] =='x')
	  {
	   twist1.publish(turun);
	   twist2.publish(turun);
	   ROS_INFO("turun");
	  }

	else if(message[0] =='c')
	  {
	   land1.publish(msg);
	   land2.publish(msg);
	   ROS_INFO("landing");
	  }
	
	else{
	ROS_INFO("command not found");
	}

	ros::spinOnce();
	exit(0);

}

}
}//int main
