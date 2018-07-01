#include <ros/ros.h>
#include <tf/tf.h>
#include <tf/transform_broadcaster.h>
#include "Eigen/Core"
#include "Eigen/Dense"
#include "Eigen/LU"

using namespace std;
using namespace Eigen;

double x = 0;
double y = 0;
double z = 0;

void broadcast()
{
    static tf::TransformBroadcaster br;
    tf::Transform transform;

    tf::Vector3 tf_vec;
    tf_vec.setX(x);
    tf_vec.setY(y);
    transform.setOrigin(tf_vec);
    
    tf::Quaternion q;
    q.setRPY(0, 0, 0);
    transform.setRotation(q);

    br.sendTransform(tf::StampedTransform(transform, ros::Time::now(), "map", "base_link"));

    x += 0.1;
    y += 0.1;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "tf_broadcaster_test");
    ros::NodeHandle nh;

    ros::Rate rate(10);

    while(ros::ok())
    {
        broadcast();
        ros::spinOnce();
        rate.sleep();
    }
    return 0;
}
