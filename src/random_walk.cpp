#include "random_walk.h"

RandomWalk::RandomWalk() : ac_("move_base", true)
{
    ROS_INFO("Waiting for the move_base action server to come online...");
    if(!ac_.waitForServer(ros::Duration(7.0)))
    {
        ROS_FATAL("Did you forget to launch the ROS navigation?");
        ROS_BREAK();
    }
    ROS_INFO("Found it!");
}

void RandomWalk::sendNewGoal()
{
    move_base_msgs::MoveBaseGoal goal;

    goal.target_pose.header.frame_id = "odom";
    goal.target_pose.header.stamp = ros::Time::now();

    srand(time(NULL));

    double x = (double(rand()) / double(RAND_MAX)) * (max_x_-min_x_) + min_x_;
    double y = (double(rand()) / double(RAND_MAX)) * (max_y_-min_y_) + min_y_;
    double yaw = (double(rand()) / double(RAND_MAX)) * 2*M_PI - M_PI;

    goal.target_pose.pose.position.x = x;
    goal.target_pose.pose.position.y = y;
    goal.target_pose.pose.orientation = tf::createQuaternionMsgFromYaw(yaw);

    ROS_INFO("Sending a new goal to move_base x %lf y %lf yaw %lf", x, y, yaw);

    ac_.sendGoal(goal, boost::bind(&RandomWalk::goalDoneCallback, this, _1, _2), boost::bind(&RandomWalk::goalActiveCallback, this), boost::bind(&RandomWalk::goalFeedbackCallback, this, _1));
}

void RandomWalk::goalDoneCallback(const actionlib::SimpleClientGoalState &state, const move_base_msgs::MoveBaseResultConstPtr &result)
{

    if(state.state_ == actionlib::SimpleClientGoalState::SUCCEEDED)
        ROS_INFO("The goal was reached!");

    if(state.state_ == actionlib::SimpleClientGoalState::ABORTED)
        ROS_WARN("Failed to reach the goal...");

    sendNewGoal();
}

void RandomWalk::goalActiveCallback()
{
    ROS_INFO("The new goal is active!");
}

void RandomWalk::goalFeedbackCallback(const move_base_msgs::MoveBaseFeedbackConstPtr &feedback)
{
    // ROS_INFO("Getting feedback! How cool is that?");
}

void RandomWalk::setLimits(double min_x, double max_x, double min_y, double max_y)
{
    min_x_ = min_x;
    max_x_ = max_x;
    min_y_ = min_y;
    max_y_ = max_y;
}
