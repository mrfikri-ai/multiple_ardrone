/*  Program two ardrones
 *  Muhamad Rausyan Fikri - UGM 
 *
 *  Elins research group
 *  AR.Drone flight with Particle swarm optimization algorithm
 *  PSO_flight.cpp
 */
 
 #include <ros/ros.h>
 #include <std_msgs/Empty.h>
 #include <geometry_msgs/Twist.h>
 #include <cmath>
 #include <iostream>
 #include <cstdlib>
 
 
 // declaration of PSO parameters
 float v_max = 1.0;
 float gbest = 2;
 float pbest = 2;
 
 
 //declaration for ros parameter
 std_msgs::Empty fn;
 geometry_msgs::Twist hover, naik, turun, maju, mundur;
 
 //declaration of PSO formulae, it based on eberhart and kennedy first paper 1995
 
 
 
