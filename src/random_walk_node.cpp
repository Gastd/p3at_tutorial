#include "random_walk.h"

int main(int argc, char** argv)
{
    ros::init(argc, argv, "random_walk_navigation");

    ROS_INFO("random walk example");

    ros::NodeHandle n;
    ros::NodeHandle pn("~");

    double min_x;
    double max_x;
    double min_y;
    double max_y;

    pn.param("min_x", min_x, -10.0);
    pn.param("max_x", max_x, 10.0);
    pn.param("min_y", min_y, -10.0);
    pn.param("max_y", max_y, 10.0);

    RandomWalk rw;
    rw.setLimits(min_x, max_x, min_y, max_y);
    rw.sendNewGoal();

    ros::spin();

    return 0;
}
