#include <ros/ros.h>
#include <ros/package.h>
#include <ros/console.h>
#include <geometry_msgs/TransformStamped.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <tf/transform_listener.h>
#include <tf/transform_broadcaster.h>


geometry_msgs::PoseWithCovarianceStamped pose_rec;

void callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& pose_msg)
{
    pose_rec = *pose_msg;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pose_tf");

    ros::NodeHandle node_handle;
    ros::Subscriber pose_sub = node_handle.subscribe("amcl_pose", 1, callback);
    ros::Rate rate(50.0);

    tf::TransformBroadcaster br;
    tf::TransformListener listener;

    tf::Transform base_to_map;
    tf::StampedTransform base_to_odom;
    tf::Quaternion rotation;


    while(ros::ok())
    {
        try
        {
            listener.lookupTransform("odom", "base_link", ros::Time(0), base_to_odom);
        }
        catch (tf::TransformException ex)
        {
            ROS_ERROR("%s",ex.what());
            continue;
        }

        tf::quaternionMsgToTF(pose_rec.pose.pose.orientation, rotation);
        base_to_map.setOrigin( tf::Vector3(pose_rec.pose.pose.position.x, pose_rec.pose.pose.position.y, 0) );
        base_to_map.setRotation(rotation);

        ROS_INFO_STREAM(pose_rec);

        tf::Transform odom_to_map = base_to_map * base_to_odom.inverse();
        ros::Time ts = ros::Time::now();
        // ros::Duration transform_tolerance(0.5);
        tf::StampedTransform my_tf(odom_to_map, ts, "map2", "odom");
        // br.sendTransform(tf::StampedTransform(odom_to_map, ts+transform_tolerance, "map2", "odom"));
        br.sendTransform(tf::StampedTransform(odom_to_map.inverse(), ts, "odom", "map2"));

        // odom_filter_pub_.publish(odom);

        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
