cmake_minimum_required(VERSION 2.8.3)
project(p3at_tutorial)

find_package(catkin REQUIRED COMPONENTS
  amcl
  base_local_planner
  base_local_planner
  gmapping
  move_base
  navfn
  roslaunch
  tf
  urdf
  xacro
)
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES p3at_tutorial
#  CATKIN_DEPENDS amcl base_local_planner base_local_planner gmapping move_base navfn roslaunch tf urdf xacro
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)
