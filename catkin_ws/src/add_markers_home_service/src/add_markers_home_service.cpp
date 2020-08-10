#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include "nav_msgs/Odometry.h"
#include <tf/tf.h>
#include <math.h>

bool bGetObj = 0;
bool bPickUpObj = 0;
bool bDropOffObj = 0;
float obj_x = 0;
float obj_y = 0;
float init_x = 2;
float init_y = 0;

void add_markers_callback(const nav_msgs::Odometry::ConstPtr& pos)
{
  float dist = 0;
  float robot_x = pos->pose.pose.position.x;
  float robot_y = pos->pose.pose.position.y;

  if(bGetObj==0){
    obj_x = 5 - init_x;
    obj_y = 0 - init_y;

    dist = std::sqrt(pow(obj_x-robot_x,2) + pow(obj_y-robot_y,2));
    if(dist <= 0.6){
      bPickUpObj = 1;
    }
  }
  else{
    obj_x = 1 - init_x;
    obj_y = 0- init_y;

    dist = std::sqrt(pow(obj_x-robot_x,2) + pow(obj_y-robot_y,2));
    if(dist <= 0.6){
      bDropOffObj = 1;
    }
  }
  ROS_INFO("Distance from Robot to Object : %f", dist);
  //ROS_INFO("Distance from Robot to Object : %f    %f", robot_x, robot_y);  
}

int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers_home_service");
  ros::NodeHandle n;
  // Subscribe to /odom topic to read the odometry inside the add_markers function 
  ros::Subscriber sub1 = n.subscribe("/odom", 1000, add_markers_callback);
  ros::Rate r(1);
  ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  
  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;

  visualization_msgs::Marker marker;
  // Set the frame ID and timestamp.  See the TF tutorials for information on these.
  marker.header.frame_id = "/map";
  marker.header.stamp = ros::Time::now();

  // Set the namespace and id for this marker.  This serves to create a unique ID
  // Any marker sent with the same namespace and id will overwrite the old one
  marker.ns = "basic_shapes";
  marker.id = 0;

  // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
  marker.type = shape;

  // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
  marker.action = visualization_msgs::Marker::ADD;

  // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
  marker.pose.position.x = 5;
  marker.pose.position.y = 0;
  marker.pose.position.z = 0;
  marker.pose.orientation.x = 0.0;
  marker.pose.orientation.y = 0.0;
  marker.pose.orientation.z = 0.0;
  marker.pose.orientation.w = 1.0;

  // Set the scale of the marker -- 1x1x1 here means 1m on a side
  marker.scale.x = 0.5;
  marker.scale.y = 0.5;
  marker.scale.z = 0.5;

  // Set the color -- be sure to set alpha to something non-zero!
  marker.color.r = 0.0f;
  marker.color.g = 0.0f;
  marker.color.b = 1.0f;
  marker.color.a = 1.0;

  marker.lifetime = ros::Duration();

  // Publish the marker
  while (marker_pub.getNumSubscribers() < 1)
  {
     if (!ros::ok())
     {
        return 0;
      }
      ROS_WARN_ONCE("Please create a subscriber to the marker");
  }
    marker_pub.publish(marker);

  while(ros::ok())
  {
    if(bPickUpObj == 1){
      marker.action = visualization_msgs::Marker::DELETE;
      marker_pub.publish(marker);
      bPickUpObj = 0;
      bGetObj = 1;
      ROS_INFO("Pick up the object");
    }
    else if(bDropOffObj == 1){
      marker.action = visualization_msgs::Marker::ADD;
      marker.pose.position.x = 1;
      marker.pose.position.y = 0;
      marker_pub.publish(marker);
      bDropOffObj = 0;
      ROS_INFO("Drop off the object");
    }
  ros::spinOnce();
  }
}
