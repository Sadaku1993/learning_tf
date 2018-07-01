#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>

void callback(const geometry_msgs::PoseConstPtr pose)
{
    double x = pose->position.x;
    double y = pose->position.y;
    double z = pose->position.z;
    double q_x = pose->orientation.x;
    double q_y = pose->orientation.y;
    double q_z = pose->orientation.z;
    double q_w = pose->orientation.w;

    tf::Vector3 vector(x, y, z);
    tf::Quaternion quat(q_x, q_y, q_z, q_w);

    double roll, pitch, yaw;
    tf::Matrix3x3(quat).getRPY(roll, pitch, yaw);

    printf("x:%.2f y:%.2f z:%.2f roll:%.2f pitch:%.2f yaw:%.2f\n", x, y, z, roll, pitch, yaw);

    static tf::TransformBroadcaster br;
    tf::Transform transform;
    transform.setOrigin(vector);
    transform.setRotation(quat);

    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map_", "base_link_"));
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "pose_sub_test");
    ros::NodeHandle nh;

    ros::Subscriber sub = nh.subscribe("/pose", 10, callback);

    ros::spin();

    return 0;
}
