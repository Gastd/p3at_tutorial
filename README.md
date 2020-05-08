# p3at_tutorial

## Overview

Package demo for ROS navigation in Gazebo usingo Pioneer 3AT.
This package was inspired by the [Husky navigation tutorials](http://wiki.ros.org/husky_navigation/Tutorials/Husky%20AMCL%20Demo). In this package a Pioneer 3AT is simulated with [move_base] as the mobile base controller and [amcl](http://wiki.ros.org/amcl) as localization system.

<p float="left">
  <img src="/docs/p3at_tutorial_gazebo.gif" width="430" />
  <img src="/docs/p3at_tutorial_rviz.gif" width="430" /> 
</p>

[![asciicast](https://asciinema.org/a/286151.svg)](https://asciinema.org/a/286151)

## License

The source code is released under a [MIT license](LICENSE).

**Author and Maintainer: [Gabriel F P Araujo](mailto:gabriel.fp.araujo@gmail.com)**
<!-- Affiliation: [LARA](https://lara.unb.br/)<br /> -->
<!-- Maintainer: [Gabriel F P Araujo](mailto:gabriel.fp.araujo@gmail.com) and [Raphael Braccialli](mailto:raphael.braccialli@gmail.com) -->

The p3at_tutorial package has been tested under Ubuntu 18.04, [ROS Melodic](https://wiki.ros.org/melodic/Installation/Ubuntu) and Gazebo 9.


<!-- This is research code, expect that it changes often and any fitness for a particular purpose is disclaimed. -->



## Usage

### Dependencies

The package depends of the following packages:

    sudo apt install ros-melodic-navigation ros-melodic-pr2-description

### Config files

Config files are in folder config/

* **costmap_common.yaml** Set all costmap parameters that will be used by any other costmap in this package.
* **costmap_global_laser.yaml** Configure the laser costmap.
* **costmap_global_static.yaml** Configure the costmap produced by the static map.
* **costmap_local.yaml** Configure the costmap produced by the local map.
* **planner.yaml** Set the configuration of the used planners. 

### Launch files

* Demo without map
In two terminal windows:

Start the Pioneer 3AT simulation environment:

    roslaunch p3at_tutorial pioneer3at.gazebo.launch

Start the move_base demo:

    roslaunch p3at_tutorial move_base_mapless_demo.launch

* Demo localization with map
In two terminal windows:

Start the Pioneer 3AT simulation environment:

    roslaunch p3at_tutorial pioneer3at.gazebo.launch

Start the amcl demo:

    roslaunch p3at_tutorial amcl_demo.launch

## Nodes

### Random Walk

Randomly choose a pose in 10x10 square and send this pose to [move_base] as goal

    rosrun p3at_tutorial random_walk


[ROS]: http://www.ros.org
[move_base]: http://wiki.ros.org/move_base
