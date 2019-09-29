# p3at_tutorial

Package demo for ROS navigation in Gazebo usingo Pioneer 3AT.

<p float="left">
  <img src="/docs/p3at_tutorial_gazebo.gif" width="430" />
  <img src="/docs/p3at_tutorial_rviz.gif" width="430" /> 
</p>


*SPAWN ROBOT IN SIMULATION*
In two separate terminal windows:
    * Start the Pioneer 3AT simulation environment:
        roslaunch p3at_tutorial pioneer3at.gazebo.launch

*DEMO WITHOUT MAP*
In two separate terminal windows:
    * Start the Pioneer 3AT simulation environment:
        roslaunch p3at_tutorial pioneer3at.gazebo.launch

    * Start the move_base demo:
        roslaunch p3at_tutorial move_base_mapless_demo.launch

*DEMO LOCALIZATION WITH MAP*
In two separate terminal windows:
    * Start the Pioneer 3AT simulation environment:
        roslaunch p3at_tutorial pioneer3at.gazebo.launch

    * Start the amcl demo:
        roslaunch p3at_tutorial amcl_demo.launch
