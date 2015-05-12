# multiple_ardrone
multiple flying ardrone, a node based from ardrone_autonomy and arl_ardrone_examples
ardrone_autonomy lets you control multiple ardrone in one computer, but to make multiple ardrones fly together simultaneously, we have to make a lot of program editing by using arl_ardrone_examples node.

by following https://github.com/AutonomyLab/ardrone_autonomy/wiki/Multiple-AR-Drones instructions
before you run your ROS environment you should create your own node by following this 
https://github.com/parcon/arl_ardrone_examples/tree/master/src

Change dependecies on your CMakeLists.txt, add_executable for your node and direct it with your .cpp or .py file

First time I usually do when running this node
> follow the instruction how to connect same IP address on multiple ardrones to your access point
> roscore
> roslaunch ardrone_autonomy [executable].launch
> make sure you have make re-create and edited .launch file in ardrone_autonomy/src and give a name to each ardrone <group ns=""> before declaration of <node-pkg> and arguments for each ardrone with desired IP address.
> open new terminal rosrun multiple_ardrone takeoff (launch ardrone to takeoff)
