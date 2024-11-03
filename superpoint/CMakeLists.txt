cmake_minimum_required(VERSION 3.0.2)
project(superpoint)

## Compile as C++11, supported in ROS Kinetic and newer
# add_compile_options(-std=c++11)


find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  roscpp
  rospy
  sensor_msgs
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS rospy std_msgs sensor_msgs geometry_msgs
)

catkin_install_python(PROGRAMS scripts/feature_match_node.py
   DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )
