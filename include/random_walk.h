#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>
#include <tf/tf.h>
#include <trajectory_msgs/JointTrajectory.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

class RandomWalk
{
public:
    RandomWalk();
    void sendNewGoal();
    void setLimits(double min_x, double max_x, double min_y, double max_y);

private:
    void goalDoneCallback(const actionlib::SimpleClientGoalState &state, const move_base_msgs::MoveBaseResultConstPtr &result);
    void goalActiveCallback();
    void goalFeedbackCallback(const move_base_msgs::MoveBaseFeedbackConstPtr &feedback);

    MoveBaseClient ac_;

    double min_x_;
    double max_x_;
    double min_y_;
    double max_y_;

};
