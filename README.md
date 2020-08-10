# home_service_robot
Udacity Robotics Software Engineer Course final Project

## Program Overview
In this program, a mobile robot goes to an area in which an object is. Then, the mobile robot picks up the object and brings it to drop-off area.
![screen shot](https://github.com/HBKDK/home_service_robot/blob/master/home_service.jpg)
## Requirements
* Gazebo any version later than v7.0.0
* ROS Kinetic : Link <http://wiki.ros.org/ROS/Installation>
* C++11 Compiler (gcc/g++)
* GNU make

## Setup and Running
1. github clone repository
<pre><code>$ git clone https://github.com/HBKDK/home_service_robot
</code></pre>

2. clone nodes
<pre><code>$cd ~/home_service_robot/catkin_ws/src
$ git clone https://github.com/ros-perception/slam_gmapping.git
$ git clone https://github.com/turtlebot/turtlebot.git
$ git clone https://github.com/turtlebot/turtlebot_interactions.git
$ git clone https://github.com/turtlebot/turtlebot_simulator.git
</code></pre>

3. build
<pre><code>$cd ~/home_service_robot/catkin_ws
$ catkin_make
</code></pre>

4. run
<pre><code>$ source devel devel/setup.bash
$ src/scripts/home_service.sh</pre></code>
