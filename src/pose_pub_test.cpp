#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_listener.h>
#include <geometry_msgs/Pose.h>
// #include <geometry_msgs/Point.h>
// #include <geometry_msgs/Quaternion.h>

ros::Publisher pub;

void pub_pose(tf::StampedTransform transform)
{
    geometry_msgs::Pose pose;
    // geometry_msgs::Point pose_msg;
    // geometry_msgs::Quaternion quat_msg;

    tf::Vector3 v = transform.getOrigin();

    tf::Quaternion quat = transform.getRotation();
    
    double x = transform.getOrigin().x();
    double y = transform.getOrigin().y();
    double z = transform.getOrigin().z();

    // クォータニオンからオイラー角への変換
    double roll, pitch, yaw;
    tf::Matrix3x3(quat).getRPY(roll ,pitch, yaw);

    // オイラー角からクォータニオンへの変換
    // tf::Quaternion quaternion=tf::createQuaternionFromRPY(roll,pitch,yaw);

    pose.position.x = float(transform.getOrigin().x());
    pose.position.y = float(transform.getOrigin().y());
    pose.position.z = float(transform.getOrigin().z());
    pose.orientation.x = float(transform.getRotation().x());
    pose.orientation.y = float(transform.getRotation().y());
    pose.orientation.z = float(transform.getRotation().z());
    pose.orientation.w = float(transform.getRotation().w());

    // tf::Quaternionからgeometry_msgs::Quaternionへの変換は以下の関数でも可能
    // quaternionTFToMsg(quat,quat_msg);

    printf("x:%.2f y:%.2f z:%.2f roll:%.2f pitch:%.2f yaw:%.2f\n", x, y, z, roll, pitch, yaw);

    pub.publish(pose);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "pose_pub_test");

    ros::NodeHandle nh;

    pub = nh.advertise<geometry_msgs::Pose>("/pose", 10);

    tf::TransformListener listener;

    ros::Rate rate(10);

    while(ros::ok())
    {
        tf::StampedTransform transform;
        try{
            ros::Time now = ros::Time::now();
            listener.waitForTransform("map", "base_link", now, ros::Duration(1.0));
            listener.lookupTransform("map", "base_link", now, transform);
            pub_pose(transform);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
    }
    return 0;
}

