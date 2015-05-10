# multiple_ardrone
multiple flying ardrone, a node based from ardrone_autonomy and arl_ardrone_examples
ardrone_autonomy lets you control multiple ardrone in one computer, but not simultaneously
to make it fly together, we have to make a lot of program editing by using arl_ardrone_examples node.

by following https://github.com/AutonomyLab/ardrone_autonomy/wiki/Multiple-AR-Drones instructions
before you run your ROS environment you should create your own node by following this 
https://github.com/parcon/arl_ardrone_examples/tree/master/src

Change dependecies on your CMakeLists.txt, add_executable for your node and direct it with your .cpp or .py file
