#include<ros/ros.h>
#include<tf/transform_listener.h>

void show_tf(tf::StampedTransform transform)
{
    tf::Vector3 v = transform.getOrigin();
    double x = transform.getOrigin().x();
    double y = transform.getOrigin().y();
    double z = transform.getOrigin().z();

    tf::Quaternion q = transform.getRotation();
    double q_x = transform.getRotation().x();
    double q_y = transform.getRotation().y();
    double q_z = transform.getRotation().z();
    double q_w = transform.getRotation().w();
    double roll, pitch, yaw;
    tf::Matrix3x3(q).getRPY(roll ,pitch, yaw);

    printf("x:%.2f y:%.2f z:%.2f roll:%.2f pitch:%.2f yaw:%.2f\n", x, y, z, roll, pitch, yaw);

}

int main(int argc, char**argv)
{
    ros::init(argc, argv, "tf_listener_test");

    ros::NodeHandle nh;

    tf::TransformListener listener;

    ros::Rate rate(10.0);

    while(ros::ok())
    {
        tf::StampedTransform transform;
        try{
            ros::Time now = ros::Time::now();
            listener.waitForTransform("map", "base_link", now, ros::Duration(1.0));
            listener.lookupTransform("map", "base_link", now, transform);
            show_tf(transform);
        }
        catch (tf::TransformException ex){
            ROS_ERROR("%s",ex.what());
            ros::Duration(1.0).sleep();
        }
    }
    return 0;
}

