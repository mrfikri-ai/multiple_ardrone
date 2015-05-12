/*  Program for takeoff between two ardrones
 *  Muhamad Rausyan Fikri - UGM 
 *
 *  Elins research group
 *  Reset.cpp
 */
 
#include <ros/ros.h>
#include <std_msgs/Empty.h>
#include <cstdlib>
#include <ardrone_autonomy/Navdata.h>

std_msgs::Empty res;
ardrone_autonomy::Navdata msg_in;
int drone_state;
